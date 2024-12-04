/*
    Made by Alexander Odom for Assignment 1 for CS 447
*/

#include <memory>
#include <list>

#include "node.h"
#include "../bulb/BulbConfig.h"

#ifndef GRAPH_H_
#define GRAPH_H_

class Graph_t
{
    public:
    Graph_t(){}
    Graph_t(std::shared_ptr<BulbConfig_t> configuration_);
    ~Graph_t();
    void makeGraph();
    int solve();
    private:
    const char ON = '1';
    const char OFF = '0';
    const char UNVISITED = 'u';
    std::shared_ptr<BulbConfig_t> configuration;
    std::size_t nodeCount;
    Node_t* onNodes;
    Node_t* offNodes;
    void connectNodes(int index1, int index2, bool on1, bool on2);
    int splitSolve(int nodeIndex, char* visitedNodes);
    int solveNode(Node_t* node, char* visitedNodes, std::list<Node_t*>* nodesToVisit);
    int solveNextNode(char* visitedNodes);
};

#endif