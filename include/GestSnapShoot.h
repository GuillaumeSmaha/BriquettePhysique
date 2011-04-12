/*!
 *  \file  GestSnapShoot.h
 * \brief Ce fichier contient la déclaration de la classe GestSnapShoot. Permet de gérer les annulations, retours de modifications : undo, redo.
 */

#ifndef __GEST_SNAP_SHOOT_H__
#define __GEST_SNAP_SHOOT_H__

#include <deque>
#include "ClassRootSingleton.h"
#include "SnapShoot.h"

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
        int currentSnapShoot;
       
	        
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
         * \brief Retire plusieurs modifications à partir du début
         * \param numberModification Nombre de modification (par défaut = 1)
         */
        void removeFirstModification(int numberModification = 1);
         /*!
         * \brief Retire plusieurs modifications à partir de la fin
         * \param numberModification Nombre de modification (par défaut = 1)
         */
        void removeLastModification(int numberModification = 1);    
        
         /*!
         * \brief Annule plusieurs modifications
         * \param numberModification Nombre de modification (par défaut = 1)
         */
        void undo(int numberModification = 1);
         /*!
         * \brief Annule toutes les modifications
         */
        void undoAll();
        
         /*!
         * \brief Re-effectue plusieurs modifications
         * \param numberModification Nombre de modification (par défaut = 1)
         */
        void redo(int numberModification = 1);
         /*!
         * \brief Re-effectue toutes les modifications
         */
        void redoAll();
};

#endif

