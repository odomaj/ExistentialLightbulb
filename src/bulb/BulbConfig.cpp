/*
    Made by Alexander Odom for Assignment 1 for CS 447
*/

#include "BulbConfig.h"
#include <iostream>

bool operator==(bulb::switch_t switch1, bulb::switch_t switch2)
{
    return switch1.on == switch2.on;
}

bool operator!=(bulb::switch_t switch1, bulb::switch_t switch2)
{
    return switch1.on != switch2.on;
}

void bulb::switch_t::flip()
{
    on = !on;
}

bool bulb::bulb_t::isOn()
{
    return badSwitch1Position != *switch1 || badSwitch2Position != *switch2;
}

BulbConfig_t::BulbConfig_t(std::size_t switchCount_, std::size_t bulbCount_)
{
    switchCount = switchCount_;
    bulbCount = bulbCount_;
    switches = new bulb::switch_t[switchCount];
    bulbs = new bulb::bulb_t[bulbCount];
}

BulbConfig_t::BulbConfig_t(std::shared_ptr<BulbConfig_t> toCopy)
{
    switchCount = toCopy -> switchCount;
    bulbCount = toCopy -> bulbCount;
    switches = new bulb::switch_t[switchCount];
    bulbs = new bulb::bulb_t[bulbCount];
    for(int i = 0; i < switchCount; i++)
    {
        switches[i] = toCopy -> switches[i];
    }
    for(int i = 0; i < bulbCount; i++)
    {
        bulbs[i] = toCopy -> bulbs[i];
    }
}

BulbConfig_t::~BulbConfig_t()
{
    delete[] switches;
    delete[] bulbs;
}

bool BulbConfig_t::valid()
{
    for(int i = 0; i < bulbCount; i++)
    {
        if(!bulbs[i].isOn())
        {
            return false;
        }
    }
    return true;
}

std::vector<std::size_t> BulbConfig_t::offBulbs()
{
    std::vector<std::size_t> offBulbs;
    for(std::size_t i = 0; i < bulbCount; i++)
    {
        if(!bulbs[i].isOn())
        {
            offBulbs.push_back(i);
        }
    }
    return offBulbs;
}

void BulbConfig_t::flipSwitch(std::size_t bulbIndex, std::size_t switchNumber)
{
    if(switchNumber == 1)
    {
        bulbs[bulbIndex].switch1 -> flip();
    }
    else if(switchNumber == 2)
    {
        bulbs[bulbIndex].switch2 -> flip();
    }
}

std::size_t BulbConfig_t::getSwitchCount()
{
    return switchCount;
}