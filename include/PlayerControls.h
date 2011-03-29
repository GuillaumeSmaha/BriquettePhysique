/*!
*  \file  PlayerControls.h
* \brief Ce fichier contient la déclaration de la classe PlayerControls. 
*/
#ifndef __PLAYER_CONTROLS_H__
#define __PLAYER_CONTROLS_H__

#include <vector>
#include "Utils.h"
#include "Signal.h"
#include "ClassRootSingleton.h"
#include "ListenerKeyboard.h"
#include "ListenerMouse.h"
#include "controls.h"

#define NB_MOUSE_MOD 2
#define MOUSE_MOD_SELECT 0
#define MOUSE_MOD_CAMERA 1



/*!
* \class PlayerControls
* \brief Class Permettant de gérer le contrôle de manière "haut niveau" du joueur au d'utiliser directement les évènements de base de Ogre
* Permettra par la suite de facilemet modifier les contrôles pour chaque joueur (enregistrés dans un fichier par exemple)
* Par la suite il faudra donc écouter les évènements (signaux) de PlayerControls et non plus directement de mouse et keyboard
*/
class PlayerControls: public ClassRootSingleton<PlayerControls>
{
		
	public:
	     /*!
		 * \brief Nombre maximum de touche clavier dans OIS
		 */
		const static int maxOISKeyControl = 0xED+1;
         /*!
		 * \brief Nombre maximum de touche souris dans OIS
		 */
		const static int maxOISMouseControl = 7;
	

	private:
         /*!
		 * \brief Lie une touche à un contrôle (déplacement, tir). 
         * par exemple listKeyControl[25]=SHOOT1 position la touche repéré par le code 25 sur l'action SHOOT1
		 */
        std::vector<Controls::Controls> listKeyControl;
         /*!
		 * \brief Lie un bouton de souris à un contrôle.
		 */
        std::vector<Controls::Controls> listMouseControl;
         /*!
		 * \brief Indique si le mouseMove est pris en compte pour les mouvements du vaisseau
		 */
        bool mouseMovedActif;
         /*!
         * \brief contient le mode actuel d'utilisation de la souris
        */
        int mouseMod;

       
	public:
		/*!
		 * \brief Emet un dispatche lorsqu'une touche est préssée  Signal(Controls key)
		 */
        Signal<Controls::Controls> signalKeyPressed;
        /*!
		 * \brief Emet un dispatche lorsqu'une touche est relâchée  Signal(Controls::Controls key)
		 */
        Signal<Controls::Controls> signalKeyReleased;
         /*!
		 * \brief Emet un dispatche de type select lorsque la souris est bougée  Signal(Ogre::Vector3)
		 */
        Signal<Ogre::Vector3> signalMouseSelectMoved;
         /*!
		 * \brief Emet un dispatche de type select lorsque la souris est bougée  Signal(Ogre::Vector3)
		 */
        Signal<Ogre::Vector3> signalMouseCameraMoved;
	
        /*!
         * \brief Permet d'arréter de réagir aux listeners 
         * Utile lorsque le menu est activé.
        */
        void suspendre_ecoute();
        /*!
         * \brief Permet de rependre l'écoute des listeneurs
         * Appelé aprés que le menu ai été fermé.
        */
        void reprendre_ecoute();
        /*!
         * \brief permet de changer de mod de souris
        */
        void changeMod();
 
    public:
        /*!
         * \brief Constructor
         */
        PlayerControls();
        /*!
         * \brief Destructor
         */
        virtual ~PlayerControls();

        /*!
         * \brief Permet de remettre les touches par défaults
         */
        void setDefaultKeys(void);        
        /*!
         * \brief Met à zéro les controllers de touche clavier et souris
         */
        void resetControls(void);        
        /*!
         * \brief Définit une touche du clavier pour une action donnée
         * \param keyControl Action à effectuer
         * \param key Touche correspondante
         */
        void setKeyControl(const Controls::Controls keyControl, const OIS::KeyCode key);
        /*!
         * \brief Définit une touche de la souris pour une action donnée
         * \param keyControl Action à effectuer
         * \param mouseId Touche correspondante
         */
        void setMouseControl(const Controls::Controls keyControl, const OIS::MouseButtonID mouseId);
        
    private:
         /*!
		 * \brief Reçoit un dispatche lorsqu'une touche du clavier est pressée et le transmet à signalKeyPressed
		 * \param evt Event OIS
		 */
        void keyboardPressed(const OIS::KeyEvent &evt);
        /*!
		 * \brief Reçoit un dispatche lorsqu'une touche du clavier est relâchée et le transmet à signalKeyReleased
		 * \param evt Event OIS
		 */
        void keyboardReleased(const OIS::KeyEvent &evt);
        /*!
		 * \brief Reçoit un dispatche lorsqu'un la souris est bougée et le transmet à signalMouseMoved
		 * \param vect Vector3(X, Y, Z)
		 */
        void mouseMoved(Ogre::Vector3 vect);
        /*!
		 * \brief Reçoit un dispatche lorsqu'une touche de la souris est pressée et le transmet à signalKeyPressed
		 * \param evt Event OIS
		 */
        void mousePressed(const OIS::MouseButtonID evt);
        /*!
		 * \brief Reçoit un dispatche lorsqu'une touche de la souris est relâchée et le transmet à signalKeyReleased
		 * \param evt Event OIS
		 */
        void mouseReleased(const OIS::MouseButtonID evt);
        /*!
		 * \brief Convertit un évènement OIS::KeyEvent en Controls::Controls pour se défaire du couplage aux touches physiques
		 * \param evt Event OIS
		 * \return Controls::Controls key correspondante
		 */
        Controls::Controls OISEventToControlKey(const OIS::KeyEvent &evt);
        /*!
		 * \brief Convertit un id IS::MouseButtonID en Controls::Controls pour se défaire du couplage aux touches physiques
		 * \param evt Mouse button ID (OIS)
		 * \return Controls::Controls key correspondante
		 */
        Controls::Controls OISEventToControlKey(const OIS::MouseButtonID evt);
         /*!
		 * \brief [Getter] Recupère la valeur de mouseMovedActif
		 * \return Indique si le mouvement de la souris est actif pour le vaisseau
		 */
        bool getMouseMovedActif();
         /*!
		 * \brief [Setter] Définit la valeur de mouseMovedActif
		 * \param mouseMovedActif Indique si le mouvement de la souris est actif pour le vaisseau
		 */
        void setMouseMovedActif(bool mouseMovedActif);


};

#endif // __PLAYER_CONTROLS_H__
