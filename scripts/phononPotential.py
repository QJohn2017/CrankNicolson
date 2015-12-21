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


outfile = open("Phonon.dat", "w")

#set the current solver for the crank nicolson algorithm here the non linear hamiltonian solver to solve soliton waves
simulation.setSolver(cn.LinearHamiltonianSolver(simulation, phononPotential)

#add a new Gaussian wave to the simulation with the width of 50 at the position 400 and with wavevector length of 50000
simulation.addWave(cn.GaussianWave(100.0, 500.0, 50000.0))

#add a observable for the simulation. In this case the observable is the Properbility which gets writen on stdout
simulation.addFilter(cn.ProperbilityObservable(outfile))

#add also an observable for the potential only writes ones to stdout at the start of the simulation
simulation.addFilter(cn.PotentialObservable(outfile, phononPotential)) #sys.stdout

#write the plot file
util.plot.writeStaticPlotScript("Phonon.static.plot", "Phonon.dat", 1)
util.plot.writeAnimatedPlotScipt("Phonon.dynamic.plot", "Phonon.dat", simulation.getParameter().iterations)
