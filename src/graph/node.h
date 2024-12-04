/*
    Made by Alexander Odom for Assignment 1 for CS 447
*/

#include <list>

#include "../bulb/BulbConfig.h"

class Node_t
{
    public:
    Node_t(){}
    Node_t(bool on_);
    void addPath(Node_t* node);
    std::list<Node_t*> getPaths();
    bool isOn();
    private:
    bool on;
    std::list<Node_t*> paths;
};