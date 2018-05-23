#include "logger.h"
#include <iomanip>


Logger::Logger(std::string fileName){
    f.open(fileName);
}

Logger::~Logger(){
    f.close();
}

void Logger::log(Interrupt t){
    mu.lock();
    // console output
    std::cout << "[" << std::put_time(std::localtime(&t.timestamp), "%c %Z") << "]"
    << std::setw(15) 
    << "src: "
    << t.mac_src
    << std::setw(15)
    << "dst: "
    << t.mac_dest 
    << std::endl;

    // log file
    f << "[" << std::put_time(std::localtime(&t.timestamp), "%c %Z") << "]"
    << std::setw(15) 
    << "src: "
    << t.mac_src
    << std::setw(15)
    << "dst: "
    << t.mac_dest 
    << std::endl;
    mu.unlock();
}

void Logger::log(Packet p){
    time_t t = std::time(NULL);
    mu.lock();
    // console output
    std::cout <<  "[" << std::put_time(std::localtime(&t), "%c %Z") << "]" 
    << std::setw(10)
    << "src: " 
    << p.get_mac_src()
    << std::setw(10)
    << "dst: "
    << p.get_mac_dest()
    << std::setw(15)
    << "payload: "
    << p.get_payload()
    << std::endl;

    // log file
    f <<  "[" << std::put_time(std::localtime(&t), "%c %Z") << "]" 
    << std::setw(10)
    << "src: " 
    << p.get_mac_src()
    << std::setw(10)
    << "dst: "
    << p.get_mac_dest()
    << std::setw(15)
    << "payload: "
    << p.get_payload()
    << std::endl;

    mu.unlock();
}