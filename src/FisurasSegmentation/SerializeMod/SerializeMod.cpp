//
// SerializeMod
// Main
//

#include "pch.h"
#include "Config.h"
#include "Serialize.h"
#include <iostream>
#include <cmdlineopt.hpp> 
#include "../common/globals.h"

using namespace cmdlineopt;
using namespace std;

int main(int argc, char* argv[]) {

	// Debugging -> Command Arguments:
	// --input=C:/Users/User/Proyectos/data/Samples_Segmentation --output=C:/Users/User/Proyectos/data/Segmentation --verbose
	CmdLineOpt opt(argc, argv);
	opt.Parse();
	
	globals::verbose_mode = opt.Verbose();
	if (globals::verbose_mode) opt.Show();

	static string Folder_with_RAW_pictures = opt.Input();
		// "C:/Users/User/Proyectos/data/Samples_Segmentation";
	static string Folder_with_Procceced_pictures = opt.Output();
		// "C:/Users/User/Proyectos/data/Segmentation";


	//--------------------------------------------------------------------------------------------------
	// Crea las imagenes con las que va a entrenar la RED.
	// las toma del directorio de origen <Folder_with_RAW_pictures> definida en config.h
	// si ya EXISTE el directorio de destino <Folder_with_Procceced_pictures> definido en config.h da por supuesto que
	// ya estan creadas y pasa de largo.
	Serialize To_disk(Folder_with_RAW_pictures, Folder_with_Procceced_pictures);
}

