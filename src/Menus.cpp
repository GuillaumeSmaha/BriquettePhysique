#include "Menus.h"
Menus::Menus()
{
    this->mouseControl=ListenerMouse::getSingletonPtr();
    this->keyControl=ListenerKeyboard::getSingletonPtr();
    this->pControl=PlayerControls::getSingletonPtr();

    this->mainWdw=NULL;
    //démarre le menusRenderer
    menusRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

    //prépare les différents groupes de ressources
    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

    //charge un scheme
    CEGUI::SchemeManager::getSingleton().create("SleekSpace.scheme");
    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");

    //enregistre les signaux sur la souris
    mouseControl->signalMousePressed.add(&Menus::mousePressed, this);
    mouseControl->signalMouseReleased.add(&Menus::mouseReleased, this);
    mouseControl->signalMouseMoved.add(&Menus::mouseMoved, this);

    //enregistre les signaux sur le clavier
    keyControl->signalKeyPressed.add(&Menus::keyPressed, this);
    keyControl->signalKeyReleased.add(&Menus::keyReleased, this);

    //enregistre les signaux sur PlayerControls (même si réagit uniquement à l'appui sur la touche permettant d'ouvrir le menus
    pControl->signalKeyPressed.add(&Menus::actionFromPlayer, this);
    this->menu_open=false;

    creer_souris();
    creer_main_window();
    
    //creer_menus_start();
}

Menus::~Menus()
{
    mouseControl->signalMousePressed.remove(&Menus::mousePressed, this);
    mouseControl->signalMouseReleased.remove(&Menus::mouseReleased, this);
    mouseControl->signalMouseMoved.remove(&Menus::mouseMoved, this);

    keyControl->signalKeyPressed.remove(&Menus::keyPressed, this);
    keyControl->signalKeyReleased.remove(&Menus::keyReleased, this);

    pControl->signalKeyPressed.remove(&Menus::actionFromPlayer, this);

    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    wmgr.destroyAllWindows();
    this->menusRenderer->destroyAllGeometryBuffers ();
    this->menusRenderer->destroyAllTextureTargets ();
    this->menusRenderer->destroyAllTextures ();
    CEGUI::OgreRenderer::destroySystem ();


}

bool Menus::destroyWindow(const CEGUI::EventArgs & evt)
{
    if(mainWdw==(static_cast<const CEGUI::WindowEventArgs&>(evt).window->getParent()->getParent()))
    {
        actionFromPlayer(Controls::OPEN_MENU);
        signalPaused.dispatch(false);
    }
    else
    {
        CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
        wmgr.destroyWindow((static_cast<const CEGUI::WindowEventArgs&>(evt)).window->getParent()->getParent());
    }
    return true;
}


void Menus::keyPressed(const OIS::KeyEvent &evt)
{
    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectKeyDown(evt.key);
    sys.injectChar(evt.text);

}

void Menus::actionFromPlayer(Controls::Controls key)
{
    switch(key)
    {
        case Controls::OPEN_MENU:
            if(!this->menu_open)
            {
                //suspendre_jeux(); marcheuh paaaas
                afficher_menus();
                this->menu_open = true;

            }
            else
            {
                cacher_menus();
                //redemarrer_jeux();
                this->menu_open = false;
            }
            break;
            
        default:
            break;
    }
}


void Menus::afficher_menus()
{
    afficher_souris();
    afficher_main_window();
    signalPaused.dispatch(true);
}

void Menus::cacher_menus()
{
    cacher_souris();
    cacher_main_window();
    signalPaused.dispatch(false);
}

void Menus::keyReleased(const OIS::KeyEvent &evt)
{
    CEGUI::System::getSingleton().injectKeyUp(evt.key);
}

void Menus::mousePressed(OIS::MouseButtonID evt)
{
    CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(evt));
}
void Menus::mouseReleased(OIS::MouseButtonID evt)
{
    CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(evt));
}

void Menus::mouseMoved(MouseMove_t &mouse)
{
    Ogre::Vector3 vect = mouse.vector;
    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectMouseMove(vect[0], vect[1]);
    // Scroll wheel.
    if (vect[2])
        sys.injectMouseWheelChange(vect[2] / 120.0f);
}

CEGUI::MouseButton Menus::convertButton(OIS::MouseButtonID evt)
{
    switch (evt)
    {
        case OIS::MB_Left:
            return CEGUI::LeftButton;

        case OIS::MB_Right:
            return CEGUI::RightButton;

        case OIS::MB_Middle:
            return CEGUI::MiddleButton;

        default:
            return CEGUI::LeftButton;
    }
}


void Menus::creer_souris(void)
{
    CEGUI::System::getSingleton().setDefaultMouseCursor("SleekSpace", "MouseArrow");
    CEGUI::MouseCursor::getSingleton().setImage(CEGUI::System::getSingleton().getDefaultMouseCursor());
    CEGUI::MouseCursor::getSingleton().hide();
}

void Menus::afficher_souris(void)
{
    CEGUI::MouseCursor::getSingleton().show();
}

void Menus::cacher_souris(void)
{
    CEGUI::MouseCursor::getSingleton().hide();
}


void Menus::creer_main_window(void)
{

    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();

    //the easy button
    CEGUI::Window * facileWdw = wmgr.createWindow("SleekSpace/Button", "SpaceShip/facileButton");
    facileWdw->setText("Facile");
    facileWdw->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.3,0)));
    facileWdw->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.05, 0.0f ), CEGUI::UDim( 0.32, 0.0f) ) );
    facileWdw->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::startFacile, this));

    //the medium button
    CEGUI::Window * mediumWdw = wmgr.createWindow("SleekSpace/Button", "SpaceShip/mediumButton");
    mediumWdw->setText("Facile");
    mediumWdw->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.3,0)));
    mediumWdw->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.25, 0.0f ), CEGUI::UDim( 0.32, 0.0f) ) );
    mediumWdw->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::startMedium, this));

    //the hard button
    CEGUI::Window * hardWdw = wmgr.createWindow("SleekSpace/Button", "SpaceShip/QuitButton");
    hardWdw->setText("Difficile");
    hardWdw->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.3,0)));
    hardWdw->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.45, 0.0f ), CEGUI::UDim( 0.32, 0.0f) ) );
    hardWdw->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::startDifficile, this));



    CEGUI::Window * tblWin[3];
    tblWin[0]=facileWdw;
    tblWin[1]=mediumWdw;
    tblWin[2]=hardWdw;

    this->mainWdw=create_std_window((CEGUI::utf8 *)"Combat de vaisseaux", 0.1, 0.05, 0.8, 0.2,3, tblWin);

    this->mainWdw->hide();
}

void Menus::cacher_main_window(void)
{
    mainWdw->hide();
}

void Menus::afficher_main_window(void)
{
    CEGUI::System::getSingleton().setGUISheet(this->mainWdw);

    mainWdw->show();
}


bool Menus::startFacile(const CEGUI::EventArgs & evt)
{
    Application * app = Application::getSingletonPtr();
    app->startFacile();
    this->cacher_main_window();
    return true;
}

bool Menus::startMedium(const CEGUI::EventArgs & evt)
{
    Application * app = Application::getSingletonPtr();
    app->startMedium();
    this->cacher_main_window();
    return true;
}

bool Menus::startDifficile(const CEGUI::EventArgs & evt)
{
    Application * app = Application::getSingletonPtr();
    app->startDifficile();
    this->cacher_main_window();
    return true;
}
