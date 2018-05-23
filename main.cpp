#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <mutex>
#include <chrono>
#include <atomic>
#include "src/interrupt.h"
#include "src/PriorityQueue.cpp"
#include "src/packet.cpp"
#include "src/logger.cpp"

std::queue<Packet> readCapture(std::string fileName);
void packets_reader(); // thread 1
void interrupt_handler(Interrupt t); // thread 2
void packets_handler(); // thread 3

//! global variables
std::queue<Packet> packets;
PriorityQueue vlan_101;
PriorityQueue vlan_100;
Logger logger("tmp/output.log");
std::atomic<bool> t1_done(false);
std::mutex m; //!synchronize variables between threads


/*
	! Compilation command
	? g++ -pthread -std=c++0x main.cpp -o main 
*/

int main() {
	try{
		std::thread t1(packets_reader);		
		std::thread t2(packets_handler);
		t1.join();
		t2.join();
	}catch(std::exception ex){
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}


std::queue<Packet> readCapture(std::string fileName){
	std::queue<Packet> packets;
	std::string raw;
	std::ifstream f(fileName);

	if(f.is_open()){
		while(getline(f, raw)){
			Packet p(raw);
			packets.push(p);
		}
		f.close();
	}else {
		throw "Unable to open file";
	}

	return packets;
}

void interrupt_handler(Interrupt t){
	logger.log(t);
}

void packets_reader(){
	m.lock();
	packets = readCapture("packets.capture");
	while(!packets.empty()){
		Packet p = packets.front();	
		if (p.priority() == 2){
			Interrupt t(p);
			std::thread i(interrupt_handler, t);
			i.join();
		}		
		if (p.vlan_tag() == 100){
			vlan_100.push(p);
		} else if(p.vlan_tag() == 101){
			vlan_101.push(p);
		} else {
			throw "Invalid VLAN";
		}
		packets.pop();
	}
	t1_done = true;
	m.unlock();
}

void packets_handler(){
	while(!t1_done) {} // wait till vlan queues are filled
	while(!vlan_100.isEmpty() && !vlan_101.isEmpty()){
		m.lock();
		if(!vlan_100.isEmpty()){
			logger.log(vlan_100.pop());
		}
		if(!vlan_101.isEmpty()){
			logger.log(vlan_101.pop());
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
		m.unlock();
	}
}