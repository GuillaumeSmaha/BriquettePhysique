#include "Application.h"

using namespace Ogre;


Application * Application::_instance = NULL;

void Application::createSingleton()
{
	if (_instance == NULL)
	{
		_instance = new Application();
	}
}

Application * Application::getSingletonPtr()
{
	if (_instance == NULL)
	{
		_instance = new Application();
	}
	return _instance;
}

Application & Application::getSingleton()
{
	if (_instance == NULL)
	{
		_instance = new Application();
	}
	return *_instance;
}

void Application::destroySingleton()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}



Application::Application(void)
{
	this->root = NULL;
	this->debugOverlay = NULL;
	
#ifdef _DEBUG
	this->resourcesCfg = "resources_d.cfg";
	this->pluginsCfg = "plugins_d.cfg";
#else
	this->resourcesCfg = "resources.cfg";
	this->pluginsCfg = "plugins.cfg";
#endif

	this->shutDown = false;
	this->isStatsOn = false;
}


Application::~Application(void)
{
	std::cout << "-" << std::endl << "Stop	application !!" << std::endl;
	
	PlayerControls::destroySingleton();
	ListenerInputManager::destroySingleton();
	ListenerFrame::destroySingleton();
	ListenerWindow::destroySingleton();
}

bool Application::start(void)
{
	Utils::logFileInit("error.log");

	// construct Ogre::Root
	this->root = new Ogre::Root(this->pluginsCfg);

	// load the ressources
	this->loadRessources();

	// restore the config or show the configuration dialog and
	if (!this->root->showConfigDialog())
		return false;
		
	//Create Window Singleton
	ListenerWindow::createSingleton("Briquette Physique");

	// get the generic SceneManager
	GestSceneManager::createSingleton(this->root);

	// Initialisation des ressources
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	// create the scene graph
	this->initSceneGraph();

	// init the input manager and create the listeners
	this->initListeners();

	// activate debugging overlay
	this->debugOverlay = OverlayManager::getSingleton().getByName("Core/DebugOverlay");

	// On affiche l'overlay
	this->showDebugOverlay(false);


	// start the scene rendering (main loop)
	this->root->startRendering();

	return true;
}

void Application::loadRessources(void)
{
	// setup resources
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(this->resourcesCfg);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}
}


void Application::initListeners(void)
{	
	//Create InputManager Singleton
	ListenerInputManager::createSingleton();
	
	//Create Keyboard Singleton
	ListenerKeyboard::createSingleton();
	
	//Create Mouse Singleton
	ListenerMouse::createSingleton();
	
	//Create Frame Singleton
	ListenerFrame::createSingleton();
	
    //create the collision system
    ListenerCollision::createSingleton();

	//Update the size of window and mouse window size
	ListenerWindow::getSingletonPtr()->windowResized(ListenerWindow::getSingletonPtr()->getRenderWindow());

	//Add signals
	ListenerWindow::getSingletonPtr()->signalWindowClosed.add(&ListenerFrame::shutdown, ListenerFrame::getSingletonPtr());
	ListenerFrame::getSingletonPtr()->signalFrameRendering.add(&ListenerKeyboard::capture, ListenerKeyboard::getSingletonPtr());
	ListenerFrame::getSingletonPtr()->signalFrameRendering.add(&ListenerMouse::capture, ListenerMouse::getSingletonPtr());
}

void Application::initSceneGraph(void)
{
    Ogre::Entity* ogreHead = GestSceneManager::getSceneManager()->createEntity("Head", "ogrehead.mesh");
 
    Ogre::SceneNode* headNode = GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode();
    headNode->attachObject(ogreHead);
    GestSceneManager::getSceneManager()->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
	GestSceneManager::getSceneManager()->setAmbientLight(Ogre::ColourValue::White);

    Ogre::Light* l = GestSceneManager::getSceneManager()->createLight("MainLight");
    l->setPosition(0,0,0);
    Ogre::SceneNode *nodeLight1 = GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode("NodeLight1");
    nodeLight1->attachObject(l);
    
    Ogre::Camera * camera = GestSceneManager::getSceneManager()->createCamera("mainCam");
    camera->setPosition(Ogre::Vector3(90, 25, 90));
    camera->lookAt(GestSceneManager::getSceneManager()->getRootSceneNode()->getPosition());

    Ogre::Viewport* viewPort = ListenerWindow::getSingletonPtr()->getRenderWindow()->addViewport(camera, 0);
    viewPort->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f));
    camera->setAspectRatio(Ogre::Real(viewPort->getActualWidth()) / Ogre::Real(viewPort->getActualHeight()));

}


void Application::updateStats(void *)
{
	static String currFps = "Current FPS: ";
	static String avgFps = "Average FPS: ";
	static String bestFps = "Best FPS: ";
	static String worstFps = "Worst FPS: ";
	static String tris = "Triangle Count: ";
	static String batches = "Batch Count: ";

	// update stats when necessary
	try {
		OverlayElement* guiAvg = OverlayManager::getSingleton().getOverlayElement("Core/AverageFps");
		OverlayElement* guiCurr = OverlayManager::getSingleton().getOverlayElement("Core/CurrFps");
		OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement("Core/BestFps");
		OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("Core/WorstFps");

		const RenderTarget::FrameStats& stats = ListenerWindow::getSingletonPtr()->getRenderWindow()->getStatistics();
		guiAvg->setCaption(avgFps + StringConverter::toString(stats.avgFPS));
		guiCurr->setCaption(currFps + StringConverter::toString(stats.lastFPS));
		guiBest->setCaption(bestFps + StringConverter::toString(stats.bestFPS)
			+" "+StringConverter::toString(stats.bestFrameTime)+" ms");
		guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS)
			+" "+StringConverter::toString(stats.worstFrameTime)+" ms");

		OverlayElement* guiTris = OverlayManager::getSingleton().getOverlayElement("Core/NumTris");
		guiTris->setCaption(tris + StringConverter::toString(stats.triangleCount));

		OverlayElement* guiBatches = OverlayManager::getSingleton().getOverlayElement("Core/NumBatches");
		guiBatches->setCaption(batches + StringConverter::toString(stats.batchCount));

		OverlayElement* guiDbg = OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
		guiDbg->setCaption(debugText);
	}
	catch(...) { /* ignore */ }
}

void Application::showDebugOverlay(bool show)
{
	if (debugOverlay)
	{
		if (show)
			this->debugOverlay->show();
		else
			this->debugOverlay->hide();
	}
}

void Application::killApplication()
{
    this->setShutDown(true);
    ListenerFrame::getSingletonPtr()->shutdown();
}
