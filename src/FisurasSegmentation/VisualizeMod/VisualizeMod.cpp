//
// VisualizeMod
// Main
//

#include <iostream>

#include "pch.h"
#include <cmdlineopt.hpp> 

// 
#include "Config.h"
#include "../common/globals.h"
#include "Tiramisu.h"
#include "Visualize.h"


using namespace cmdlineopt;
using namespace std;

int main(int argc, char* argv[]) {
    std::cout << "Visualize\n";

	// --input=C:/Users/User/Proyectos/data/Positive --prefix="" --verbose
	CmdLineOpt opt(argc, argv);
	opt.Parse();

	globals::verbose_mode = opt.Verbose();
	if (globals::verbose_mode) opt.Show();

	string Folder_with_JPGs = opt.Input();
	string prefix = "";
	opt.Parse("prefix", prefix);

	string modelfn = opt.Model();

	//--------------------------------------------------------------------------------------------------
	// Configuracion de la RED, se puede toquetear los FEATURES y los LAYERS
	Tiramisu net(1 /*CHANNEL_IN*/, 3 /*FEATURES*/, 4 /*LAYERS*/);

	//--------------------------------------------------------------------------------------------------
	if (globals::verbose_mode) cout << net << endl;
	//--------------------------------------------------------------------------------------------------
	// Si existe un entrenamiento previo arranca desde ahi, sino empieza desde cero/
	try {
		std::cout << "Try to Load <model.pt> from Disk..." << std::endl;
		torch::load(net, "model.pt");
	}
	catch (...) {
		std::cout << "MODEL Not Found..." << std::endl;
		exit(-1);
	}
	//--------------------------------------------------------------------------------------------------


	Visualize<Tiramisu> VISVISUALIZAR(Folder_with_JPGs, net);

	return 0;
}
