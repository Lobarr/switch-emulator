#pragma once
#include <iostream>
#include <fstream>
#include <mutex>
#include "interrupt.h"
#include "packet.h"

class Logger {
    public:
        Logger(std::string fileName);
        ~Logger();

        void log(Interrupt t);
        void log(Packet p);
    private:
        std::ofstream f;
        std::mutex mu;
};
