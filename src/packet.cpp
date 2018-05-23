#include "packet.h"
#include <iomanip>
#include <sstream>

Packet::Packet() {}

Packet::Packet(const Packet &old) {
	preamable = old.preamable;
	mac_dest = old.mac_dest;
	mac_src = old.mac_src;
	vlan = old.vlan;
	payload_length = old.payload_length;
	payload = old.payload;
	crc = old.crc;
}

Packet::Packet(std::string input) {
    set_raw(input);
    set_preamable(input.substr(0, 16));
    set_mac_dest(input.substr(16, input.length()).substr(0, 12));
    set_mac_src(input.substr(28, input.length()).substr(0, 12));
    set_vlan(input.substr(40, input.length()).substr(0, 8));
    set_payload_length(std::stoi(input.substr(48, input.length()).substr(0, 4)));
    set_payload(input.substr(52, input.length()).substr(0, get_payload_length()*2));
    set_crc(input.substr(52+(get_payload_length()*2), input.length()).substr(0, input.length()));
}

void Packet::set_preamable(std::string input) {
    preamable = input;
}

std::string Packet::get_preamable() const {
    return preamable;
}

void Packet::set_mac_dest(std::string input) {
    mac_dest = input;
}

std::string Packet::get_mac_dest() const {
    return mac_dest;
}

void Packet::set_mac_src(std::string input) {
    mac_src = input;
}
std::string Packet::get_mac_src() const {
    return mac_src;
}

void Packet::set_vlan(std::string input) {
    vlan = input;
}
std::string Packet::get_vlan() const {
    return vlan;
}
int Packet::priority() {
    if((int)vlan_identifier()[0] == 48) {
        return 0;
    } else if ((int)vlan_identifier()[0] == 50) {
        return 2;
    } else {
        throw "invalid priority";
    }
}

int Packet::vlan_tag(){
    return std::stoi(vlan_identifier().substr(1,vlan_identifier().length()));
}

std::string Packet::vlan_identifier() {
    return get_vlan().substr(4,get_vlan().length());
}

void Packet::set_payload_length(int input) {
    payload_length = input;
}
int Packet::get_payload_length() const {
    return payload_length;
}

void Packet::set_payload(std::string input) {
	payload = "";
	int c;
	for (int i = 0; i < input.length(); i += 2) {
        std::string temp = input.substr(i,2);
        char c = (char) (int)std::strtol(temp.c_str(), NULL, 16);
        payload += char(c);
	}
}

std::string Packet::get_payload() const {
    return payload;
}

void Packet::set_crc(std::string input) {
    crc = input;
}
std::string Packet::get_crc() const {
 return crc;
}

void Packet::set_raw(std::string input){
    raw = input;
}

std::string Packet::get_raw() const {
    return raw;
}