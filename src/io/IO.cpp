/*
    Made by Alexander Odom for Assignment 1 for CS 447
*/

#include "IO.h"

std::shared_ptr<BulbConfig_t> IO::read(const std::string& filename)
{
    std::ifstream in;
    in.open(filename);
    if(!in)
    {
        throw "FILE DOES NOT EXIST: " + filename;
    }

    std::size_t switchCount;
    std::size_t bulbCount;

    in >> switchCount;
    in >> bulbCount;

    std::shared_ptr<BulbConfig_t> bulbConfig = std::shared_ptr<BulbConfig_t>(new BulbConfig_t(switchCount, bulbCount));

    for(int i = 0; i < switchCount; i++)
    {
        bulbConfig -> switches[i].on = 0;
    }

    for(int i = 0; i < bulbCount; i++)
    {
        bulb::bulb_t *current_bulb = &(bulbConfig -> bulbs[i]);
        int switch1, switch2;
        in >> switch1 >> switch2;
        
        bulb::switch_t temp;
        temp.on = 1;
        current_bulb -> badSwitch1Position = temp;
        current_bulb -> badSwitch2Position = temp;
        if(switch1 < 0)
        {
            (current_bulb -> badSwitch1Position).on = 0;
            switch1 *= -1;
        }
        if(switch2 < 0)
        {
            (current_bulb -> badSwitch2Position).on = 0;
            switch2 *= -1;
        }
        current_bulb -> switch1 = &(bulbConfig -> switches[switch1 - 1]);
        current_bulb -> switch2 = &(bulbConfig -> switches[switch2 - 1]);
    }

    in.close();

    return bulbConfig;
}

std::shared_ptr<BulbConfig_t> IO::read()
{
    std::size_t switchCount;
    std::size_t bulbCount;

    std::cin >> switchCount;
    std::cin >> bulbCount;

    std::shared_ptr<BulbConfig_t> bulbConfig = std::shared_ptr<BulbConfig_t>(new BulbConfig_t(switchCount, bulbCount));

    for(int i = 0; i < switchCount; i++)
    {
        bulbConfig -> switches[i].on = 0;
    }

    for(int i = 0; i < bulbCount; i++)
    {
        bulb::bulb_t *current_bulb = &(bulbConfig -> bulbs[i]);
        int switch1, switch2;
        std::cin >> switch1 >> switch2;

        bulb::switch_t temp;
        temp.on = 1;
        current_bulb -> badSwitch1Position = temp;
        current_bulb -> badSwitch2Position = temp;
        if(switch1 < 0)
        {
            (current_bulb -> badSwitch1Position).on = 0;
            switch1 *= -1;
        }
        if(switch2 < 0)
        {
            (current_bulb -> badSwitch2Position).on = 0;
            switch2 *= -1;
        }
        current_bulb -> switch1 = &(bulbConfig -> switches[switch1 - 1]);
        current_bulb -> switch2 = &(bulbConfig -> switches[switch2 - 1]);
    }
    
    return bulbConfig;
}

void IO::write(std::shared_ptr<BulbConfig_t> configuration, std::size_t counter, const std::string& filename)
{
    std::ofstream out;
    out.open(filename);
    if(!out)
    {
        throw "FILE DOES NOT EXIST: " + filename;
    }

    if(configuration -> valid())
    {
        out << "configuration valid\nfound after " << counter << " switches\n";
    }
    else
    {
        out << "configuration not valid\nstopped after " << counter << " switches\n";
    }

    for(int i = 0; i < configuration -> switchCount; i++)
    {
        if(!configuration -> switches[i].on)
        {
            out << '-';
        }
        out << i+1 << ' ';
    }

    printOffBulbs(configuration, out);
    out.close();
}

void IO::write(std::shared_ptr<BulbConfig_t> configuration, std::size_t counter)
{
    if(configuration -> valid())
    {
        std::cout << "configuration valid\nfound after " << counter << " switches\n";
    }
    else
    {
        std::cout << "configuration not valid\nstopped after " << counter << " switches\n";
    }

    for(int i = 0; i < configuration -> switchCount; i++)
    {
        if(!configuration -> switches[i].on)
        {
            std::cout << '-';
        }
        std::cout << i+1 << ' ';
    }
    std::cout << '\n';
    printOffBulbs(configuration, std::cout);
}

void IO::write(std::shared_ptr<BulbConfig_t> configuration, const std::string& filename)
{
    std::ofstream out;
    out.open(filename);
    if(!out)
    {
        throw "FILE DOES NOT EXIST: " + filename;
    }

    if(configuration -> valid())
    {
        out << "configuration valid\n";
    }
    else
    {
        out << "configuration not valid\n";
    }

    for(int i = 0; i < configuration -> switchCount; i++)
    {
        if(!configuration -> switches[i].on)
        {
            out << '-';
        }
        out << i+1 << ' ';
    }

    printOffBulbs(configuration, out);
    out.close();
}

void IO::write(std::shared_ptr<BulbConfig_t> configuration)
{
    if(configuration -> valid())
    {
        std::cout << "configuration valid\n";
    }
    else
    {
        std::cout << "configuration not valid\n";
    }

    for(int i = 0; i < configuration -> switchCount; i++)
    {
        if(!configuration -> switches[i].on)
        {
            std::cout << '-';
        }
        std::cout << i+1 << ' ';
    }
    std::cout << '\n';
    printOffBulbs(configuration, std::cout);
}

void IO::write(int problemBulb, const std::string& filename)
{
    std::ofstream out;
    out.open(filename);
    if(!out)
    {
        throw "FILE DOES NOT EXIST: " + filename;
    }

    out << "problem has no valid configuration\nswitch " << problemBulb << " causes downstream effects to other bulbs when either on or off\n";

    out.close();
}

void IO::printBulbs(std::shared_ptr<BulbConfig_t> configuration)
{
    for(int i = 0; i < configuration -> bulbCount; i++)
    {
        bulb::bulb_t* currentBulb = &(configuration -> bulbs[i]);
        if(!currentBulb -> badSwitch1Position.on)
        {
            std::cout << '-';
        }
        std::cout << currentBulb -> switch1 - configuration -> switches + 1 << ' ';
        if(!currentBulb -> badSwitch2Position.on)
        {
            std::cout << '-';
        }
        std::cout << currentBulb -> switch2 - configuration -> switches + 1 << '\n';
        
    }
}

void IO::printOffBulbs(std::shared_ptr<BulbConfig_t> configuration, std::ostream& out)
{
    std::vector<std::size_t> offBulbs = configuration -> offBulbs();
    for(int i = 0; i < offBulbs.size(); i++)
    {
        bulb::bulb_t* currentBulb = &(configuration -> bulbs[offBulbs[i]]);
        if(!currentBulb -> badSwitch1Position.on)
        {
            out << '-';
        }
        out << currentBulb -> switch1 - configuration -> switches + 1 << ' ';
        if(!currentBulb -> badSwitch2Position.on)
        {
            out << '-';
        }
        out << currentBulb -> switch2 - configuration -> switches + 1 << '\n';
    }
}