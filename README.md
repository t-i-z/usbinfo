# usbinfo

collect infomation about attached usb devices


# build

g++ main.cpp USBDevice.cpp Config.cpp Interface.cpp Setting.cpp Storage.cpp -o usbinfo -l:libusb-1.0.a -ludev

# usage

./usbinfo
