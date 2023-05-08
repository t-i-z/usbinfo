#include <string>
#include <iostream>
#include <libusb-1.0/libusb.h>

#include "Setting.h"

Setting::Setting(const libusb_interface_descriptor *desc, libusb_device_handle *handle) {
    this->desc = desc;
    this->handle = handle;
};


Setting::~Setting() {
};

unsigned char *Setting::get_protocoll(){
    std::cout << "setting::get_protocoll..." << std::endl;

    libusb_get_string_descriptor_ascii(handle, desc->iInterface, data, sizeof(data));

    return this->data;
}


const libusb_endpoint_descriptor *Setting::get_endpoint_descriptor_by_index(uint8_t index) {
    return &this->desc->endpoint[index];
};
