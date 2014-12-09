How to compile
=================

##Linux
```
sudo su
apt-get install libqt5widgets5 qt5-default qt5-qmake qtbase5-dev
cd ~
git clone --depth 5 https://github.com/xbianonpi/xbian-installer-universal.git
cd xbian-installer-universal
cp Makefile.linux Makefile
make
```

The final file is XBian-installer

##Windows (cross-compiled on linux)

### Create cross-compiler
```
sudo su
apt-get install autopoint intltool bison flex gperf ruby scons unzip pkg-config libffi6 libffi-dev
git clone https://github.com/mxe/mxe.git
cd ~
cd mxe
make qtbase
```

### Cross-compile
```
sudo su
cd ~/xbian-installer-universal
export PATH=$PATH:~/mxe/usr/bin/
~/mxe/usr/bin/i686-w64-mingw32.static-qmake-qt5
make
```

The final file is release/XBian-installer.exe
