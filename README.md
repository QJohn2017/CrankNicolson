# CrankNicolson

![Example soliton solution](doc/images/Soliton.Prop.dynamic.plot.gif)

This is a small project which implements the [Crank Nicolson method](https://en.wikipedia.org/wiki/Crank-Nicolson_method)
for one dimensional waves by solving the timedependent Schrödinger equation.

The project itself allows to dynamiclly script the wanted waves as python files
and define the wanted solvers.

## Example Green function solver.
```python
outfile = open("Green.dat", "w")

# add a new Gaussian wave to the simulation with the width of 50 
# at the position 400 and with wavevector length of 50000
simulation.addWave(cn.GaussianWave(100.0, 500.0, 50000.0))

# add the custom filter to the simulation
simulation.addFilter(GreenFunction(100, 0.1, outfile))
```
To specify a simulation define a json file with the simulation parameters
and the desired script to run.
```json
{
  "Simulation": {
    "iterations": "1000",
    "atoms": "1000",
    "dx": "0.0005",
    "dt": "0.00000008",
    "script": "scripts/solitonSimulation.py"
  }
}
```
then execute the program by ./cranknicolson --files "path to simulation parameters"

## Build
### Dependencies
  * Required
    - CMake > 2.8
    - Boost >= 1.55.0 (with Boost.Python)
    - Python 2.7
    - Python libraries
    - A compiler which is capable to compile c++11 (e.g. gcc >= 4.8)
  * (optional)
    - Doxygen >= 1.8.0
    
To generate the project solution run CMake.
