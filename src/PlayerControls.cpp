#include "PlayerControls.h"

template<> PlayerControls * ClassRootSingleton<PlayerControls>::_instance = NULL;

PlayerControls::PlayerControls() : ClassRootSingleton<PlayerControls>()
{    
	this->resetControls();
	
	this->setMouseMovedActif(true);

    this->setDefaultKeys();

    ListenerKeyboard::getSingletonPtr()->signalKeyPressed.add(&PlayerControls::keyboardPressed, this);
    ListenerKeyboard::getSingletonPtr()->signalKeyReleased.add(&PlayerControls::keyboardReleased, this);
    ListenerMouse::getSingletonPtr()->signalMouseMoved.add(&PlayerControls::mouseMoved, this);
    ListenerMouse::getSingletonPtr()->signalMousePressed.add(&PlayerControls::mousePressed, this);
    ListenerMouse::getSingletonPtr()->signalMouseReleased.add(&PlayerControls::mouseReleased, this);
}

PlayerControls::~PlayerControls()
{
    ListenerKeyboard::getSingletonPtr()->signalKeyPressed.remove(&PlayerControls::keyboardPressed, this);
    ListenerKeyboard::getSingletonPtr()->signalKeyReleased.remove(&PlayerControls::keyboardReleased, this);
    ListenerMouse::getSingletonPtr()->signalMouseMoved.remove(&PlayerControls::mouseMoved, this);
    ListenerMouse::getSingletonPtr()->signalMousePressed.remove(&PlayerControls::mousePressed, this);
    ListenerMouse::getSingletonPtr()->signalMouseReleased.remove(&PlayerControls::mouseReleased, this);
}

void PlayerControls::setDefaultKeys()
{
	this->setMouseControl(Controls::SELECT, OIS::MB_Left);
	
	this->setKeyControl(Controls::CAM_MOVE_RIGHT, OIS::KC_RIGHT);
	this->setKeyControl(Controls::CAM_MOVE_LEFT, OIS::KC_LEFT);
	this->setKeyControl(Controls::CAM_MOVE_UP, OIS::KC_UP);
	this->setKeyControl(Controls::CAM_MOVE_DOWN, OIS::KC_DOWN);
	this->setKeyControl(Controls::CAM_ZOOM_IN, OIS::KC_H);
	this->setKeyControl(Controls::CAM_ZOOM_OUT, OIS::KC_N);
	this->setKeyControl(Controls::CAM_ROTATE_LEFT, OIS::KC_Q);
	this->setKeyControl(Controls::CAM_ROTATE_RIGHT, OIS::KC_D);
    
	this->setKeyControl(Controls::OPEN_MENU, OIS::KC_ESCAPE);
	this->setKeyControl(Controls::QUIT, OIS::KC_F10);
	this->setKeyControl(Controls::UNDO, OIS::KC_U);
	this->setKeyControl(Controls::SAVE, OIS::KC_S);
	this->setKeyControl(Controls::SUPPR, OIS::KC_DELETE);
	
	this->setKeyControl(Controls::OPEN_MENU, OIS::KC_ESCAPE);
}

void PlayerControls::resetControls(void)
{
	this->setMouseMovedActif(false);
	
	this->listKeyControl.resize(PlayerControls::maxOISKeyControl);
	for(unsigned int i = 0 ; i < this->listKeyControl.size() ; i++)
		this->listKeyControl[i] = Controls::NONE;
		
	this->listMouseControl.resize(PlayerControls::maxOISMouseControl);
	for(unsigned int i = 0 ; i < this->listMouseControl.size() ; i++)
		this->listMouseControl[i] = Controls::NONE;
}

void PlayerControls::setKeyControl(const Controls::Controls keyControl, const OIS::KeyCode key)
{
	if(key <= PlayerControls::maxOISKeyControl)
	{
		for(unsigned int i = 0 ; i < this->listMouseControl.size() ; i++)
		{
			if(this->listMouseControl[i] == keyControl)
				this->listMouseControl[i] = Controls::NONE;
		}
		for(unsigned int i = 0 ; i < this->listKeyControl.size() ; i++)
		{
			if(this->listKeyControl[i] == keyControl)
				this->listKeyControl[i] = Controls::NONE;
		}		
		this->listKeyControl[key] = keyControl;
	}
}

void PlayerControls::setMouseControl(const Controls::Controls keyControl, const OIS::MouseButtonID mouseId)
{
	if(mouseId <= PlayerControls::maxOISMouseControl)
	{
		for(unsigned int i = 0 ; i < this->listMouseControl.size() ; i++)
		{
			if(this->listMouseControl[i] == keyControl)
				this->listMouseControl[i] = Controls::NONE;
		}
		for(unsigned int i = 0 ; i < this->listKeyControl.size() ; i++)
		{
			if(this->listKeyControl[i] == keyControl)
				this->listKeyControl[i] = Controls::NONE;
		}		
		this->listMouseControl[mouseId] = keyControl;
	}
}

void PlayerControls::keyboardPressed(const OIS::KeyEvent &evt)
{
    Controls::Controls key = this->OISEventToControlKey(evt);
    if(key != Controls::NONE)
    {
         this->signalKeyPressed.dispatch(key);
    }
}

void PlayerControls::keyboardReleased(const OIS::KeyEvent &evt)
{
    Controls::Controls key = this->OISEventToControlKey(evt);
    if(key != Controls::NONE)
    {
        this->signalKeyReleased.dispatch(key);
    }
}

void PlayerControls::mouseMoved(Ogre::Vector3 vect)
{
	if(this->getMouseMovedActif())
		this->signalMouseMoved.dispatch(vect);
}

void PlayerControls::mousePressed(const OIS::MouseButtonID evt)
{
    Controls::Controls key = this->OISEventToControlKey(evt);
    if(key != Controls::NONE)
    {
         this->signalKeyPressed.dispatch(key);
    }
}

void PlayerControls::mouseReleased(const OIS::MouseButtonID evt)
{
    Controls::Controls key = this->OISEventToControlKey(evt);
    if(key != Controls::NONE)
    {
         this->signalKeyReleased.dispatch(key);
    }
}

Controls::Controls PlayerControls::OISEventToControlKey(const OIS::KeyEvent &evt)
{
	Controls::Controls key = this->listKeyControl[evt.key];
	
	return key;
}


Controls::Controls PlayerControls::OISEventToControlKey(const OIS::MouseButtonID evt)
{
	Controls::Controls key = this->listMouseControl[evt];
	
	return key;
}

void PlayerControls::suspendre_ecoute()
{
    ListenerKeyboard::getSingletonPtr()->signalKeyPressed.remove(&PlayerControls::keyboardPressed, this);
    ListenerKeyboard::getSingletonPtr()->signalKeyReleased.remove(&PlayerControls::keyboardReleased, this);
    ListenerMouse::getSingletonPtr()->signalMousePressed.remove(&PlayerControls::mousePressed, this);
    ListenerMouse::getSingletonPtr()->signalMouseMoved.remove(&PlayerControls::mouseMoved, this);
    ListenerMouse::getSingletonPtr()->signalMouseReleased.remove(&PlayerControls::mouseReleased, this);
}

void PlayerControls::reprendre_ecoute()
{
    ListenerKeyboard::getSingletonPtr()->signalKeyPressed.add(&PlayerControls::keyboardPressed, this);
    ListenerKeyboard::getSingletonPtr()->signalKeyReleased.add(&PlayerControls::keyboardReleased, this);
    ListenerMouse::getSingletonPtr()->signalMouseMoved.add(&PlayerControls::mouseMoved, this);
    ListenerMouse::getSingletonPtr()->signalMousePressed.add(&PlayerControls::mousePressed, this);
    ListenerMouse::getSingletonPtr()->signalMouseReleased.add(&PlayerControls::mouseReleased, this);
}

bool PlayerControls::getMouseMovedActif()
{
	return this->mouseMovedActif;
}

void PlayerControls::setMouseMovedActif(bool mouseMovedActif)
{
	this->mouseMovedActif = mouseMovedActif;
}
