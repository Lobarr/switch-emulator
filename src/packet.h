#pragma once
#include <iostream>
#include <string>


class Packet {
public:
	Packet();
	Packet(std::string raw);
	Packet(const Packet &old);

	void set_preamable(std::string input);
	std::string get_preamable() const;

	void set_mac_dest(std::string input);
	std::string get_mac_dest() const;

	void set_mac_src(std::string input);
	std::string get_mac_src() const;

	void set_vlan(std::string input);
	std::string get_vlan() const;
	int vlan_tag();
	int priority();
	std::string vlan_identifier();

	void set_payload_length(int input);
	int get_payload_length() const;

	void set_payload(std::string input);
	std::string get_payload() const;

	void set_crc(std::string input);
	std::string get_crc() const;

	void set_raw(std::string input);
	std::string get_raw() const;

private:
	std::string preamable;
	std::string mac_dest;
	std::string mac_src;
	std::string vlan;
	int payload_length;
	std::string payload;
	std::string crc;
	std::string raw;
};