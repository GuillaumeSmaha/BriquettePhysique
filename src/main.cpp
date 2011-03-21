#include "main.h"
#include "Application.h"

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
		return 1;
	}

	return 0;
}
