#include <libusb-1.0/libusb.h>
#include <iostream>
#include <vector>

#include "Interface.h"
#include "Setting.h"


Interface::Interface(const libusb_interface *iface, uint8_t i, libusb_device_handle *handle) {
    this->interface = iface;
    this->index = i;
    this->handle = handle;
};


Interface::~Interface() {
};


Interface *Interface::load_interface_descriptor(){
    std::cout << "interface::load_interface_descriptor..." << std::endl;
    desc = &interface->altsetting[index];
    return this;
};


Interface *Interface::load_altsetting(){
    std::cout << "interface::load_altsetting..." << std::endl;
    for (uint8_t i = 0; i < interface->num_altsetting; i++) {
        Setting *altset = new Setting(&interface->altsetting[i], handle);
        set.push_back(*altset);
    }
    return this;
}


Setting *Interface::get_setting_by_index(uint8_t index){
    std::cout << "interface::get_setting_by_index..." << std::endl;
    return &set.at(index);
};