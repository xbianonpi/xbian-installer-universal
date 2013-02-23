#ifndef VERSION_H
#define VERSION_H

#include "string"
#include "vector"
#include "QXmlStreamReader"

using namespace std;

class version
{
public:
    version(QXmlStreamReader& xml);
    string getRandomMirror();
    string getVersionName();
    bool checkMD5(string md5);
    string getArchiveName();
private:
    string versionName;
    vector<string> mirrors;
    string md5;
};

#endif // VERSION_H
