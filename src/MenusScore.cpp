#include "Menus.h"

Menus::MenusScore::MenusScore()
{
	this->textScore = NULL;
}

Menus::MenusScore::~MenusScore()
{

}


CEGUI::Window * Menus::MenusScore::afficher_menus_calculs(void)
{
    this->est_affiche = true;
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();

    this->textScore = wmgr.createWindow("TaharezLook/StaticText", "TextScenDebut");
    this->textScore->setSize(CEGUI::UVector2(CEGUI::UDim(0.6, 0), CEGUI::UDim(0.6,0)));
    this->textScore->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.2, 0.0f ), CEGUI::UDim( 0.2, 0.0f) ) );
    
    this->update_score();

    return create_std_window((CEGUI::utf8 *)"score", 0.1, 0.05, 0.8, 0.2,1, &this->textScore);
}



void Menus::MenusScore::update_score(void)
{
	if(this->est_affiche && this->textScore != NULL)
	{
        GestObj * gestObj= GestObj::getSingletonPtr();
        double dist= gestObj->calculDistBriquetteEloigne();
        int nbBriquettes=gestObj->getCountBriquetteDrawed(); 
        std::ostringstream oss;
        oss << "\
Nombre de briquettes placées: " << nbBriquettes <<" \n\
Distance de la briquette la plus éloignée \n au centre de la table: "<<dist;
        this->textScore->setText((CEGUI::utf8 *)(oss.str().c_str()));
	}
}

bool Menus::MenusScore::destroyWindow(const CEGUI::EventArgs & evt)
{
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    wmgr.destroyWindow((static_cast<const CEGUI::WindowEventArgs&>(evt)).window->getParent()->getParent());
    this->textScore = NULL;
    this->est_affiche = false;
    
    return true;
}


void Menus::MenusScore::actionFromPlayer(Controls::Controls key)
{
	
}


bool Menus::MenusScore::estAffiche()
{
	return this->est_affiche;
}
