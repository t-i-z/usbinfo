#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <vector>
#include <libusb-1.0/libusb.h>

#include "Interface.h"

class Config {
    public:
        Config(libusb_device *dev, uint8_t i, libusb_device_handle *handle);
        ~Config();

        Interface *get_interface_by_index(size_t index);
        Config *load_config_descriptor();
        Config *load_interfaces();

        uint8_t get_bNumInterfaces() {return config->bNumInterfaces;};

    private:
        libusb_device *device = NULL;
        uint8_t index;
        libusb_device_handle *handle = NULL;
        libusb_config_descriptor *config;
        std::vector<Interface> interfaces;
};

#endif