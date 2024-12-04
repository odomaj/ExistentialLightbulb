/*
    Made by Alexander Odom for Assignment 1 for CS 447
*/

#include <cstdint>
#include <vector>
#include <memory>

#ifndef BULBCONFIG_H_
#define BULBCONFIG_H_

namespace bulb
{
    typedef struct
    {
        bool on;
        void flip();
    } switch_t;

    typedef struct
    {
        switch_t *switch1;
        switch_t *switch2;
        switch_t badSwitch1Position;
        switch_t badSwitch2Position;
        bool isOn();
    } bulb_t;
}

bool operator==(bulb::switch_t switch1, bulb::switch_t switch2);
bool operator!=(bulb::switch_t switch1, bulb::switch_t switch2);

class BulbConfig_t
{
    public:
    BulbConfig_t(){}
    BulbConfig_t(std::size_t switchCount_, std::size_t bulbCount_);
    BulbConfig_t(std::shared_ptr<BulbConfig_t> toCopy);
    ~BulbConfig_t();
    bool valid();
    std::vector<std::size_t> offBulbs();
    void flipSwitch(std::size_t bulbIndex, std::size_t switchNumber);
    std::size_t getSwitchCount();
    friend class IO;
    friend class Graph_t;
    private:
    std::size_t switchCount;
    std::size_t bulbCount;
    bulb::switch_t *switches;
    bulb::bulb_t *bulbs;
};
#endif
