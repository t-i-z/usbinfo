#ifndef USBDEVICE_H
#define USBDEVICE_H

#include <iostream>
#include <vector>
#include <libusb-1.0/libusb.h>
#include "Config.h"

class USBDevice {
    public:
        USBDevice(libusb_device *device);
        ~USBDevice();

        USBDevice *open_device();
        void close_device();

        Config *get_config_by_index(size_t index);
        USBDevice *load_device_descriptor();
        USBDevice *load_device_configurations();

        uint16_t get_vendorId() { return desc.idVendor; };
        uint16_t get_productId() { return desc.idProduct; };
        uint8_t get_bNumConfiguration() { return desc.bNumConfigurations; };
 
    private:
        libusb_device *dev = NULL;
        libusb_device_descriptor desc;
        libusb_device_handle *handle = NULL;

        std::vector<Config> configs;

};

#endif