#include "mac_disk.h"
#include <ctype.h>
#include "sstream"
#include <string>
#include "iostream"
#include <algorithm>


mac_disk::mac_disk(string FsLocation, string MountLocation, long TotalSizeInMB)
{
    FsLocation.erase(std::remove(FsLocation.begin(), FsLocation.end(), '\n'), FsLocation.end());
    MountLocation.erase(std::remove(MountLocation.begin(), MountLocation.end(), '\n'), MountLocation.end());

    fsLocation = FsLocation;
    mountLocation = MountLocation;
    totalSizeInMB = TotalSizeInMB;
}

int mac_disk::getDiskNumber()
{
    int cnt = 0;
    char s = 's';
    stringstream ss;
    for (char c : fsLocation) {
        if (c == s) cnt++;
        if (isdigit(c) && cnt < 2) ss << c;
    }

    int i = atoi(ss.str().c_str());
    return i;
}

string mac_disk::getFsLocation() {
    return fsLocation;
}

string mac_disk::getMountLocation() {
    return this->mountLocation;
}

long mac_disk::getTotalSizeInMB() {
    return totalSizeInMB;
}

