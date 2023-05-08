#include <libusb-1.0/libusb.h>
#include "Storage.h"

Storage::Storage(){

};

Storage::~Storage(){

};


Storage *Storage::set_vendorId(uint16_t vendorId) {
    this->vendorId = vendorId;
    return this;
};


Storage *Storage::set_productId(uint16_t productId) {
    this->productId = productId;
    return this;
};


Storage *Storage::set_ep_desc(const libusb_endpoint_descriptor *ep_desc) {
    this->ep_desc = ep_desc;
    return this;
};


uint16_t Storage::get_vendorId() {
    return this->vendorId;
};


uint16_t Storage::get_productId() {
    return this->productId;
};


const libusb_endpoint_descriptor *Storage::get_ep_desc() {
    return this->ep_desc;
};