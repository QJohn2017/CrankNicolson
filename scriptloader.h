#pragma once

#include <string>
#include <boost/filesystem.hpp>

#include "simulation.h"

/**
 * @brief The ScriptLoader class load all scripts from a directory and execute them for the given simulation.
 */
class ScriptExecutor {
public:
    /**
     * @brief ScriptLoader Load a script from a file and execute it.
     * @param simulation The current simulation.
     * @param scriptDir The directory with the python script inside.
     */
    ScriptExecutor(Simulation &simulation,
                 const std::string& scriptFile);

    /**
     * @brief ~ScriptLoader Destructor of the ScriptExecutor
     */
    ~ScriptExecutor();

private:
    std::vector<boost::filesystem::path> getScriptFiles(const std::string& dir);
};
