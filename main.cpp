#include <iostream>
#include <complex>
#include <fstream>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/tokenizer.hpp>
#include <boost/token_functions.hpp>

#include "simulationexecutor.h"
#include "TridiagonalMatrix.h"

using namespace boost;
using namespace boost::program_options;

int main(int argc, char** argv) {
    options_description desc(
        "Crank Nicolson solver for one dimensional waves.\n"
        "This program solves the timedependent Schroedinger equation\n"
        "for one dimensional waves.\n"
        "The only parameter which is nessesary is the simulation file.\n"
        "This simulation file contains the data and\na path to a script to run a simulation.\n"
    );
    desc.add_options()
            ("help,h", "Show this help text")
            ("files,f", value<std::vector<std::string>>(), "Simulation files");

    variables_map vm;
    try {
        store(command_line_parser(argc, argv).options(desc).run(), vm);
        notify(vm);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        std::cout << desc << std::endl;
    }

    if (vm.count("help")) {
        desc.print(std::cout);
    }

    if (vm.count("files")) {
        std::vector<std::string> files = vm["files"].as<std::vector<std::string>>();
        for (auto file : files) {
            std::cout << "process file: " << file << std::endl;
            SimulationExecutor(file.c_str()); //only call constructor
        }
    }

    return 0;
}

