#include <libusb-1.0/libusb.h>
#include <iostream>
#include <vector>

#include "Config.h"
#include "Interface.h"


Config::Config(libusb_device *device, uint8_t i, libusb_device_handle *handle) {
    this->device = device;
    this->index = i;
    this->handle = handle;
};


Config::~Config() {
};


Config *Config::load_config_descriptor(){
    std::cout << "config::load_config_descriptor..." << std::endl;
    int ret = libusb_get_config_descriptor(device, index, &config);
    if (LIBUSB_SUCCESS != ret) {
        std::cout << "failed to get config descriptor" << std::endl;
        return NULL;
    }
    return this;
};


Config *Config::load_interfaces() {
    std::cout << "config::load_interfaces..." << std::endl;
    for (uint8_t i = 0; i < config->bNumInterfaces; i++) {
        Interface *iface = new Interface(&config->interface[i], i, handle);
        interfaces.push_back(*iface);
    }
    std::cout << "interfaces.size() " << interfaces.size() << std::endl << std::flush;
    return this;
};


Interface *Config::get_interface_by_index(size_t index) {
    return &interfaces.at(index);
}