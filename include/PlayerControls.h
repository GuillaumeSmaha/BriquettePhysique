/*!
*  \file  PlayerControls.h
*  \brief Ce fichier contient la déclaration de la classe PlayerControls. 
*/
#ifndef __PLAYER_CONTROLS_H__
#define __PLAYER_CONTROLS_H__

#include <vector>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include "Signal.h"
#include "ListenerMouse.h"
#include "ClassRoot.h"
#include "ListenerKeyboard.h"

class ListenerKeyboard;
class ListenerMouse;

/*!
* \class PlayerControls
* \brief Class Permettant de gérer le contrôle de manière "haut niveau" du joueur au d'utiliser directement les évènements de base de Ogre
* Permettra par la suite de facilemet modifier les contrôles pour chaque joueur (enregistrés dans un fichier par exemple)
* Par la suite il faudra donc écouter les évènements (signaux) de PlayerControls et non plus directement de mouse et keyboard
*/
class PlayerControls: public ClassRoot
{
	private:
		/*!
		 *  \brief Instance de ListenerFrame pour le singleton
		 */
		static PlayerControls * _instance ;
        /*!
         * \brief Constructor
         * \param mouse MouseListener
         * \param keyboard KeyboardListener
         */
        PlayerControls();
        /*!
         * \brief Destructor
         */
        virtual ~PlayerControls();
        

    public:
		/// Définit les différents types de contrôles
		enum Controls
		{
			NONE = 0,
			CAM_MOVE_RIGHT= 1,
			CAM_MOVE_LEFT= 2,
			CAM_MOVE_UP= 3,
			CAM_MOVE_DOWN= 4,
			CAM_ZOOM_IN= 5,
			CAM_ZOOM_OUT= 6,
            OPEN_MENU= 7,
			QUIT = 8,
            SWITCH_NEXT_CAMERA = 9,
            SWITCH_PREV_CAMERA = 12,
            SELECT = 12,    //permet de selectionner une briquette
            UNDO = 14,
            SUPPR = 15,
            SAVE= 16
		};
		
         /*!
		 * \brief Nombre maximum de touche clavier dans OIS
		 */
		const static int maxOISKeyControl = 0xED+1;
         /*!
		 * \brief Nombre maximum de touche souris dans OIS
		 */
		const static int maxOISMouseControl = 7;

         /*!
		 * \brief Pointeur sur le controleur du clavier
		 */
        ListenerKeyboard * keyboard;
         /*!
		 * \brief Pointeur sur le controleur de la souris
		 */
        ListenerMouse * mouse;


		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static void createSingleton();
		/*!
		 *  \brief Retourne un pointeur sur l'instance du singleton
		 */
		static PlayerControls * getSingletonPtr();
		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static PlayerControls & getSingleton();
        /*!
         * \brief Detruit le singleton
         */
        static void destroySingleton();



	private:
         /*!
		 * \brief Lie une touche à un contrôle (déplacement, tir). 
         * par exemple listKeyControl[25]=SHOOT1 position la touche repéré par le code 25 sur l'action SHOOT1
		 */
        std::vector<PlayerControls::Controls> listKeyControl;
         /*!
		 * \brief Lie un bouton de souris à un contrôle.
		 */
        std::vector<PlayerControls::Controls> listMouseControl;
         /*!
		 * \brief Indique si le mouseMove est pris en compte pour les mouvements du vaisseau
		 */
        bool mouseMovedActif;
        
	public:
		/*!
		 * \brief Emet un dispatche lorsqu'une touche est préssée  Signal(PlayerControls::Controls key)
		 */
        Signal<PlayerControls::Controls> signalKeyPressed;
        /*!
		 * \brief Emet un dispatche lorsqu'une touche est relâchée  Signal(PlayerControls::Controls key)
		 */
        Signal<PlayerControls::Controls> signalKeyReleased;
         /*!
		 * \brief Emet un dispatche lorsque la souris est bougée  Signal(Ogre::Vector3)
		 */
        Signal<Ogre::Vector3> signalMouseMoved;
	
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

    public:

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
        void setKeyControl(const PlayerControls::Controls keyControl, const OIS::KeyCode key);
        /*!
         * \brief Définit une touche de la souris pour une action donnée
         * \param keyControl Action à effectuer
         * \param mouseId Touche correspondante
         */
        void setMouseControl(const PlayerControls::Controls keyControl, const OIS::MouseButtonID mouseId);
        
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
        void mousePressed(OIS::MouseButtonID evt);
        /*!
		 * \brief Reçoit un dispatche lorsqu'une touche de la souris est relâchée et le transmet à signalKeyReleased
		 * \param evt Event OIS
		 */
        void mouseReleased(OIS::MouseButtonID evt);
        /*!
		 * \brief Convertit un évènement OIS::KeyEvent en PlayerControls::Controls pour se défaire du couplage aux touches physiques
		 * \param evt Event OIS
		 * \return PlayerControls::Controls key correspondante
		 */
        PlayerControls::Controls OISEventToControlKey(const OIS::KeyEvent &evt);
        /*!
		 * \brief Convertit un id IS::MouseButtonID en PlayerControls::Controls pour se défaire du couplage aux touches physiques
		 * \param evt Mouse button ID (OIS)
		 * \return PlayerControls::Controls key correspondante
		 */
        PlayerControls::Controls OISEventToControlKey(const OIS::MouseButtonID evt);
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
