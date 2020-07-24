// SerializeMod.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include "Config.h"
#include "Serialize.h"
#include <iostream>
#include <cmdlineopt.hpp> 

using namespace cmdlineopt;
using namespace std;

int main(int argc, char* argv[]) {
	CmdLineOpt opt(argc, argv);
	opt.Parse();
	
	bool Verbose = opt.Verbose();
	if (Verbose) opt.Show();

	static string Folder_with_RAW_pictures = opt.Input();
		// "C:/Users/User/Proyectos/data/Samples_Segmentation";
	static string Folder_with_Procceced_pictures = opt.Output();
		// "C:/Users/User/Proyectos/data/Segmentation";


	//--------------------------------------------------------------------------------------------------
	// Crea las imagenes con las que va a entrenar la RED.
	// las toma del directorio de origen <Folder_with_RAW_pictures> definida en config.h
	// si ya EXISTE el directorio de destino <Folder_with_Procceced_pictures> definido en config.h da por supuesto que
	// ya estan creadas y pasa de largo.
	Serialize To_disk(Folder_with_RAW_pictures, Folder_with_Procceced_pictures, Verbose);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
