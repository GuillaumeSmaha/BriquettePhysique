#include "Menus.h"

Menus::MenusBriquette::MenusBriquette()
{


}

Menus::MenusBriquette::~MenusBriquette()
{


}

bool Menus::MenusBriquette::destroyWindow(const CEGUI::EventArgs & evt)
{
	return true;
}


void Menus::MenusBriquette::actionFromPlayer(Controls::Controls key)
{
	
}

CEGUI::Window * Menus::MenusBriquette::creer_menus_briquettes(void)
{
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();

    //the add briquette button
    this->addBriquetteWdw = wmgr.createWindow("SleekSpace/Button", "Briquette/addBriquette");
    this->addBriquetteWdw->setText("0");
    this->addBriquetteWdw->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.3,0)));
    this->addBriquetteWdw->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.05, 0.0f ), CEGUI::UDim( 0.32, 0.0f)));
    this->addBriquetteWdw->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::MenusBriquette::addBriquette, this));
    
    this->idRevisionWdw = wmgr.createWindow("SleekSpace/Button", "Briquette/idRevisionBriquette");
    this->idRevisionWdw->setText("Rev : 0/0");
    this->idRevisionWdw->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.3,0)));
    this->idRevisionWdw->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.25, 0.0f ), CEGUI::UDim( 0.32, 0.0f)));
    //~ this->idRevisionWdw->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::MenusBriquette::addBriquette, this));
    
    int nbList = 2;
    CEGUI::Window * tblWin[nbList];
    tblWin[0] = this->addBriquetteWdw;
    tblWin[1] = this->idRevisionWdw;

	return create_std_window((CEGUI::utf8 *)"Controles du jeux", 0.0, 0.85, 1, 0.1, nbList, tblWin);
}

void Menus::MenusBriquette::updateTextButtons()
{
    this->addBriquetteWdw->setText(Utils::toString(GestGame::getSingletonPtr()->getNumberBriquetteRemaining()));
    this->idRevisionWdw->setText("Rev : "+Utils::toString(GestSnapShoot::getSingletonPtr()->getCurrentRevision())+"/"+Utils::toString(GestSnapShoot::getSingletonPtr()->getNumberRevision()));
}

bool Menus::MenusBriquette::addBriquette(const CEGUI::EventArgs & evt)
{
    if(GestGame::getSingletonPtr()->addBriquette())
    {
		this->updateTextButtons();
		
		return true;
	}
	
	return false;
}
