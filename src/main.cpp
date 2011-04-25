#include "main.h"

int main(void)
{
	std::cout << "\t\tApplication..." << std::endl;
	Application::createSingleton();

	std::cout << "pointeur Application::getSingletonPtr() = " << Application::getSingletonPtr() << std::endl;
	
	try
	{
	    Application::getSingletonPtr()->start();
		Application::destroySingleton();
	}
	catch( Ogre::Exception& e )
	{
		std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
		Application::destroySingleton();
		
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
