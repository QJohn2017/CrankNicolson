#pragma once

#include <string>
#include <vector>

#include "SimulationParameter.h"

class SimulationExecutor
{
public:
    SimulationExecutor(const std::string& filename);
    SimulationExecutor(const SimulationParameter& params, const std::string& scriptFile);

private:
    void run();

    std::vector<std::pair<SimulationParameter, std::string>> simulations;
};
