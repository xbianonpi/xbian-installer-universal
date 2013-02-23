#include "version.h"
#include "sstream"
#include "md5.h"
#include "algorithm"

version::version(QXmlStreamReader& xml)
{
    xml.readNext();

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "version")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
             if(xml.name() == "name") versionName = xml;
             if(xml.name() == "locations") mirrors = parseMirrors(xml);
             if(xml.name() == "md5") md5 = xml;
        }
    }
}

vector<string> parseMirrors(string locations) {
    vector<string> v;
    stringstream ss;
    char endChar = ";";
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
    if (md5sum == md5.digestFile(this->getArchiveName())) return true;
    else return false;
}

string version::getArchiveName() {
    string s (versionName);
    replace(s.begin(),s.end()," ","");
    stringstream ss;
    ss << "XBian" << s << ".tar.gz";
    return ss.str();
}
