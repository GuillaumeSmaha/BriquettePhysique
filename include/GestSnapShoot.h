/*!
 *  \file  GestSnapShoot.h
 * \brief Ce fichier contient la déclaration de la classe GestSnapShoot. Permet de gérer les annulations, retours de modifications : undo, redo.
 */

#ifndef __GEST_SNAP_SHOOT_H__
#define __GEST_SNAP_SHOOT_H__

#include <deque>
#include "ClassRootSingleton.h"
#include "SnapShoot.h"
#include "ObjBriquette.h"

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
         * \param snapShoot SnapShoot correspondant à la modification
         */
        void addModification(SnapShoot * snapShoot);

         /*!
         * \brief Ajoute un nouveau snapshoot
         * \param briquette Briquette ayant subi la modification.
         */
        void addModification(ObjBriquette * briquette);

         /*!
         * \brief Annule une modification
         */
        void undo();
         /*!
         * \brief Annule plusieurs modifications
         * \param numberModification Nombre de modification
         */
        void undo(int numberModification);
         /*!
         * \brief Annule toutes les modifications
         */
        void undoAll();
        
         /*!
         * \brief Re-effectue une modification
         */
        void redo();
         /*!
         * \brief Re-effectue plusieurs modifications
         * \param numberModification Nombre de modification
         */
        void redo(int numberModification);
         /*!
         * \brief Re-effectue toutes les modifications
         */
        void redoAll();
};

#endif

