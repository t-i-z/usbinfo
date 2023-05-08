#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <libusb-1.0/libusb.h>

#include "USBDevice.h"
#include "Storage.h"


int main() {

    libusb_device **devs;
    libusb_context *ctx;
    int ret, i;
    ssize_t cnt;

    //vector for storing result
    std::vector<Storage> store;

    ret = libusb_init(&ctx);
    if (ret < 0)
        return ret;

    cnt = libusb_get_device_list(ctx, &devs);
    printf("found %li devices\n", cnt);
    if (cnt < 0) {
        libusb_exit(ctx);
        return -1;
    }

    // collect information for all attached usb devices, if device can be opend

    for (i = 0; devs[i]; i++) {

        USBDevice *dev = new USBDevice(devs[i]);
        std::cout << std::endl << "----- " << +i << ".Device -----" << std::endl;
        
        if (dev->open_device()) {
            dev->load_device_descriptor()->load_device_configurations();
            
            for (int j = 0; j < dev->get_bNumConfiguration(); j++) {

                dev->get_config_by_index(j)->load_config_descriptor()->load_interfaces();
                
                for (int k = 0; k < dev->get_config_by_index(j)->get_bNumInterfaces(); k++) {

                    dev->get_config_by_index(j)->get_interface_by_index(k)->load_interface_descriptor()->load_altsetting();
                    
                    for (int l = 0; l < dev->get_config_by_index(j)->get_interface_by_index(k)->get_num_altsetting(); l++) {

                        unsigned char *data = dev->get_config_by_index(j)->get_interface_by_index(k)->get_setting_by_index(l)->get_protocoll();
                        std::cout << "Protocoll: " << reinterpret_cast<char*>(data) << std::endl;

                        // if ADB Device store result
                        // stored values are VendorId, ProductId, endpoint_descriptor

                        if (!strcmp((char *)data, "ADB Interface")) {
                            
                            for (uint8_t m = 0; m < dev->get_config_by_index(j)->get_interface_by_index(k)->get_bNum_Enpoints(); m++) {
                                Storage *st = new Storage();
                                st->set_vendorId(dev->get_vendorId());
                                st->set_productId(dev->get_productId());
                                st->set_ep_desc(dev->get_config_by_index(j)->get_interface_by_index(k)->get_setting_by_index(l)->get_endpoint_descriptor_by_index(m));
                                store.push_back(*st);
                            }
                        }
                    }
                }
            }
        }    
        else {
            std::cout << "----> could not open device..." << std::endl;
        }

        dev->close_device();
        delete dev;

    }

    libusb_exit(ctx);


    // print summary of collected ADB devices
    std::cout << std::endl << "----- List of ADB Devices with endpoints -----" << std::endl << std::endl;

    std::vector<Storage>::iterator it;

    for (it = store.begin(); it != store.end(); it++) {
        std::cout << "VendorId:ProductId -> " <<  std::setfill('0') << std::setw(4) << std::hex << it->get_vendorId()
                  << ":" << std::setfill('0') << std::setw(4) << std::hex << it->get_productId() << std::endl;
        std::cout << "      bEndpointAddress: " << "0x" << std::hex << +it->get_ep_desc()->bEndpointAddress << std::endl;
    }


}