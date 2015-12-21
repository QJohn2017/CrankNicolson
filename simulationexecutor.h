#pragma once

#include <string>
#include <vector>

#include "SimulationParameter.h"

/**
 * @brief The SimulationExecutor class load a setting file and execute the simulations with its parameter.
 */
class SimulationExecutor
{
public:
    /**
     * @brief SimulationExecutor Loads the given file by its filename and execute the simulations.
     * @param filename The filename to load the parameter from.
     */
    SimulationExecutor(const std::string& filename);

    /**
     * @brief SimulationExecutor Loads the given file by its filename and execute the simulations.
     * @param params The parameter to run the simulatios with.
     * @param scriptFile The script file to run the simulation with.
     */
    SimulationExecutor(const SimulationParameter& params, const std::string& scriptFile);

private:
    void run();

    std::vector<std::pair<SimulationParameter, std::string>> simulations;
};
