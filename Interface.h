#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <vector>
#include <libusb-1.0/libusb.h>
#include "Setting.h"

class Interface {
    public:
        Interface(const libusb_interface *iface, uint8_t i, libusb_device_handle *handle);
        ~Interface();

        Interface *load_interface_descriptor();
        Interface *load_altsetting();

        Setting *get_setting_by_index(uint8_t index);

        uint8_t get_num_altsetting() {return interface->num_altsetting;};
        uint8_t get_bNum_Enpoints() {return desc->bNumEndpoints;};

    private:
        const libusb_interface *interface = NULL;
        uint8_t index;
        libusb_device_handle *handle = NULL;
        const libusb_interface_descriptor *desc = NULL;
        std::vector<Setting> set;
};

#endif