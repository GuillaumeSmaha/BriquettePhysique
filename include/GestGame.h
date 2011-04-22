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
#include "ListenerFrame.h"

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
        */
        bool addBriquette();
     
        /*!
        * \brief Quitte le jeu
        */
        void quitGame();
        
	    /*!
		* \brief Permet de recevoir un evènement quand une touche est appuyé
        *   Ici, permet de fermer l'application
		*/	
        void onKeyPressed(Controls::Controls key);
        
        
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
