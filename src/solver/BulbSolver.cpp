/*
    Made by Alexander Odom for Assignment 1 for CS 447
*/

#include "BulbSolver.h"
#include <cstdlib>

void BulbSolver::solve()
{
    configuration = io.read();
    std::size_t counter = 0;
    std::size_t maxCount = configuration -> getSwitchCount();
    maxCount = maxCount * maxCount;
    while(!configuration -> valid())
    {
        std::vector<std::size_t> offBulbs = configuration -> offBulbs();
        configuration -> flipSwitch(offBulbs[rand() % offBulbs.size()], (rand() & 1) + 1);
        if(counter++ > maxCount)
        {
            break;
        }
    }
    io.write(configuration, counter);
}

void BulbSolver::solve(std::string inputFile, std::string outputFile)
{
    configuration = io.read(inputFile);
    std::size_t counter = 0;
    std::size_t maxCount = configuration -> getSwitchCount();
    maxCount = maxCount * maxCount;
    while(!configuration -> valid())
    {
        std::vector<std::size_t> offBulbs = configuration -> offBulbs();
        configuration -> flipSwitch(offBulbs[rand() % offBulbs.size()], (rand() & 1) + 1);
        if(counter++ > maxCount)
        {
            break;
        }
    }
    io.write(configuration, counter, outputFile);
}

void BulbSolver::solveGraph(std::string inputFile, std::string outputFile)
{
    configuration = io.read(inputFile);
    Graph_t graph = Graph_t(configuration);
    graph.makeGraph();
    int problemSwitch = graph.solve();
    if(problemSwitch == 0)
    {
        if(configuration -> valid())
        {
            io.write(configuration, outputFile);
        }
    }
    else
    {
        io.write(problemSwitch, outputFile);
    }
}