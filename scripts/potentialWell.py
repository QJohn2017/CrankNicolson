import CrankNicolson as cn
import utility as util
import sys

#example potentials
def potentialWell(x):
	if (x < 0.300 or x > 0.600):
        	return 100	
	return 0.0

outfile = open("PotentialWell.dat", "w")

#set the current solver for the crank nicolson algorithm here the non linear hamiltonian solver to solve soliton waves
simulation.setSolver(cn.LinearHamiltonianSolver(simulation, potentialWell))

#add a new Gaussian wave to the simulation with the width of 50 at the position 400 and with wavevector length of 50000
simulation.addWave(cn.GaussianWave(100.0, 500.0, 50000.0))

#add a observable for the simulation. In this case the observable is the Properbility which gets writen on stdout
simulation.addFilter(cn.ProperbilityObservable(outfile))

#add also an observable for the potential only writes ones to stdout at the start of the simulation
simulation.addFilter(cn.PotentialObservable(outfile, potentialWell)) #sys.stdout

#write the plot file
util.plot.writeStaticPlotScript("PotentialWell.static.plot", "PotentialWell.dat", 1)
util.plot.writeAnimatedPlotScipt("PotentialWell.dynamic.plot", "PotentialWell.dat", simulation.getParameter().iterations)

