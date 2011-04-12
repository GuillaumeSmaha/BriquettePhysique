/*!
 *  \file  SnapShoot.h
 * \brief Ce fichier contient la déclaration de la classe SnapShoot. Gere la table du monde, qui correspond à l'objet statique sur lequelle on pose nos briques.
 */

#ifndef __SNAP_SHOOT_H__
#define __SNAP_SHOOT_H__

#include <vector>
#include <Ogre.h>
#include "GestObj.h"
#include "ListenerCollision.h"

/*!
* \struct SnapShootData
* \brief Structure d'une donnée du SnapShoot
*/
struct SnapShootData
{
	/*!
	 * \brief Objet concerné par la donnée.
	 * Si objectDelete == true alors objet est une copie de l'objet.
	*/
	ObjBriquette * object;
	/*!
	 * \brief Indique si l'objet a été créé
	*/
	bool objectCreate;
	/*!
	 * \brief Indique si l'objet a été supprimé
	*/
	bool objectDelete;
	/*!
	 * \brief Position de l'objet
	*/
	Ogre::Vector3 position;
	/*!
	 * \brief Orientation de l'objet
	*/
	Ogre::Quaternion orientation;
	
};

/*!
* \class SnapShoot
* \brief Gere la table du monde, qui correspond à l'objet statique sur lequelle on pose nos briques.
*/
class SnapShoot
{
	private:
		/*!
		 * \brief Liste des données
		*/
		std::vector<SnapShootData *> lstPosition;
		
	public:
		/*!
		 * \brief Constructor
		 * \param node Noeud contenant toutes les briquettes
		*/
		SnapShoot(SnapShoot * lastSnapShoot);
		/*!
		 * \brief Destructor
		*/
		~SnapShoot(); 

		/*!
		 * \brief Recherche la briquette dans les données
		 * \return La donnée trouvée sinon NULL
		*/
		SnapShootData * findData(ObjBriquette * briquette);

		/*!
		 * \brief Vérifie si la briquette existe dans les données
		 * \return Vrai ou faux
		*/
		bool existData(ObjBriquette * briquette);
		
		/*!
		 * \brief Nombre de données
		 * \return Le taille du vecteur "lstPosition"
		*/
		int getNumberData();
};


#endif //__SNAP_SHOOT_H__




