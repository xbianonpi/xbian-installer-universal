//#ifdef Q_WS_MAC
#include "mac_functions.h"
#include <iostream>
#include "sstream"
#include "stdio.h"

mac_functions::mac_functions()
{

}

vector<mac_disk> mac_functions::mac_GetDisks()
{
    int cnt = 0;
    vector<mac_disk> disks;
    vector<string> disksLocation;
    vector<string> disksMountLocation;
    vector<long> diskSizeInMB;
    FILE * fp ;

    // Getting diskLocation's
    char cmd1[] = "df | grep '/Volumes/*' | awk '{print $1}'";
    char path1[PATH_MAX];
    fp = popen(cmd1, "r");
    while ( fgets( path1, PATH_MAX, fp ) != NULL ) {
        stringstream buffer;
        buffer << path1 << endl;
        disksLocation.push_back(buffer.str());
        cnt++;
    }

    pclose(fp);


    // Getting sizeInMB's
    char cmd2[] = "df -k | grep '/Volumes/*' | awk '{print $2}'";
    char path2[PATH_MAX];
    fp = popen(cmd2, "r");
    while ( fgets( path2, PATH_MAX, fp ) != NULL ) {
        stringstream buffer;
        buffer << path2 << endl;
        long sizeInMB = (atol(buffer.str().c_str()) / 1024);
        diskSizeInMB.push_back(sizeInMB);
    }

    pclose(fp);


    // Getting diskLocation's
    char cmd3[] = "df | grep '/Volumes/*' | awk '{print $9}'";
    char path3[PATH_MAX];
    fp = popen(cmd3, "r");
    while ( fgets( path3, PATH_MAX, fp ) != NULL ) {
        stringstream buffer;
        buffer << path3 << endl;
        disksMountLocation.push_back(buffer.str());
    }

    pclose(fp);

    for(int i = 0; i < cnt; i++) {
        mac_disk disk(disksLocation.at(i), disksMountLocation.at(i), diskSizeInMB.at(i));
        disks.push_back(disk);
    }

    return disks;
}

//#endif
