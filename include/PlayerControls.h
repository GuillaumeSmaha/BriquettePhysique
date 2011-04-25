/*!
*  \file  PlayerControls.h
* \brief Ce fichier contient la déclaration de la classe PlayerControls. 
*/
#ifndef __PLAYER_CONTROLS_H__
#define __PLAYER_CONTROLS_H__

#ifndef DOXYGEN_SKIP
#include <vector>
#endif

#include "controls.h"
#include "mouseMove.h"
#include "ClassRootSingleton.h"
#include "Signal.h"
#include "Utils.h"
#include "ListenerKeyboard.h"
#include "ListenerMouse.h"

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
		 * \brief Emet un dispatche lorsque la souris est déplacée Signal(Ogre::MouseMove_t)
		 */
        Signal<MouseMove_t&> signalMouseMoved;
 
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
         * \param removeDuplicate Definit si l'on supprime ou non les doublons avant l'affectation.
         * Permet en autre d'ajouter plusieurs touches pour une seule action
         * Définit à vrai par défaut.
         */
        void setKeyControl(const Controls::Controls keyControl, const OIS::KeyCode key, bool removeDuplicate = true);
        /*!
         * \brief Définit une touche de la souris pour une action donnée
         * \param keyControl Action à effectuer
         * \param mouseId Touche correspondante
         * \param removeDuplicate Definit si l'on supprime ou non les doublons avant l'affectation.
         * Permet en autre d'ajouter plusieurs touches pour une seule action
         * Définit à vrai par défaut.
         */
        void setMouseControl(const Controls::Controls keyControl, const OIS::MouseButtonID mouseId, bool removeDuplicate = true);
	
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
        
        
    private:
         /*!
		 * \brief Reçoit un dispatche lorsqu'une touche du clavier est pressée et le transmet à signalKeyPressed
		 * \param evt Evénement du clavier
		 */
        void keyboardPressed(const OIS::KeyEvent &evt);
        /*!
		 * \brief Reçoit un dispatche lorsqu'une touche du clavier est relâchée et le transmet à signalKeyReleased
		 * \param evt Evénement du clavier
		 */
        void keyboardReleased(const OIS::KeyEvent &evt);
        /*!
		 * \brief Reçoit un dispatche lorsqu'un la souris est bougée et le transmet à signalMouseMoved
		 * \param mouseMove Structure de déplacement de la souris
		 */
        void mouseMoved(MouseMove_t &mouseMove);
        /*!
		 * \brief Reçoit un dispatche lorsqu'une touche de la souris est pressée et le transmet à signalMousePressed
		 * \param evt Evénement de la souris
		 */
        void mousePressed(const OIS::MouseButtonID evt);
        /*!
		 * \brief Reçoit un dispatche lorsqu'une touche de la souris est relâchée et le transmet à signalMouseReleased
		 * \param evt Evénement de la souris
		 */
        void mouseReleased(const OIS::MouseButtonID evt);
        /*!
		 * \brief Convertit un évènement OIS::KeyEvent en Controls::Controls pour se défaire du couplage aux touches physiques
		 * \param evt Evénement du clavier (OIS)
		 * \return Controls::Controls Touche correspondante
		 */
        Controls::Controls OISEventToControlKey(const OIS::KeyEvent &evt);
        /*!
		 * \brief Convertit un id IS::MouseButtonID en Controls::Controls pour se défaire du couplage aux touches physiques
		 * \param evt Evénement de la souris (OIS)
		 * \return Controls::Controls Touche correspondante
		 */
        Controls::Controls OISEventToControlKey(const OIS::MouseButtonID evt);
        
        
        //Getter-Setter
        
	public:        
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
