#ifndef SETTING_H
#define SETTING_H

#include <iostream>
#include <vector>
#include <libusb-1.0/libusb.h>

class Setting {
    public:
        Setting(const libusb_interface_descriptor *desc, libusb_device_handle *handle);
        ~Setting();

        unsigned char *get_protocoll();
        const libusb_endpoint_descriptor *get_endpoint_descriptor_by_index(uint8_t index);

    private:
        const libusb_interface_descriptor *desc = NULL;
        libusb_device_handle *handle = NULL;
        unsigned char data[256];
};

#endif