#include "mac_disk.h"
#include <ctype.h>
#include "sstream"
#include <string.h>
#include "iostream"


mac_disk::mac_disk(string FsLocation, string MountLocation, long TotalSizeInMB)
{
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
