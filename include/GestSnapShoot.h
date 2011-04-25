/*!
 *  \file  GestSnapShoot.h
 * \brief Ce fichier contient la déclaration de la classe GestSnapShoot. Permet de gérer les annulations, retours de modifications : undo, redo.
 */

#ifndef __GEST_SNAP_SHOOT_H__
#define __GEST_SNAP_SHOOT_H__

#ifndef DOXYGEN_SKIP
#include <deque>
#endif

#include "ClassRootSingleton.h"
#include "PlayerControls.h"
#include "SnapShoot.h"

class SnapShoot;

/*!
* \class GestSnapShoot
* \brief Permet de gérer les annulations, retours de modifications : undo, redo.
*/
class GestSnapShoot : public ClassRootSingleton<GestSnapShoot>
{
	private:
 		/*!
		 * \brief La liste des snapShoot
		 */
        std::deque<SnapShoot *> lstSnapShoot;
 		/*!
		 * \brief SnapShoot en cours de visualisation
		 */
        unsigned int currentSnapShoot;
       
	        
    public:
        /*!
         * \brief Constructor
         */
        GestSnapShoot();
        /*!
         * \brief Destructor
         */
        ~GestSnapShoot();

         /*!
         * \brief Ajoute un nouveau snapshoot
         */
        void addModification();

         /*!
         * \brief Retourne la révision courante
         * \return La valeur de currentSnapShoot
         */
        unsigned int getCurrentRevision();

         /*!
         * \brief Retourne le nombre de révision
         * \return La taille de la liste -1
         */
        unsigned int getNumberRevision();
            
         /*!
         * \brief Retire plusieurs modifications à partir du début
         * \param numberModification Nombre de modification (par défaut = 1)
         */
        void removeFirstModification(unsigned int numberModification = 1);
         /*!
         * \brief Retire plusieurs modifications à partir de la fin
         * \param numberModification Nombre de modification (par défaut = 1)
         */
        void removeLastModification(unsigned int numberModification = 1);   
         
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
        
	private:
         /*!
         * \brief Re-effectue une modification
         */
        void _applyRevision(int iVersion);
        
        /*!
         * \brief Permet de réagir a l'appui sur touche/button souris, permet de lancer la prise de briquettes
         * \param key Evénement du clavier
        */
        void onKeyPressed(Controls::Controls key);
};

#endif

