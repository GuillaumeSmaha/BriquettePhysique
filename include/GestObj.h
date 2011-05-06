/*!
 *  \file  GestObj.h
 * \brief Ce fichier contient la déclaration de la classe GestObj. Permet de gérer les différents objets du monde, création, utilisation, destruction
 */
#ifndef __GEST_OBJ_H__
#define __GEST_OBJ_H__

#include "nodeName.h"
#include "ClassRootSingleton.h"
#include "Utils.h"
#include "GestGame.h"
#include "ObjTable.h"
#include "ObjBriquette.h"

class ObjBriquette;
class ObjTable;

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
 		/*!
		 * \brief La liste des briquettes afin de 
		 */
        std::map<OgreBulletDynamics::RigidBody *, ObjBriquette *> lstRigidBodyToBriquette;
     
	        
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
		 * \brief Retourne le nombre de briquette affichée
		 * \return Nombre de briquette
		*/
        int getCountBriquetteDrawed();
        
         /*!
         * \brief Ajoute une nouvelle briquettes
         * \param pos: position à laquelle la nouvelle briquette est placé
         */
        void addBriquette(const Ogre::Vector3 &pos);

		/*!
		 * \brief Vérifie si la briquette existe dans la liste
		 * \param briquette Pointeur à vérifier
		 * \return Vrai ou faux
		*/
		bool existBriquette(ObjBriquette * briquette);

		/*!
		 * \brief Vérifie si la briquette existe dans la liste
		 * \param briquette Pointeur à supprimer
		*/
		void removeBriquette(ObjBriquette * briquette);    
		
        /*!
         * \brief Met à jour les forces de toutes les briquettes en jeux
         * Ca permet d'avoir les briquettes en mouvement immédiatement.
        */
        void updateAllForces();
        /*!
         * \brief Clear les forces de toutes les briquettes en jeux
         * Ca permet d'avoir un déplacement de briquettes immédiat.
        */
        void clearAllForces();


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
        std::vector<ObjBriquette *> & getListBriquettes();

         /*!
		 * \brief Nombre de données
		 * \return Le taille du vecteur "lstBriquettes"
         */
        unsigned int getNumberBriquettes();
         
         /*!
         * \brief La liste des relations rigidBody->briquette
		 * \return La map "lstRigidBodyToBriquette"
         */
        std::map<OgreBulletDynamics::RigidBody *, ObjBriquette *> & getListRigidBodyToBriquette();

         /*!
		 * \brief Retourne la briquette en fonction de son rigidBody
		 * \return Un pointeur ou NULL s'il n'existe pas
         */
        ObjBriquette * getBriquetteByRigidBody(OgreBulletDynamics::RigidBody * rigidBody);
};

#endif

