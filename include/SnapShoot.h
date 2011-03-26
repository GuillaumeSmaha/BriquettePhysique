/*!
 *  \file  SnapShoot.h
 * \brief Ce fichier contient la déclaration de la classe SnapShoot. Gere la table du monde, qui correspond à l'objet statique sur lequelle on pose nos briques.
 */

#ifndef __SNAP_SHOOT_H__
#define __SNAP_SHOOT_H__

#include <vector>
#include <Ogre.h>
#include "GestObj.h"

/*!
* \class SnapShoot
* \brief Gere la table du monde, qui correspond à l'objet statique sur lequelle on pose nos briques.
*/
class SnapShoot
{
	private:
		/*!
		 * \brief Noeud contenant l'objet concerné par la modification
		*/
		Ogre::SceneNode * node;
		/*!
		 * \brief Objet concerné par la modification
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
		 * \brief Différence de position par rapport à l'étape précédente
		*/
		Ogre::Vector3 diffPosition;
		/*!
		 * \brief Différence d'orientation par rapport à l'étape précédente
		*/
		Ogre::Quaternion diffOrientation;
		
	public:
		/*!
		 * Constructor
		 * \param object Objet concerné par la modification
		 * \param diffPosition Différence de position par rapport à l'étape précédente
		*/
		SnapShoot(Ogre::SceneNode * node, ObjBriquette * object, Ogre::Vector3 diffPosition);
		/*!
		 * Constructor
		 * \param object Objet concerné par la modification
		 * \param diffOrientation Différence  d'orientation par rapport à l'étape précédente
		*/
		SnapShoot(Ogre::SceneNode * node, ObjBriquette * object, Ogre::Quaternion diffOrientation);
		/*!
		 * Constructor
		 * \param object Objet concerné par la modification
		 * \param diffPosition Différence de position par rapport à l'étape précédente
		 * \param diffOrientation Différence  d'orientation par rapport à l'étape précédente
		*/
		SnapShoot(Ogre::SceneNode * node, ObjBriquette * object, Ogre::Vector3 diffPosition, Ogre::Quaternion diffOrientation);
		/*!
		 * Destructor
		*/
		~SnapShoot();  
};


#endif //__SNAP_SHOOT_H__




