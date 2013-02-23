#ifndef MAC_DISK_H
#define MAC_DISK_H

#include "string"

using namespace std;

class mac_disk
{
private:
    string fsLocation;
    string mountLocation;
    long totalSizeInMB;
public:
    mac_disk(string FsLocation, string MountLocation, long TotalSizeInMB);
    string getFsLocation();
    string getMountLocation();
    long getTotalSizeInMB();
    int getDiskNumber();
};

#endif // MAC_DISK_H
