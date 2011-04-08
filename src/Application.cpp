#include "Application.h"

using namespace Ogre;

template<> Application * ClassRootSingleton<Application>::_instance = NULL;


Application::Application() : ClassRootSingleton<Application>()
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


Application::~Application()
{
	std::cout << "-" << std::endl << "Stop	application !!" << std::endl;
		
	PlayerControls::destroySingleton();
	ListenerMouse::destroySingleton();
	ListenerKeyboard::destroySingleton();
	ListenerInputManager::destroySingleton();
	ListenerFrame::destroySingleton();
	ListenerWindow::destroySingleton();
    ListenerCollision::destroySingleton();
}

bool Application::start()
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
	ListenerWindow::createSingleton(this->root, "Briquette Physique");
		
	//Create Camera Singleton
	GestCamera::createSingleton();
		
	//Create Viewport Singleton
	GestViewport::createSingleton();

	// get the generic SceneManager
	GestSceneManager::createSingleton(this->root);

	// Initialisation des ressources
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	// init the input manager and create the listeners
	this->initListeners();

	// create the scene graph
	this->initSceneGraph();

	// init the scene
	this->initScene();

	// activate debugging overlay
	this->debugOverlay = OverlayManager::getSingleton().getByName("Core/DebugOverlay");

	// On affiche l'overlay
	this->showDebugOverlay(false);

	// start the scene rendering (main loop)
	this->root->startRendering();

	return true;
}

void Application::loadRessources()
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


void Application::initListeners()
{	
	//Create InputManager Singleton
	ListenerInputManager::createSingleton();
	
	//Create Keyboard Singleton
	ListenerKeyboard::createSingleton();
	
	//Create Mouse Singleton
	ListenerMouse::createSingleton();
	
	//Create Frame Singleton
    ListenerFrame::createSingleton(this->root);

    //create the collision system
    ListenerCollision::createSingleton();

	//Update the size of window and mouse window size
	ListenerWindow::getSingletonPtr()->windowResized(ListenerWindow::getSingletonPtr()->getRenderWindow());

	//Add signals
	ListenerWindow::getSingletonPtr()->signalWindowClosed.add(&ListenerFrame::shutdown, ListenerFrame::getSingletonPtr());
	ListenerFrame::getSingletonPtr()->signalFrameRendering.add(&ListenerKeyboard::capture, ListenerKeyboard::getSingletonPtr());
	ListenerFrame::getSingletonPtr()->signalFrameRendering.add(&ListenerMouse::capture, ListenerMouse::getSingletonPtr());

    PlayerControls::getSingletonPtr()->signalKeyPressed.add(&Application::onKeyPressed, this);
}

void Application::initSceneGraph()
{
	GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode(NODE_NAME_GROUPE_TABLE);
	GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode(NODE_NAME_GROUPE_BRIQUETTES);
	GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode(NODE_NAME_GROUPE_CAMERA);
}

void Application::initScene()
{
    //GestSceneManager::getSceneManager()->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
	//GestSceneManager::getSceneManager()->setAmbientLight(Ogre::ColourValue::White);

    GestSceneManager::getSceneManager()->createLight("MainLight");
    //Ogre::Light * l = GestSceneManager::getSceneManager()->createLight("MainLight");
    //l->setPosition(0,0,0);
    //Ogre::SceneNode *nodeLight1 = GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode("NodeLight1");
    //nodeLight1->attachObject(l);

    GestObj * gestObj = GestObj::getSingletonPtr();
    
    ObjTable * tableBackground = new ObjTable(2500.0, -500.0);
    ObjTable * table = new ObjTable();
   
    gestObj->setTableBackground(tableBackground);
    gestObj->setTable(table);
    
    for(int i = 0 ; i < 1 ; i++)
	{
		for(int j = 0 ; j < 1 ; j++)
		{
			Ogre::Vector3 vect(i, j, 50.0);
			gestObj->addBriquette(vect);
		}
    }
    
    CameraTarget * gestCamera = new CameraTarget("mainCam", GestObj::getSingletonPtr()->getTable()->getNode());
    
    this->idViewport = GestViewport::getSingletonPtr()->addViewport(gestCamera);
    
    GestCamera::getSingletonPtr()->addCamera(gestCamera);
    SelectionMouse::createSingleton(ListenerWindow::getSingletonPtr()->getRenderWindow());

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



void Application::onKeyPressed(Controls::Controls key){
    switch(key)
    {
        case Controls::QUIT :
            this->killApplication();
            break;

        default:
            break;
    }
}
