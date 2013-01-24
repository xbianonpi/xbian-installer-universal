#ifndef MAC_DISK_H
#define MAC_DISK_H

#include "string"

using namespace std;

class mac_disk
{
public:
    mac_disk(string FsLocation, string MountLocation, long TotalSizeInMB);
private:
    string fsLocation;
    string mountLocation;
    long totalSizeInMB;
};

#endif // MAC_DISK_H
