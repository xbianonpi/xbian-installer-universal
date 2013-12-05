#include "diskwriter_unix.h"

#include <QDebug>

#include <QApplication>
#include <QDir>
#include <QProcess>
#include <QTextStream>

#if defined(Q_OS_LINUX)
#include <blkid/blkid.h>
#include "QtZlib/zlib.h"
#else
#include "zlib.h"
#endif

DiskWriter_unix::DiskWriter_unix(QObject *parent) :
    DiskWriter(parent)
{
    isCancelled = false;
}

DiskWriter_unix::~DiskWriter_unix()
{
    if (dev.isOpen()) {
        dev.close();
    }
}

int DiskWriter_unix::open(QString device)
{

#ifdef Q_OS_MAC
    // Write to RAW device, this is MUCH faster
    device.replace("/dev/","/dev/r");
#endif

    dev.setFileName(device);

#ifdef Q_OS_MAC
    QProcess unmount;
    unmount.start("diskutil unmountDisk "+device, QIODevice::ReadOnly);
    unmount.waitForStarted();
    unmount.waitForFinished();
#endif

    if (!dev.open(QFile::WriteOnly)) {
        return -1;
    }
    return 0;
}

void DiskWriter_unix::close()
{
    dev.close();
}

bool DiskWriter_unix::isOpen()
{
    return dev.isOpen();
}

void DiskWriter_unix::cancelWrite()
{
    isCancelled = true;
}

bool DiskWriter_unix::writeCompressedImageToRemovableDevice(const QString &filename)
{
    int r;
    bool ok;
    // 512 == common sector size
    char buf[512*1024];

    if (!dev.isOpen()) {
        return false;
    }

    // Open source
    gzFile src = gzopen(filename.toStdString().c_str(), "rb");
    if (src == NULL) {
        return false;
    }

    if (gzbuffer(src, 128*1024) != 0) {
        gzclose_r(src);
        return false;
    }

    r = gzread(src, buf, sizeof(buf));
    while (r > 0 && ! isCancelled) {
        // TODO: Sanity check
        ok = dev.write(buf, r);
        if (!ok) {
            return false;
        }
        emit bytesWritten(gztell(src));
        QApplication::processEvents();
        r = gzread(src, buf, sizeof(buf));
    }

    isCancelled = false;
    if (r < 0) {
        gzclose_r(src);
        return false;
    }

    dev.close();
    gzclose_r(src);
    return true;
}

QStringList DiskWriter_unix::getRemovableDeviceNames()
{

    QStringList names;
    QStringList unmounted;

#ifdef Q_OS_LINUX
    names = getDeviceNamesFromSysfs();

    foreach (QString device, names)
    {
        if (this->checkIfUSB(device)) unmounted << "/dev/"+device;
    }

    return unmounted;
#else
    QProcess lsblk;
    lsblk.start("diskutil list", QIODevice::ReadOnly);
    lsblk.waitForStarted();
    lsblk.waitForFinished();

    QString device = lsblk.readLine();
    while (!lsblk.atEnd()) {
        device = device.trimmed(); // Odd trailing whitespace

        if (device.startsWith("/dev/disk")) {
            // We only want to add USB devics
            QString name = device.split(QRegExp("\\s+")).first();
            if (this->checkIfUSB(name)) {
                names.append(name);
            }
        }
        device = lsblk.readLine();
    }

    return names;
#endif
}

QStringList DiskWriter_unix::getUserFriendlyNamesRemovableDevices(QStringList devices) {
    QStringList returnList;

        foreach (QString s, devices) {
    #ifdef Q_OS_LINUX
            quint64 size = driveSize(s);
            QStringList partInfo = getPartitionsInfo(s);

            QTextStream friendlyName(&s);
            friendlyName.setRealNumberNotation(QTextStream::FixedNotation);
            friendlyName.setRealNumberPrecision(2);
            friendlyName << " (";
            friendlyName << size/(1024*1024*1024.0) << " GB, partitions: ";
            foreach (QString partition, partInfo) {
                friendlyName << partition << ", ";
            }
            s.chop(2);
            friendlyName << ")";

            returnList.append(s);
    #else
            QProcess lsblk;
            lsblk.start(QString("diskutil info %1").arg(s), QIODevice::ReadOnly);
            lsblk.waitForStarted();
            lsblk.waitForFinished();

            QString output = lsblk.readLine();
            QStringList iddata;
            QString item = "";
            while (!lsblk.atEnd()) {
                output = output.trimmed(); // Odd trailing whitespace
                if (output.contains("Device / Media Name:")) { // We want the volume name of this device
                    output.replace("Device / Media Name:      ","");
                    iddata.append(output);
                }else if (output.contains("Device Identifier:")) { // We want the volume name of this device
                    output.replace("Device Identifier:        ","");
                    iddata.append(output);
                }else if (output.contains("Total Size:")) { // We want the volume name of this device
                     output.replace("Total Size:               ","");
                     QStringList tokens = output.split(" ");
                     iddata.append( "("+tokens[0]+tokens[1]+")");
                }

                output = lsblk.readLine();
            }

            foreach(QString each,iddata)
            {
                item += each+" ";
            }

            returnList.append(item);
    #endif
        }

        return returnList;
}

bool DiskWriter_unix::checkIfUSB(QString device) {
#ifdef Q_OS_LINUX
    QProcess lssize;
    lssize.start(QString("cat /sys/block/%1/removable").arg(device), QIODevice::ReadOnly);
    lssize.waitForStarted();
    lssize.waitForFinished();
    QString s = lssize.readLine();
    if (s.toInt() == 1) return true;
    return false;
#else
    QProcess lssize;
        lssize.start(QString("diskutil info %1").arg(device), QIODevice::ReadOnly);
        lssize.waitForStarted();
        lssize.waitForFinished();

        QString s = lssize.readLine();
        while (!lssize.atEnd()) {
             if (s.contains("Protocol:") && ( s.contains("USB") || s.contains("Secure Digital"))) {
                 return true;
             }
             s = lssize.readLine();
        }

        return false;
#endif
}

bool DiskWriter_unix::checkIsMounted(QString device)
{
    bool mounted = false;
    QProcess chkmount;
    chkmount.start("mount",QIODevice::ReadOnly);
    chkmount.waitForStarted();
    chkmount.waitForFinished();

    QString mount = chkmount.readLine();
    while (!chkmount.atEnd() && ! mounted) {
        mount = mount.trimmed(); // Odd trailing whitespace
        mount = mount.split(QRegExp("\\s+")).first();
        mounted = mount.indexOf(device) >= 0;
        mount = chkmount.readLine();
    }

    return mounted;
}

QStringList DiskWriter_unix::getDeviceNamesFromSysfs()
{
    QStringList names;

    QDir currentDir("/sys/block");
    currentDir.setFilter(QDir::Dirs);

    QStringList entries = currentDir.entryList();
    foreach (QString device, entries) {
        // Skip "." and ".." dir entries
        if (device == "." || device == "..") {
            continue;
        }

        if (device.startsWith("mmcblk") || device.startsWith("sd")) {
            QProcess* process = new QProcess();
            process->start("fdisk -l");
            process->waitForFinished();
            QString output =  process->readAll();
            if (output.contains(device)) {

                names << device;
            }

        }
    }

    return names;
}

#if defined(Q_OS_LINUX)
quint64 DiskWriter_unix::driveSize(const QString& device) const
{
    blkid_probe pr;

    pr = blkid_new_probe_from_filename(qPrintable(device));
    if (!pr) {
        return -1;
    }

    blkid_loff_t size = blkid_probe_get_size(pr);
    blkid_free_probe(pr);
    return size;
}

QStringList DiskWriter_unix::getPartitionsInfo(const QString& device) const
{
    blkid_probe pr;
    blkid_partlist ls;
    int nparts, i;
    QStringList partList;

    pr = blkid_new_probe_from_filename(qPrintable(device));
    if (!pr) {
        return partList;
    }

    ls = blkid_probe_get_partitions(pr);
    if (ls == NULL) {
        blkid_free_probe(pr);
        return partList;
    }

    nparts = blkid_partlist_numof_partitions(ls);
    if (nparts < 0) {
        blkid_free_probe(pr);
        return partList;
    }

    for (i = 0; i < nparts; i++) {
         blkid_partition par = blkid_partlist_get_partition(ls, i);
         QString partition;
         QTextStream stream(&partition);
         stream << "#" << blkid_partition_get_partno(par) << " - ";
         stream << " " << blkid_partition_get_size(par)*512/(1024*1024.0) << "MB";

         partList << partition;
    }

    blkid_free_probe(pr);
    return partList;
}
#endif
