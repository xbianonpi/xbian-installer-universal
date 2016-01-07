How to compile
=================

##Linux
```
sudo apt-get install qt5-default
cd ~
git clone --depth 5 https://github.com/xbianonpi/xbian-installer-universal.git
cd xbian-installer-universal
cp Makefile.linux Makefile
make
```

The final file is XBian-installer

###To Run the installer
```
chmod +x XBian-installer
sudo ./XBian-installer
```

##Windows (cross-compiled on linux)

### Create cross-compiler
Install the dependencies
```
sudo apt-get install \
    autoconf automake autopoint bash bison bzip2 flex gettext\
    git g++ gperf intltool libffi-dev libgdk-pixbuf2.0-dev \
    libtool libltdl-dev libssl-dev libxml-parser-perl make \
    openssl p7zip-full patch perl pkg-config python ruby scons \
    sed unzip wget xz-utils 
```
For 64bit also install
```
sudo apt-get install g++-multilib libc6-dev-i386
```
To install the complier
```
cd ~ 
git clone https://github.com/mxe/mxe.git
cd mxe
make qtbase
```

### To Cross-compile
```
cd ~
git clone --depth 5 https://github.com/xbianonpi/xbian-installer-universal.git
cd ~/xbian-installer-universal
export PATH=$PATH:~/mxe/usr/bin/
~/mxe/usr/bin/i686-w64-mingw32.static-qmake-qt5
make
```

The final file is release/XBian-installer.exe