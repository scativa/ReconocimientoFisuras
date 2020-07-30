//
// Tensorfiles
// Main
//

#include "pch.h"
#include "Config.h"
#include "CementDataset.h"
#include <iostream>
#include <cmdlineopt.hpp> 
#include "../common/globals.h"

using namespace cmdlineopt;
using namespace std;

int main(int argc, char* argv[]) {
	cout << "tensorfilesMod" << endl;

	// Debugging -> Command Arguments:
	// --input=C:/Users/User/Proyectos/data/Segmentation --prefix="" --verbose
	CmdLineOpt opt(argc, argv);
	opt.Parse();

	globals::verbose_mode = opt.Verbose();
	if (globals::verbose_mode) opt.Show();

	static string Folder_with_Procceced_pictures = opt.Input();
	string prefix = "";
	opt.Parse("prefix",prefix);

	//--------------------------------------------------------------------------------------------------
	// Crea los DATASET de entrenamiento y testeo, cada corrida que se hace del programa crea uno distinto.
	// Sobreescribe
	//--------------------------------------------------------------------------------------------------
	auto train_dataset = torch::data::datasets::CementDataset(
		Folder_with_Procceced_pictures,
		classes, prefix
	);

}
