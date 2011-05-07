#include "Menus.h"

Menus::MenusScore::MenusScore()
{

}

Menus::MenusScore::~MenusScore()
{

}


CEGUI::Window * Menus::MenusScore::afficher_menus_calculs(void){
    this->est_affiche=true;
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();

    double dist= GestObj::getSingletonPtr()->calculDistBriquetteEloigne();
	std::ostringstream oss;
	oss << "Distance de la briquette la plus eloigne \n au centre de la table: "<<dist;

    CEGUI::Window * textScen= wmgr.createWindow("TaharezLook/StaticText", "TextScenDebut");
    textScen->setSize(CEGUI::UVector2(CEGUI::UDim(0.6, 0), CEGUI::UDim(0.6,0)));
    textScen->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.2, 0.0f ), CEGUI::UDim( 0.2, 0.0f) ) );

    textScen->setText(oss.str());


    return create_std_window((CEGUI::utf8 *)"score", 0.1, 0.05, 0.8, 0.2,1, &textScen);
}


bool Menus::MenusScore::destroyWindow(const CEGUI::EventArgs & evt){
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    wmgr.destroyWindow((static_cast<const CEGUI::WindowEventArgs&>(evt)).window->getParent()->getParent());
    this->est_affiche=false;
}
