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



Application::Application(void)
{
	this->root = NULL;
	this->sceneMgr = NULL;

#ifdef _DEBUG
	this->resourcesCfg = "resources_d.cfg";
	this->pluginsCfg = "plugins_d.cfg";
#else
	this->resourcesCfg = "resources.cfg";
	this->pluginsCfg = "plugins.cfg";
#endif

    this->listenerMouse = NULL;
    this->listenerKeyboard = NULL;
    this->listenerFrame = NULL;
    this->listenerWindow = NULL;

	this->shutDown = false;

	this->isStatsOn = false;
}


Application::~Application(void)
{
	std::cout << "-" << std::endl << "Stop	application !!" << std::endl;
}

bool Application::start(void)
{
	Utils::logFileInit("error.log");

	// construct Ogre::Root
	this->root = new Ogre::Root(this->pluginsCfg);

	// load the ressources
	this->loadRessources();

	// restore the config or show the configuration dialog and
	//if(! this->root->restoreConfig() && ! this->root->showConfigDialog())
	if (!this->root->showConfigDialog())
		return false;

	// initialise the system, create the default rendering window
	this->listenerWindow = new ListenerWindow(this->root, "Briquette");

	// get the generic SceneManager
	this->sceneMgr = this->root->createSceneManager(Ogre::ST_GENERIC);

	// Initialisation des ressources
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	// create the scene graph
	this->initSceneGraph();

	// init the input manager and create the listeners
	this->initListeners();

	// activate debugging overlay
	debugOverlay = OverlayManager::getSingleton().getByName("Core/DebugOverlay");

	// On affiche l'overlay
	showDebugOverlay(false);



	// start the scene rendering (main loop)

	this->root->startRendering();

	return true;
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

		const RenderTarget::FrameStats& stats = this->listenerWindow->getRenderWindow()->getStatistics();
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
	// Init the input system
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	this->listenerWindow->getRenderWindow()->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	this->inputManager = OIS::InputManager::createInputSystem(pl);
	this->listenerFrame = new ListenerFrame(this->root);

	this->listenerWindow->signalWindowClosed.add(&ListenerFrame::shutdown, this->listenerFrame);


	this->listenerMouse = new ListenerMouse(this->inputManager);
	this->listenerKeyboard = new ListenerKeyboard(this->inputManager);


	this->listenerWindow->setMouseControl(this->listenerMouse);
	this->listenerWindow->windowResized(this->listenerWindow->getRenderWindow());


    this->listenerFrame->signalFrameRendering.add(&ListenerMouse::capture, this->listenerMouse);
	this->listenerFrame->signalFrameRendering.add(&ListenerKeyboard::capture, this->listenerKeyboard);

}

void Application::initSceneGraph(void)
{
	this->sceneMgr->setAmbientLight(Ogre::ColourValue::White);

}

void Application::showDebugOverlay(bool show)
{
	if (debugOverlay)
	{
		if (show)
			debugOverlay->show();
		else
			debugOverlay->hide();
	}
}
