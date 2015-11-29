def writeStaticPlotScript(filename, datafile, frame):
	with open(filename, "w") as f:
		f.write("set terminal png\n")
		f.write("set output '" + str(filename) + ".png '\n")
		f.write("set yrange[-1:1]\n")
		f.write("plot \"" + str(datafile) + "\" index (" + str(frame) +
			") with lines, \"" + str(datafile) + "\" index(0) with lines\n")

def writeAnimatedPlotScipt(filename, datafile, size):
	with open(filename, "w") as f:
		f.write("set terminal gif animate delay 1\n")
		f.write("set output '" + filename + ".gif'\n")
		f.write("stats '" + str(datafile) + "' nooutput\n")
		f.write("set yrange [-1:1]\n")
		f.write("do for [i=1:int(" + str(size) + ")] {\n")
		f.write("\tplot \"" + str(datafile) + "\" index (i) with lines, \"" + str(datafile) + "\" index(0) with lines\n")
		f.write("}")
