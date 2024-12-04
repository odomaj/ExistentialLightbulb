/*
    Made by Alexander Odom for Assignment 1 for CS 447
*/

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <cstdint>
#include <vector>

#include "../bulb/BulbConfig.h"

#ifndef IO_H_
#define IO_H_

class IO
{
    public:
    IO(){}
    std::shared_ptr<BulbConfig_t> read();
    std::shared_ptr<BulbConfig_t> read(const std::string& filename);
    void write(std::shared_ptr<BulbConfig_t> configuration, std::size_t counter);
    void write(std::shared_ptr<BulbConfig_t> configuration, std::size_t counter, const std::string& filename);
    void write(std::shared_ptr<BulbConfig_t> configuration);
    void write(std::shared_ptr<BulbConfig_t> configuration, const std::string& filename);
    void write(int problemSwitch, const std::string& filename);
    void printBulbs(std::shared_ptr<BulbConfig_t> configuration);
    void printOffBulbs(std::shared_ptr<BulbConfig_t> configuration, std::ostream& out);
};

#endif