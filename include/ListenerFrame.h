/*!
 *  \file  ListenerFrame.h
 * \brief Ce fichier contient la déclaration de la classe ListenerFrame. C'est la classe gérant les événements de la mise à jour du rendu.
 */
#ifndef __LISTENER_FRAME_H__
#define __LISTENER_FRAME_H__

#include <iostream>
#include <Ogre.h>
#include "Signal.h"
#include "ClassRootSingleton.h"
//#include "Application.h"

class Application;

/*!
 * \class ListenerFrame
 * \brief Classe permettant de gérer les événements de la mise à jour du rendu.
 */
class ListenerFrame : public ClassRootSingleton<ListenerFrame>, public Ogre::FrameListener
{
    private :
        /*!
         * \brief Indique si l'application est fermée
         */
		bool closed;
		
	public:
        /*!
         * \brief Dispatche le signal à chaque image. N'a aucun argument.
         */
        Signal<void *> signalFrameRendering;
         /*!
         * \brief Dispatche le signal à chaque début d'image. 
         */
        Signal<const Ogre::FrameEvent&> signalFrameStarted;
        /*!
         * \brief Dispatche le signal à chaque fin d'image. 
         */
        Signal<const Ogre::FrameEvent&> signalFrameEnded;
        
        		
	public:
		/*!
		 * \brief Constructeur
		 */
		ListenerFrame(){std::cerr<<"Le constructeur de listenerFrame ne doit pas être appelé via createSingleton() (ou createSingletonPtr()) et doit être appelé avec un Ogre::Root * en argument!" <<std::endl;};
		ListenerFrame(Ogre::Root *);
		/*!
		 * \brief Destructeur
		 */
		~ListenerFrame();
		
		/*!
		 * \brief Génère la frame de rendu
		 * \param evt Evénement de la frame
		 * \return Si on arrête l'application
		 */
        bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		/*!
		 * \brief Comportement avnt génération de la frame
		 * \param evt Evénement de la frame
		 * \return Si on arrête l'application
		 */
		bool frameStarted(const Ogre::FrameEvent& evt);
		/*!
		 * \brief Comportement après génération de la frame
		 * \param evt Evénement de la frame
		 * \return Si on arrête l'application
		 */
		bool frameEnded(const Ogre::FrameEvent& evt);
		
		/*!
         * \brief Appelée lorsque l'application est fermée
         */
        void shutdown();
		/*!
        * \brief Appelée lorsque l'application est fermée
        */
        void shutdown(void *);
};

#endif //__LISTENER_FRAME_H__


