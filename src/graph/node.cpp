/*
    Made by Alexander Odom for Assignment 1 for CS 447
*/

#include "node.h"

Node_t::Node_t(bool on_)
{
    on = on_;
}

void Node_t::addPath(Node_t* node)
{
    paths.push_back(node);
}

bool Node_t::isOn()
{
    return on;
}

std::list<Node_t*> Node_t::getPaths()
{
    return paths;
}