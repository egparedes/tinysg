#include <xode\xode.h>

#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
	std::string filename;
	if (argc > 1) filename = argv[1];
	else {
		std::cout << "Usage: scene_test scenedescription.xml" << std::endl;
		return -1;
	}
	
	// Create a new scene object
	xode::sceneS s;
	
	// Read in the scene description
	readSceneDescription(&s, filename);	
}
