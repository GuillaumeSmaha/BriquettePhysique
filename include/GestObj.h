/*!
 *  \file  GestObj.h
 *  \brief Ce fichier contient la déclaration de la classe GestObj. Permet de gérer les différents objets du monde, création, utilisation, destruction
 */

#ifndef __GEST_OBJ_H__
#define __GEST_OBJ_H__


#include "ObjTable.h"
#include "ObjBriquette.h"

/*!
* \class GestObj
* \brief Permet de gérer les différents objets du monde, création, utilisation, destruction. Contient l'objet Table utilité et une liste des briquettes
*/
class GestObj
{
	private:
		/*!
		 *  \brief Instance de ListenerFrame pour le singleton
		 */
		static GestObj * _instance;

		/*!
		 *  \brief La table active dans le jeux
		 */
        ObjTable * table;
 		/*!
		 *  \brief La liste des briquettes
		 */
        std::vector<ObjBriquette *> lstBriquettes;
               

	public:
		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static void createSingleton();
		/*!
		 *  \brief Retourne un pointeur sur l'instance du singleton
		 */
		static GestObj * getSingletonPtr();
		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static GestObj & getSingleton();
        /*!
         * \brief Detruit le singleton
         */
        static void destroySingleton();
       
	
	private:
        /*!
         * \brief Constructor
         */
        GestObj();
        
    public:
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

