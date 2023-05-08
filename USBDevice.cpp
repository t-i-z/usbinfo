#include <libusb-1.0/libusb.h>
#include <iostream>
#include <vector>

#include "USBDevice.h"
#include "Config.h"


USBDevice::USBDevice(libusb_device *device) {
    dev = device;
};


USBDevice::~USBDevice() {

};


USBDevice *USBDevice::open_device() {
    std::cout << "USBDevice::open_device..." << std::endl;
    libusb_open(dev, &handle);
    if (handle) {
        return this;
    }
    return NULL;
}


void USBDevice::close_device() {
    std::cout << "USBDevice::close_device..." << std::endl;
    libusb_close(handle);
}


USBDevice *USBDevice::load_device_descriptor() {
    std::cout << "USBDevice::load_device_descriptor..." << std::endl;

    int ret;
   
    ret = libusb_get_device_descriptor(dev, &desc);
    if (ret < 0) {
        fprintf(stderr, "failed to get device descriptor");
    }

    return this;
};


USBDevice *USBDevice::load_device_configurations() {
    std::cout << "USBDevice::load_device_configuration..." << std::endl;

    for (uint8_t i = 0; i < desc.bNumConfigurations; i++) {
        Config *conf = new Config(dev, i, handle);
        configs.push_back(*conf);
    }

    return this;
};


Config *USBDevice::get_config_by_index(size_t index){

    return &configs.at(index);
}