/*!
 *  \file  GestObj.h
 * \brief Ce fichier contient la déclaration de la classe GestObj. Permet de gérer les différents objets du monde, création, utilisation, destruction
 */

#ifndef __GEST_OBJ_H__
#define __GEST_OBJ_H__


#include "ClassRootSingleton.h"
#include "ObjTable.h"
#include "ObjBriquette.h"

/*!
* \class GestObj
* \brief Permet de gérer les différents objets du monde, création, utilisation, destruction. Contient l'objet Table utilité et une liste des briquettes
*/
class GestObj : public ClassRootSingleton<GestObj>
{
	private:
		/*!
		 * \brief La table active dans le jeux
		 */
        ObjTable * table;
 		/*!
		 * \brief La liste des briquettes
		 */
        std::vector<ObjBriquette *> lstBriquettes;
       
	        
    public:
        /*!
         * \brief Constructor
         */
        GestObj();
        /*!
         * \brief Destructor
         */
        virtual ~GestObj();

         /*!
         * \brief défini la table du jeux, ne peux être appellé qu'une fois
         */
        void setTable(ObjTable * table);

         /*!
         * \brief Ajoute une nouvelle briquettes
         */
        void addBriquette(ObjBriquette* briquette);


};

#endif

