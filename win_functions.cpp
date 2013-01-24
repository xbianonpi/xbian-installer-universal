#ifdef Q_MS_WIN
#include "win_functions.h"
#include <windows.h>
#include <winioctl.h>
#include "win_disk.h"


win_Functions::win_Functions()
{

}

void win_Functions::getWinLogicalDrives()
{
    // GetLogicalDrives returns 0 on failure, or a bitmask representing
    // the drives available on the system (bit 0 = A:, bit 1 = B:, etc)
    unsigned long driveMask = GetLogicalDrives();
    int i = 0;
    ULONG pID;

    cboxDevice->clear();

    while (driveMask != 0)
    {
        if (driveMask & 1)
        {
            // the "A" in drivename will get incremented by the # of bits
            // we've shifted
            char drivename[] = "\\\\.\\A:\\";
            drivename[4] += i;
            if (checkDriveType(drivename, &pID))
            {
                cboxDevice->addItem(QString("[%1:\\]").arg(drivename[4]), (qulonglong)pID);
            }
        }
        driveMask >>= 1;
        cboxDevice->setCurrentIndex(0);
        ++i;
    }
}
#endif
