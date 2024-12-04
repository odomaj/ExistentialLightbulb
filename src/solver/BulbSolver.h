/*
    Made by Alexander Odom for Assignment 1 for CS 447
*/

#include <string>
#include <memory>

#include "../bulb/BulbConfig.h"
#include "../io/IO.h"
#include "../graph/graph.h"

#ifndef BULBSOLVER_H_
#define BULBSOLVER_H_

class BulbSolver
{
    public:
    BulbSolver(){}
    void solve();
    void solve(std::string inputFile, std::string outputFile);
    void solveGraph(std::string inputFile, std::string outputFile);
    private:
    std::shared_ptr<BulbConfig_t> configuration;
    IO io;
};

#endif