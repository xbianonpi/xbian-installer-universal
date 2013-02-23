#include "version.h"
#include "sstream"
#include "md5.h"
#include "algorithm"
#include "string.h"

version::version(string name, string locations, string md5)
{
    this->versionName = name;
    this->mirrors = this->parseMirrors(locations);
    this->md5 = md5;
}

vector<string> version::parseMirrors(string locations)
{
    vector<string> v;
    stringstream ss;
    char endChar = ';';
    for (char c : locations) {
        if (c == endChar) { // We reached the end of the location
            v.push_back(ss.str());
            ss.str(string());
        } else ss << c;
    }

    v.push_back(ss.str());
    return v;
}

string version::getRandomMirror() {
    int random = rand()%mirrors.size();
    return mirrors[random];
}

string version::getVersionName() {
    return this->versionName;
}

bool version::checkMD5(string md5sum) {
    MD5 md5;

    string archiveName = this->getArchiveName();
    char *file = new char[archiveName.length() + 1];
    strcpy(file, archiveName.c_str());

    char *md5sumGiven = new char[md5sum.length() + 1];
    strcpy(md5sumGiven,md5sum.c_str());

    if (md5sumGiven == md5.digestFile(file)) return true;
    else return false;
}

string version::getArchiveName() {
    string str = versionName;

    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    this->RemoveSpaces(cstr);

    stringstream ss;
    ss << "XBian" << cstr << ".tar.gz";
    return ss.str();
}

void version::RemoveSpaces(char* source)
{
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;
}
