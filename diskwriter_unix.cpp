#include "diskwriter_unix.h"

#include <QDebug>

#include <QApplication>
#include <QDir>
#include <QProcess>
#include <QRegularExpression>
#include <QTextStream>

#include "zlib.h"

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
#elif defined(Q_OS_LINUX)
    QProcess* ls = new QProcess();
    ls->start("/bin/ls", QStringList() << "/dev" << "-m");
    ls->waitForFinished();

    QString output =  ls->readAll();

    // *** this variable
    output = output.replace("\n"," ");

    // *** LIST OD ENTRIES TO UNMOUNT:
    QStringList entries = output.split(", ");
    QMutableStringListIterator lsi(entries);
    while (lsi.hasNext())
        lsi.next().prepend("/dev/");

    // *** QStringList partitions = entries.filter(QRegularExpression(device.append("*")));

    // *** this variable
    QStringList partitions = entries.filter(QRegularExpression(device.append("*")));


    QProcess unmount;

    // *** partitions change to only one//sd
    // partions place in function is qstring&
    //unmount.start(QString("umount"), partitions , QIODevice::ReadOnly);

    unmount.start(QString("umount"), partitions , QIODevice::ReadOnly);

    unmount.waitForStarted();
    if(!unmount.waitForFinished()) {
        qDebug() << "Unmount failed:" << unmount.errorString();
    }
    unmount.waitForReadyRead();
    qDebug() << "Unmount stdout:" << unmount.readAllStandardOutput();
    qDebug() << "Unmount stderr:" << unmount.readAllStandardError();
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
            QProcess* process = new QProcess();
            process->start("fdisk -l | grep " + s);
            process->waitForFinished();
            QString output =  process->readAll();
            output = output.split(",")[0];
            output = output.replace("Disk " + s + ": ","");
            output = output.replace("\n","");
            s += " (" + output + ")";
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
    if(device.indexOf("mmcblk")==0) return true;
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
    QProcess* process = new QProcess();
    process->start("fdisk -l");
    process->waitForFinished();
    QString output =  process->readAll();
    foreach (QString device, entries) {
        // Skip "." and ".." dir entries
        if (device == "." || device == "..") {
            continue;
        }

        if (device.startsWith("mmcblk") || device.startsWith("sd")) {
            if (output.contains(device)) {
                names << device;
            }
        }
    }

    return names;
}
