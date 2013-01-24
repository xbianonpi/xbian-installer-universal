#include "mac_disk.h"

mac_disk::mac_disk(string FsLocation, string MountLocation, long TotalSizeInMB)
{
    fsLocation = FsLocation;
    mountLocation = MountLocation;
    totalSizeInMB = TotalSizeInMB;
}
