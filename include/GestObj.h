/*!
 *  \file  GestObj.h
 * \brief Ce fichier contient la déclaration de la classe GestObj. Permet de gérer les différents objets du monde, création, utilisation, destruction
 */

#ifndef __GEST_OBJ_H__
#define __GEST_OBJ_H__


#include "nodeName.h"
#include "ClassRootSingleton.h"
#include "Utils.h"
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
		 * \brief La table de fond
		 */
        ObjTable * tableBackground;
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
         * \brief Ajoute une nouvelle briquettes
         * \param pos: position à laquelle la nouvelle briquette est placé
         */
        void addBriquette(const Ogre::Vector3 &pos);
        

		/*!
		 * \brief Vérifie si la briquette existe dans la liste
		 * \return Vrai ou faux
		*/
		bool existBriquette(ObjBriquette * briquette);

         //#######GETTER /SETTER########

         /*!
         * \brief [Getter] Retourne un pointeur sur la table de fond
         * \return Un pointeur sur l'objet tableBackground
         */
        ObjTable * getTableBackground(void)
        {
            return this->tableBackground;
        }
         /*!
         * \brief [Setter] Défini la table du jeux, ne peux être appellé qu'une fois
         * \param tableBackground Un pointeur sur la table de fond à définir
         */
        void setTableBackground(ObjTable * tableBackground);

         /*!
         * \brief [Getter] Retourne un pointeur sur la table de jeux
         * \return Un pointeur sur l'objet table
         */
        ObjTable * getTable(void)
        {
            return this->table;
        }
         /*!
         * \brief [Setter] Défini la table du jeux, ne peux être appellé qu'une fois
         * \param table Un pointeur sur la table à définir
         */
        void setTable(ObjTable * table);
         
         /*!
         * \brief La liste des données
		 * \return Le vecteur "lstBriquettes"
         */
        std::vector<ObjBriquette *> getListBriquettes()
        {
			return this->lstBriquettes;
		}

         /*!
		 * \brief Nombre de données
		 * \return Le taille du vecteur "lstBriquettes"
         */
        int getNumberBriquettes()
        {
			return this->lstBriquettes.size();
		}

};

#endif

