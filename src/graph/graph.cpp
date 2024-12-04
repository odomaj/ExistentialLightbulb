/*
    Made by Alexander Odom for Assignment 1 for CS 447
*/

#include <string.h>

#include "graph.h"

Graph_t::Graph_t(std::shared_ptr<BulbConfig_t> configuration_)
{
    configuration = configuration_;
    nodeCount = configuration -> getSwitchCount();
    onNodes = new Node_t[nodeCount];
    offNodes = new Node_t[nodeCount];
    for(int i = 0; i < nodeCount; i++)
    {
        onNodes[i] = Node_t(true);
        offNodes[i] = Node_t(false);
    }
}

Graph_t::~Graph_t()
{
    delete[] onNodes;
    delete[] offNodes;
}

void Graph_t::makeGraph()
{
    for(int i = 0; i < configuration -> bulbCount; i++)
    {
        int switch1 = configuration -> bulbs[i].switch1 - configuration -> switches;
        int switch2 = configuration -> bulbs[i].switch2 - configuration -> switches;
        bool switch1On = configuration -> bulbs[i].badSwitch1Position.on;
        bool switch2On = configuration -> bulbs[i].badSwitch2Position.on;
        connectNodes(switch1, switch2, switch1On, switch2On);
    }
}

void Graph_t::connectNodes(int index1, int index2, bool on1, bool on2)
{
    if(on1)
    {
        // !on1 || !on2 bulb is on
        if(on2)
        {
            // on1 -> !on2 for bulb to be on
            onNodes[index1].addPath(&offNodes[index2]);
            // on2 -> !on1 for bulb to be on
            onNodes[index2].addPath(&offNodes[index1]);
        }
        // !on1 || on2 bulb is on
        else
        {
            // on1 -> on2 for bulb to be on
            onNodes[index1].addPath(&onNodes[index2]);
            // !on2 -> !on1 for bulb to be on
            offNodes[index2].addPath(&offNodes[index1]);
        }
    }
    else
    {
        // on1 || !on2 bulb is on
        if(on2)
        {
            // !on1 -> !on2 for bulb to be on
            offNodes[index1].addPath(&offNodes[index2]);
            // on2 -> on1 for bulb to be on
            onNodes[index2].addPath(&onNodes[index1]);
        }
        // on1 || on2 bulb is on
        else
        {
            // !on1 -> on2 for bulb to be on
            offNodes[index1].addPath(&onNodes[index2]);
            // !on2 -> on1 for bulb to be on
            offNodes[index2].addPath(&onNodes[index1]);
        }
    }
}

// returns 0 if there is a solution, otherwise returns the the problematic switch's number (starting from 1)
int Graph_t::solve()
{
    // set the first node to either 0 or 1, loop through for each node that is not set by another node
    // whenerer ^^^ occurs perform a graph search for both possibilities
    // once all of the states have been set a valid configuration has been found
    // if a branch arrives at a value that was previously set the branch fails
    // if both initial branches fail there is no solution
    
    char* visitedNodes = new char[nodeCount];
    for(int i = 0; i < nodeCount; i++)
    {
        visitedNodes[i] = UNVISITED;
    }

    int problemNode = splitSolve(0, visitedNodes);

    if(problemNode == -1)
    {
        for(int i = 0; i < nodeCount; i++)
        {
            if(visitedNodes[i] == ON)
            {
                configuration -> switches[i].on = true;
            }
            else if(visitedNodes[i] == OFF)
            {
                configuration -> switches[i].on = false;
            }
            else
            {
                delete[] visitedNodes;
                return -2;
            }
        }
    }

    delete[] visitedNodes;
    return problemNode + 1;
}

int Graph_t::splitSolve(int nodeIndex, char* visitedNodes)
{
    char* onVisitedNodes = new char[nodeCount];
    char* offVisitedNodes = new char[nodeCount];
    std::list<Node_t*> onNodesToVisit;
    std::list<Node_t*> offNodesToVisit;

    memcpy(onVisitedNodes, visitedNodes, nodeCount * sizeof(char));
    memcpy(offVisitedNodes, visitedNodes, nodeCount * sizeof(char));

    int problemNode = nodeIndex;

    if(solveNode(&onNodes[nodeIndex], onVisitedNodes, &onNodesToVisit) == -1)
    {
        problemNode = -1;
        memcpy(visitedNodes, onVisitedNodes, nodeCount * sizeof(char));
    }

    else if(solveNode(&offNodes[nodeIndex], offVisitedNodes, &offNodesToVisit) == -1)
    {
        problemNode = -1;
        memcpy(visitedNodes, onVisitedNodes, nodeCount * sizeof(char));
    }

    delete[] onVisitedNodes;
    delete[] offVisitedNodes;

    return problemNode;
}

int Graph_t::solveNode(Node_t* node, char* visitedNodes, std::list<Node_t*>* nodesToVisit)
{
    if(node -> isOn())
    {
        int nodeIndex = node - onNodes;
        if(visitedNodes[nodeIndex] == OFF)
        {
            return nodeIndex;
        }
        
        if(visitedNodes[nodeIndex] == UNVISITED)
        {
            std::list<Node_t*> newNodes = node -> getPaths();
            nodesToVisit -> splice(nodesToVisit -> end(), newNodes);
        }

        visitedNodes[nodeIndex] = ON;
        
        if(nodesToVisit -> empty())
        {
            return solveNextNode(visitedNodes);
        }
        Node_t* nextNode = nodesToVisit -> front();
        nodesToVisit -> pop_front();
        return solveNode(nextNode, visitedNodes, nodesToVisit);
    }
    
    else
    {
        int nodeIndex = node - offNodes;
        if(visitedNodes[nodeIndex] == ON)
        {
            return nodeIndex;
        }

        if(visitedNodes[nodeIndex] == UNVISITED)
        {
            std::list<Node_t*> newNodes = node -> getPaths();
            nodesToVisit -> splice(nodesToVisit -> end(), newNodes);
        }

        visitedNodes[nodeIndex] = OFF;

        if(nodesToVisit -> empty())
        {
            return solveNextNode(visitedNodes);
        }
        Node_t* nextNode = nodesToVisit -> front();
        nodesToVisit -> pop_front();
        return solveNode(nextNode, visitedNodes, nodesToVisit);
    }
}

int Graph_t::solveNextNode(char* visitedNodes)
{

    for(int i = 0; i < nodeCount; i++)
    {
        if(visitedNodes[i] == UNVISITED)
        {
            return splitSolve(i, visitedNodes);
        }
    }

    return -1;
}