import CrankNicolson as cn
import utility as util
import sys

#example potentials
def noPotential(x):
	return 0.0

outfile = open("ExpectationValue.dat", "w")

#set the current solver for the crank nicolson algorithm here the non linear hamiltonian solver to solve soliton waves
simulation.setSolver(cn.LinearHamiltonianSolver(simulation, noPotential))

#add a new Gaussian wave to the simulation with the width of 50 at the position 400 and with wavevector length of 50000
simulation.addWave(cn.GaussianWave(100.0, 500.0, 50000.0))

#add a observable for the simulation. In this case the observable is the Properbility which gets writen on stdout
simulation.addFilter(cn.ProperbilityObservable(outfile))

#add also an observable for the potential only writes ones to outfile at the start of the simulation
simulation.addFilter(cn.PotentialObservable(outfile, noPotential))

#write the plot file
util.plot.writeStaticPlotScript("ExpectationValue.static.plot", "ExpectationValue.dat", 1)

