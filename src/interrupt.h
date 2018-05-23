#pragma once
#include "packet.h"
#include <iostream>
#include <ctime>

struct Interrupt {
    //?
    Interrupt(Packet p){
        mac_src = p.get_mac_src();
        mac_dest = p.get_mac_dest();
        time_t temp = std::time(NULL);
        timestamp = temp;
    } 

    //!
    std::string mac_dest;
	std::string mac_src;  
    time_t timestamp;  
};