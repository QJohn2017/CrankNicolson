import CrankNicolson as cn
import utility as util
import sys

#see https://en.wikipedia.org/wiki/Phonon
def phononPotential(x):
	off = 0
	omega = 2
	size = simulation.getParameter().atomCount
	index = int(x * size)
	atoms = simulation.getAtoms()
	if (index > 0 and index < size - 1):
		off = abs(atoms[index] - atoms[index - 1]) ** 2 + abs(atoms[index] - atoms[index + 1]) ** 2
	return 0.5 * omega**2 * off

def potentialWell(x):
	if (x < 0.300 or x > 0.700):
        	return 10 * 10**5
	return 0

def hamonicalPotential(x):
	omega = 10
	return 0.5 * omega ** 2 * (x - 0.5)

outfile = open("TestData.dat", "w")
#set the current solver for the crank nicolson algorithm here the non linear hamiltonian solver to solve soliton waves
simulation.setSolver(cn.NonLinearHamiltonianSolver(simulation, phononPotential, 0.001)) # 0.01

#add a new Gaussian wave to the simulation with the width of 50 at the position 400 and with wavevector length of 50000
simulation.addWave(cn.GaussianWave(50.0, 400.0, 50000.0))
#add a new Gaussian wave to the simulation with the width of 20 at the position 600 and with wavevector length of -50000
#simulation.addWave(cn.GaussianWave(20.0, 600.0, -50000.0))

#add a observable for the simulation. In this case the observable is the Properbility which gets writen on stdout
simulation.addFilter(cn.ProperbilityObservable(outfile)) #sys.stdout
#add also an observable for the potential only writes ones to stdout at the start of the simulation
#simulation.addFilter(cn.PotentialObservable(outfile, phononPotential)) #sys.stdout

#write the plot file
util.plot.writeStaticPlotScript("TestData.static.plot", "TestData.dat", 1)
util.plot.writeAnimatedPlotScipt("TestData.dynamic.plot", "TestData.dat", simulation.getParameter().iterations)
