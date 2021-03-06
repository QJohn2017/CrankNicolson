import CrankNicolson as cn
import utility as util
import sys

#example potentials
def noPotential(x):
	return 0.0

def potentialWell(x):
	if (x < 0.300 or x > 0.600):
        	return 100	
	return 0.0

def hamonicalPotential(x):
	omega = 10
	return 0.5 * omega ** 2 * (x - 0.5)**2

outfile = open("ProperbilityFlux.dat", "w")

#set the current solver for the crank nicolson algorithm here the non linear hamiltonian solver to solve soliton waves
simulation.setSolver(cn.NonLinearHamiltonianSolver(simulation, potentialWell, 0.01))

#add a new Gaussian wave to the simulation with the width of 50 at the position 400 and with wavevector length of 50000
simulation.addWave(cn.GaussianWave(100.0, 500.0, 50000.0))

#add a stream density observable
simulation.addFilter(cn.ProperbilityFluxObservable(outfile))

#write the plot file
util.plot.writeStaticPlotScript("ProperbilityFlux.static.plot", "ProperbilityFlux.dat", 1)

