#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
#include <vector>
#include <libusb-1.0/libusb.h>

class Storage {
    public:
        Storage();
        ~Storage();

        Storage *set_vendorId(uint16_t vendorId);
        Storage *set_productId(uint16_t productId);
        Storage *set_ep_desc(const libusb_endpoint_descriptor *ep_desc);

        uint16_t get_vendorId();
        uint16_t get_productId();
        const libusb_endpoint_descriptor *get_ep_desc();

    private:
        uint16_t vendorId;
        uint16_t productId;
        const libusb_endpoint_descriptor *ep_desc;
};

#endif