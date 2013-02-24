#include "version.h"
#include "sstream"
#include "algorithm"
#include "string.h"
#include "iostream"
#include "QCryptographicHash"

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

bool version::checkMD5(QFile* file) {
    if(file->open(QIODevice::ReadOnly))
      {
        QCryptographicHash* hash;

        QString fileHash = hash->hash(file->readAll(),QCryptographicHash::Md5).toHex();
        file->close();
        cout << "Original MD5: " << this->md5 << endl;
        cout << "File MD5: " << fileHash.toStdString();
        if (this->md5 == fileHash.toStdString()) return true;
      }

    return false;
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
