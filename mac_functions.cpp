#include "mac_functions.h"
#include <iostream>
#include "sstream"
#include "stdio.h"
#include "stdlib.h"

int processID;
long imageSize;
int timePassed;

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
        if (diskSizeInMB.at(i) < 70000) {
        mac_disk disk(disksLocation.at(i), disksMountLocation.at(i), diskSizeInMB.at(i));
        disks.push_back(disk);
        }
    }

    return disks;
}


void mac_functions::unmountDisk(mac_disk disk)
{    
    // Unmounting device
    for (int i = 0; i < 5; i++) {
        stringstream ss;
        ss << "sudo diskutil unmount /dev/disk" << disk.getDiskNumber() << "s" << i;
        system(ss.str().c_str());
    }
}

void mac_functions::restoreImage(string image, mac_disk disk)
{
    cout << "DEBUG: PID:" << disk.getDiskNumber() << endl;

    // Getting the size of the image that is going to be restored
    stringstream ss;
    ss << "ls -Al " << image <<" | awk '{print $5}'";
    imageSize = system(ss.str().c_str());

    // Starting the restore
    stringstream cmd_DD;
    cmd_DD << "sudo dd if=" << image << " of=/dev/rdisk" << disk.getDiskNumber() << " bs=1m &";

    unmountDisk(disk);
    system(cmd_DD.str().c_str());
    usleep(500000);

    // Getting the process id of DD
    stringstream cmd_PID;
    cmd_PID << "ps aux | grep 'dd if=" << image << " of=/dev/rdisk" << disk.getDiskNumber() << " bs=1m' | awk '{print $2}'";
    cout << cmd_PID.str() << endl;
    char path[PATH_MAX];
    FILE * fp = popen(cmd_PID.str().c_str(), "r");
    while ( fgets( path, PATH_MAX, fp ) != NULL ) {
        stringstream buffer;
        buffer << path << endl;
        processID = atoi(buffer.str().c_str());
        break;
    }

    cout << "DEBUG: PID of DD:" << processID << endl;
}

 int mac_functions::getRestoreProgress()
 {
     stringstream ss;
     ss << "kill -0 " << processID << " 2>/dev/null; echo $?";
     int i = system (ss.str().c_str());
     timePassed++;

     if (i != 0) {
         ss << "nohup kill -s SIGINFO " << processID << " 2>/tmp/process 1>/dev/null;";
         system(ss.str().c_str());

         ss << "cat /tmp/process | grep -a bytes | awk '{print $1}'";
         long newCopied = system(ss.str().c_str());

         return (newCopied*100)/imageSize;
     }

    return -1;
 }





