#include "simulationexecutor.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "scriptloader.h"
#include "simulation.h"

#include "nonlinearhamiltonian.h"

using namespace boost;
using namespace property_tree;

SimulationExecutor::SimulationExecutor(const std::string& filename) {
    ptree tree;
    json_parser::read_json(filename, tree);

    for (auto it = tree.begin(); it != tree.end(); ++it) {
        if (it->first == "Simulation") {
            const ptree& child = it->second;
            SimulationParameter params(child.get<double>("dx"),
                                       child.get<double>("dt"),
                                       child.get<int>("iterations"),
                                       child.get<int>("atoms"));
            simulations.push_back(std::pair<SimulationParameter, std::string>(params, child.get<std::string>("script")));
        }
    }

    run();
}

SimulationExecutor::SimulationExecutor(const SimulationParameter& params, const std::string& scriptFile) {
    simulations.push_back(std::pair<SimulationParameter, std::string>(params, scriptFile));

    run();
}

void SimulationExecutor::run() {
    for (std::pair<SimulationParameter, std::string> simul : simulations) {
        Simulation sim(simul.first, nullptr);
        ScriptExecutor(sim, simul.second);
    }
}
