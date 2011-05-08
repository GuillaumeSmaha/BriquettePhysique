/*!
 *  \file  GestGame.h
 * \brief Ce fichier contient la déclaration de la classe GestGame. C'est la classe gérant les informations de la partie
 */
#ifndef __GEST_GAME_H__
#define __GEST_GAME_H__

/*!
 * \brief Nombre de briquettes au niveau facile
 */
#define NB_BRIQ_EASY 10
/*!
 * \brief Nombre de briquettes au niveau normal
 */
#define NB_BRIQ_MEDIUM 100
/*!
 * \brief Nombre de briquettes au niveau difficile
 */
#define NB_BRIQ_HARD 250


#include "controls.h"
#include "ClassRootSingleton.h"
#include "Application.h"
#include "Menus.h"
#include "PlayerControls.h"
#include "ListenerFrame.h"
#include "ListenerCollision.h"
#include "ListenerWindow.h"
#include "MouseFunction.h"
#include "ObjBriquette.h"

class Menus;

/*!
 * \class GestGame
 * \brief Classe permettant de gérer le jeu.
 */
class GestGame : public ClassRootSingleton<GestGame>
{
    public:
		/// Define the different types of control
		enum Difficulty
		{
			///Difficulty seay
			DIFFICULTY_EASY = 0,
			///Difficulty medium
			DIFFICULTY_MEDIUM,
			///Difficulty hard
			DIFFICULTY_HARD
		};
    
    private:
        /*!
        * \brief Position for the new briquette
        */
        Ogre::Vector3 positionCreationBriquette; 
        
        /*!
        * \brief Number maximum of Briquette
        */
        unsigned int numberMaxBriquette; 
    
        /*!
        * \brief Number of Briquette in game
        */
        unsigned int numberBriquetteInGame;  
        
        /*!
        * \brief Number of Briquette in game
        */
        bool gameLauched;
        
	public:
        /*!
        * \brief constructeur
        */
        GestGame();
        /*!
        * \brief destructeur
        */
        ~GestGame();     
     
        
        /*!
        * \brief Définit le niveau de difficulté
        * \param difficulty The difficulty choosen
        */
        void setDifficulty(GestGame::Difficulty difficulty);
     
        /*!
        * \brief Ajoute une briquette au jeu
        * \return Si la briquette à été ajouté
        */
        bool addBriquette();
     
        /*!
        * \brief Retire une briquette au jeu
        * \param briquette Briquette à supprimer
        */
        void removeBriquette(ObjBriquette * briquette);
        
        /*!
        * \brief Vérifie si une briquette ne doit pas etre supprimer de l'affichage
        */
        void checkBriquette(const Ogre::FrameEvent & null);
        
        /*!
        * \brief Aligne les briquettes
        */
        void alignBriquettes();
        
         /*!
         * \brief Ajoute une nouvelle modification
         */
        void addModification();
         /*!
         * \brief Annule plusieurs modifications
         * \param numberModification Nombre de modification (par défaut = 1)
         */
        void undo(unsigned int numberModification = 1);
         /*!
         * \brief Annule toutes les modifications
         */
        void undoAll();
               
         /*!
         * \brief Re-effectue plusieurs modifications
         * \param numberModification Nombre de modification (par défaut = 1)
         */
        void redo(unsigned int numberModification = 1);
         /*!
         * \brief Re-effectue toutes les modifications
         */
        void redoAll();
     
        /*!
        * \brief Quitte le jeu
        */
        void quitGame();
        
        /*!
         * \brief Essaie de déplacer la cible de la caméra à l'emplacement de la briquette
        */
        void moveCameraTargetOnBriquette();
        
		/*!
		 * \brief Switch the value of the attribute physicEngineState in the singleton ListenerCollision
		 */
        void switchPhysicEngineState();
        
        /*!
         * \brief Permet de déplacer la souris en lui injectant le vecteur x, y.
         * La souris n'est pas géré directement dans cette classe mais dans la
         * classe MouseFunction car en réalité on à 2 souris (la souris du
         * menus CEGUI et la souris de bullet pour attraper les briquettes.
         *
         * Cette fonction permet donc a GestGame de déplacer la souris de
         * Bullet et de CEGUI pour que les deux ai la même position
         * \param delta_x Déplacement sur l'axe X
         * \param delta_y Déplacement sur l'axe Y
        */
        void injectMouseMove(float delta_x, float delta_y);
        
        
	    /*!
		 * \brief Permet de recevoir un evènement quand une touche est appuyé
         * \param key Touche du clavier (Controls::Controls)
		*/	
        void onKeyPressed(Controls::Controls key);
        /*!
		 * \brief Permet de recevoir un evènement quand une touche est appuyé
         * \param key Touche du clavier (Controls::Controls)
        */
        void onKeyReleased(Controls::Controls key);        
        /*!
		 * \brief Permet de recevoir un evènement quand une touche de la souris est appuyé ou quand la souris est déplacé
		 * \param mouseMove Structure de déplacement de la souris
        */
        void onMouseMoved(MouseMove_t &mouseMove);
        
        
	public:
	
        // Getter - Setter
        
        
		/*!
		 * \brief Définit la difficulté : facile
		*/
        void setDifficultyEasy()
        {
			this->setDifficulty(GestGame::DIFFICULTY_EASY);
		}
		
		/*!
		 * \brief Définit la difficulté : normal
		*/
        void setDifficultyMedium()
        {
			this->setDifficulty(GestGame::DIFFICULTY_MEDIUM);
		}
		
		/*!
		 * \brief Définit la difficulté : difficile
		*/
        void setDifficultyHard()
        {
			this->setDifficulty(GestGame::DIFFICULTY_HARD);
		}        
        
		/*!
		 * \brief Retourne si le jeu est lancé
		 * \return Valeur de gameLauched
		*/
        bool getGameLauched()
        {
			return this->gameLauched;
		}
		
		/*!
		 * \brief Retourne le nombre de briquette dans la partie
		 * \return Valeur de numberBriquetteInGame
		*/
        unsigned int getNumberBriquetteInGame()
        {
			return this->numberBriquetteInGame;
		}
        
		/*!
		 * \brief Retourne le nombre de briquette max dans la partie
		 * \return Valeur de numberMaxBriquette
		*/
        unsigned int getNumberMaxBriquette()
        {
			return this->numberMaxBriquette;
		}
        
		/*!
		 * \brief Retourne le nombre de briquette restante dans la partie
		 * \return Valeur de (numberMaxBriquette-numberBriquetteInGame)
		*/
        unsigned int getNumberBriquetteRemaining()
        {
			return (this->numberMaxBriquette - this->numberBriquetteInGame);
		}
		
		/*!
		 * \brief Retourne la posiiton des nouvelles briquettes
		 * \return Valeur de positionCreationBriquette
		*/
        Ogre::Vector3 getPositionCreationBriquette()
        {
			return this->positionCreationBriquette;
		}
		
		/*!
		 * \brief Définit la posiiton des nouvelles briquettes
		 * \param positionCreationBriquette Valeur de positionCreationBriquette
		*/
        void setPositionCreationBriquette(Ogre::Vector3 positionCreationBriquette)
        {
			this->positionCreationBriquette = positionCreationBriquette;
		}
        
};


#endif //__GEST_GAME_H__
