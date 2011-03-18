#include "PlayerControls.h"

#include "Utils.h"

PlayerControls * PlayerControls::_instance = NULL;


void PlayerControls::createSingleton()
{
	if (_instance == NULL)
	{
		_instance = new PlayerControls();
	}
}

PlayerControls * PlayerControls::getSingletonPtr()
{
	if (_instance == NULL)
	{
		_instance = new PlayerControls();
	}
	return _instance;
}

PlayerControls & PlayerControls::getSingleton()
{
	if (_instance == NULL)
	{
		_instance = new PlayerControls();
	}
	return *_instance;
}

void PlayerControls::destroySingleton()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}



PlayerControls::PlayerControls()
{    
	this->resetControls();
	
	this->setMouseMovedActif(true);

    this->setDefaultKeys();
    
    this->keyboard = ListenerKeyboard::getSingletonPtr();
    this->mouse = ListenerMouse::getSingletonPtr();

    this->keyboard->signalKeyPressed.add(&PlayerControls::keyboardPressed, this);
    this->keyboard->signalKeyReleased.add(&PlayerControls::keyboardReleased, this);
    this->mouse->signalMouseMoved.add(&PlayerControls::mouseMoved, this);
    this->mouse->signalMousePressed.add(&PlayerControls::mousePressed, this);
    this->mouse->signalMouseReleased.add(&PlayerControls::mouseReleased, this);
}

PlayerControls::~PlayerControls()
{
    this->keyboard->signalKeyPressed.remove(&PlayerControls::keyboardPressed, this);
    this->keyboard->signalKeyReleased.remove(&PlayerControls::keyboardReleased, this);
    this->mouse->signalMouseMoved.remove(&PlayerControls::mouseMoved, this);
    this->mouse->signalMousePressed.remove(&PlayerControls::mousePressed, this);
    this->mouse->signalMouseReleased.remove(&PlayerControls::mouseReleased, this);
}

void PlayerControls::setDefaultKeys()
{
	this->setMouseControl(PlayerControls::SELECT, OIS::MB_Left);
	
	this->setKeyControl(PlayerControls::CAM_MOVE_RIGHT, OIS::KC_RIGHT);
	this->setKeyControl(PlayerControls::CAM_MOVE_LEFT, OIS::KC_LEFT);
	this->setKeyControl(PlayerControls::CAM_MOVE_UP, OIS::KC_UP);
	this->setKeyControl(PlayerControls::CAM_MOVE_DOWN, OIS::KC_DOWN);
	this->setKeyControl(PlayerControls::CAM_ZOOM_IN, OIS::KC_H);
	this->setKeyControl(PlayerControls::CAM_ZOOM_OUT, OIS::KC_N);
	this->setKeyControl(PlayerControls::OPEN_MENU, OIS::KC_ESCAPE);
	this->setKeyControl(PlayerControls::QUIT, OIS::KC_F10);
	this->setKeyControl(PlayerControls::UNDO, OIS::KC_U);
	this->setKeyControl(PlayerControls::SAVE, OIS::KC_S);
	this->setKeyControl(PlayerControls::SUPPR, OIS::KC_DELETE);
	
	this->setKeyControl(PlayerControls::OPEN_MENU, OIS::KC_ESCAPE);
}

void PlayerControls::resetControls(void)
{
	this->setMouseMovedActif(false);
	
	this->listKeyControl.resize(PlayerControls::maxOISKeyControl);
	for(unsigned int i = 0 ; i < this->listKeyControl.size() ; i++)
		this->listKeyControl[i] = PlayerControls::NONE;
		
	this->listMouseControl.resize(PlayerControls::maxOISMouseControl);
	for(unsigned int i = 0 ; i < this->listMouseControl.size() ; i++)
		this->listMouseControl[i] = PlayerControls::NONE;
}

void PlayerControls::setKeyControl(const PlayerControls::Controls keyControl, const OIS::KeyCode key)
{
	if(key <= PlayerControls::maxOISKeyControl)
	{
		for(unsigned int i = 0 ; i < this->listMouseControl.size() ; i++)
		{
			if(this->listMouseControl[i] == keyControl)
				this->listMouseControl[i] = PlayerControls::NONE;
		}
		for(unsigned int i = 0 ; i < this->listKeyControl.size() ; i++)
		{
			if(this->listKeyControl[i] == keyControl)
				this->listKeyControl[i] = PlayerControls::NONE;
		}		
		this->listKeyControl[key] = keyControl;
	}
}

void PlayerControls::setMouseControl(const PlayerControls::Controls keyControl, const OIS::MouseButtonID mouseId)
{
	if(mouseId <= PlayerControls::maxOISMouseControl)
	{
		for(unsigned int i = 0 ; i < this->listMouseControl.size() ; i++)
		{
			if(this->listMouseControl[i] == keyControl)
				this->listMouseControl[i] = PlayerControls::NONE;
		}
		for(unsigned int i = 0 ; i < this->listKeyControl.size() ; i++)
		{
			if(this->listKeyControl[i] == keyControl)
				this->listKeyControl[i] = PlayerControls::NONE;
		}		
		this->listMouseControl[mouseId] = keyControl;
	}
}

void PlayerControls::keyboardPressed(const OIS::KeyEvent &evt)
{
    Controls key = this->OISEventToControlKey(evt);
    if(key != PlayerControls::NONE)
    {
         this->signalKeyPressed.dispatch(key);
    }
}

void PlayerControls::keyboardReleased(const OIS::KeyEvent &evt)
{
    Controls key = this->OISEventToControlKey(evt);
    if(key != PlayerControls::NONE)
    {
        this->signalKeyReleased.dispatch(key);
    }
}

void PlayerControls::mouseMoved(Ogre::Vector3 vect)
{
	if(this->getMouseMovedActif())
		this->signalMouseMoved.dispatch(vect);
}

void PlayerControls::mousePressed(OIS::MouseButtonID evt)
{
    Controls key = this->OISEventToControlKey(evt);
    if(key != PlayerControls::NONE)
    {
         this->signalKeyPressed.dispatch(key);
    }
}

void PlayerControls::mouseReleased(OIS::MouseButtonID evt)
{
    Controls key = this->OISEventToControlKey(evt);
    if(key != NONE)
    {
         this->signalKeyReleased.dispatch(key);
    }
}

PlayerControls::Controls PlayerControls::OISEventToControlKey(const OIS::KeyEvent &evt)
{
	PlayerControls::Controls key = this->listKeyControl[evt.key];
	
	return key;
}


PlayerControls::Controls PlayerControls::OISEventToControlKey(const OIS::MouseButtonID evt)
{
	PlayerControls::Controls key = this->listMouseControl[evt];
	
	return key;
}

void PlayerControls::suspendre_ecoute()
{
    this->keyboard->signalKeyPressed.remove(&PlayerControls::keyboardPressed, this);
    this->keyboard->signalKeyReleased.remove(&PlayerControls::keyboardReleased, this);
    this->mouse->signalMousePressed.remove(&PlayerControls::mousePressed, this);
    this->mouse->signalMouseMoved.remove(&PlayerControls::mouseMoved, this);
    this->mouse->signalMouseReleased.remove(&PlayerControls::mouseReleased, this);
}

void PlayerControls::reprendre_ecoute()
{
    this->keyboard->signalKeyPressed.add(&PlayerControls::keyboardPressed, this);
    this->keyboard->signalKeyReleased.add(&PlayerControls::keyboardReleased, this);
    this->mouse->signalMouseMoved.add(&PlayerControls::mouseMoved, this);
    this->mouse->signalMousePressed.add(&PlayerControls::mousePressed, this);
    this->mouse->signalMouseReleased.add(&PlayerControls::mouseReleased, this);
}

bool PlayerControls::getMouseMovedActif()
{
	return this->mouseMovedActif;
}

void PlayerControls::setMouseMovedActif(bool mouseMovedActif)
{
	this->mouseMovedActif = mouseMovedActif;
}
