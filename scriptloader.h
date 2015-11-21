#pragma once

#include <string>
#include <boost/filesystem.hpp>

#include "simulation.h"

/**
 * @brief The ScriptLoader class load all scripts from a directory and execute them for the given simulation
 */
class ScriptLoader {
public:
    /**
     * @brief ScriptLoader Load all scripts from a directory and execute the scripts insite
     * @param simulation The current simulation
     * @param scriptDir The directory with the python scripts insite
     */
    ScriptLoader(Simulation &simulation,
                 const std::string& scriptDir);

private:
    std::vector<boost::filesystem::path> getScriptFiles(const std::string& dir);
};
