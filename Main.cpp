#include <iostream>
#include "Examples/Automata/Simulation.h"
#include <fstream>
#include <cstdint>
//using namespace rng;
/**
 * @author Timothy Van Slyke
 *
 * Run a simulation example to demonstrate what the library algorithms can do.
 *
 * To show the simulation (batteries not included folks), run the included python script on the output file.
 *
 *
 * @return exit code
 *
 */
int main(void)
{


	// use uint64_t instead of size_t because the python script expects a uint64...
	// number of food instances
	const uint64_t numFood = 16;
	// number of automata
	const uint64_t numAut = 32;
	// number of updates each generation
	const uint64_t updatesPerSim = 500;
	// number of generations
	const uint64_t numGenerations = 3;
	// boundaries for the simulation region
	const double xmin = -100;
	const double xmax = 100;
	const double ymin = -100;
	const double ymax = 100;

	// file to store simulation information to be visualized.
	std::string simFileName = "/home/tim/Projects/simData1.bin";

	// simulation object
	Simulation<numAut, numFood> simulation(xmin, xmax, ymin, ymax);

	// binary file to write to for visualization
	std::ofstream outFile(simFileName, std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);

	// put some parameters at the beginning of the file
	outFile.write(reinterpret_cast<const char *>(&numFood), sizeof(uint64_t));
	outFile.write(reinterpret_cast<const char *>(&numAut), sizeof(uint64_t));
	outFile.write(reinterpret_cast<const char *>(&updatesPerSim), sizeof(uint64_t));
	outFile.write(reinterpret_cast<const char *>(&numGenerations), sizeof(uint64_t));
	outFile.write(reinterpret_cast<const char *>(&xmin), sizeof(double));
	outFile.write(reinterpret_cast<const char *>(&xmax), sizeof(double));
	outFile.write(reinterpret_cast<const char *>(&ymin), sizeof(double));
	outFile.write(reinterpret_cast<const char *>(&ymax), sizeof(double));

	// send this frame to the output file
	simulation.pack(outFile);

	// iterate over each generation
	for(auto i = 0u; i < numGenerations; ++i)
	{
		// iterate over each update frame
		for(auto j = 0u; j < updatesPerSim; ++j)
		{
			// update
			simulation.update(0.001);
			// send this frame to the output file
			simulation.pack(outFile);
		}
		// calculate fitness using genetic diversity as a measure
		simulation.setFitnesses(true);
		// go to the next generation
		simulation.nextGeneration();
		// show the generation count
		std::cout << "Generation " << i << std::endl;
	}
	// flush the output file
	outFile << std::flush;
	outFile.close();


	return 0;
}
