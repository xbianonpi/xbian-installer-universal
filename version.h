#ifndef VERSION_H
#define VERSION_H

#include "string"
#include "vector"
#include "QXmlStreamReader"

using namespace std;

class version
{
public:
    version(string name, string locations, string md5);
    string getRandomMirror();
    string getVersionName();
    bool checkMD5(string md5);
    string getArchiveName();
private:
    string versionName;
    vector<string> mirrors;
    string md5;
    void RemoveSpaces(char* source);
    vector<string> parseMirrors(string locations);
};

#endif // VERSION_H
