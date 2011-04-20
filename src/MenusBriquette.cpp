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
    CEGUI::Window * tblWin[1];
    tblWin[0] = this->addBriquetteWdw;

	return create_std_window((CEGUI::utf8 *)"Controles du jeux", 0.0, 0.85, 1, 0.1,1, tblWin);
}

void Menus::MenusBriquette::update_Nb_briquette_in_menus()
{
    this->addBriquetteWdw->setText(Utils::toString(GestGame::getSingletonPtr()->getNumberBriquetteRemaining()));
}

bool Menus::MenusBriquette::addBriquette(const CEGUI::EventArgs & evt)
{
    if(GestGame::getSingletonPtr()->addBriquette())
    {
		this->update_Nb_briquette_in_menus();
		
		return true;
	}
	
	return false;
}
