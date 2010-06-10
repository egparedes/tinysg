#ifdef _MSC_VER
//#include "vld.h"
#endif

#include <sceneml.h>

#include <string>
#include <memory>
#include <iostream>


using namespace sceneml;

int main(int argc, char* argv[])
{	
	ScenePtr scene;
	
	while (1) {
		SceneDirector sceneDirector;
		std::auto_ptr<XMLSceneBuilder> xmlSceneBuilder;
		
		if (argc == 2) {
			xmlSceneBuilder.reset( new XMLSceneBuilder(argv[1]) );
		} else {
			xmlSceneBuilder.reset( new XMLSceneBuilder("twopa10.scene") );
		}	
	
		sceneDirector.SetSceneBuilder( xmlSceneBuilder.get() );
		sceneDirector.ConstructScene();

		scene = sceneDirector.GetScene();
		scene.get()->update();	
	
		scene.get()->setMutableValue("q_src_1", M_PI/5);
		scene.get()->update();
		
		float *leak = new float;
	}
	return EXIT_SUCCESS;	
}
