#pragma once

#include <OgrePrerequisites.h>
#include <OgreMath.h>
#include <OgreFrameListener.h>
#include <OgreWindowEventUtilities.h>

class CeguiMgr;

namespace Ogre
{
	class RenderWindow;
	class Camera;
}

namespace OIS
{
	class InputManager;
	class Mouse;
	class Keyboard;
}

/* Classe pour g�rer les entr�es utilisateurs */
/* H�rite de Ogre::FrameListener et Ogre::WindowEventListener */
class InputListener: public Ogre::FrameListener, Ogre::WindowEventListener
{
public:

    /* Constructeur */
    /* pWindow, pointeur sur la fen�tre de rendue de Ogre */
    /* pCam, pointeur sur la cam�ra */
    InputListener(Ogre::RenderWindow *pWindow, Ogre::Camera *pCam, CeguiMgr *pCEGUI);

    /* Destructeur */
    virtual ~InputListener();

    /* S'ex�cute pendant le rendu */
    /* Renvoie false si le programme doit s'arr�ter */
    bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;

    /* Initialise OIS, appel�e par le constructeur */
    void startOIS();

    /* Appel�e lors du redimensionnement de la fen�tre */
    virtual void windowResized(Ogre::RenderWindow* rw) override;

    /* Appel�e lors de la fermeture de la fen�tre */
    virtual void windowClosed(Ogre::RenderWindow* rw) override;

protected:
    Ogre::RenderWindow *mpWindow;
    Ogre::Camera *mpCamera;

    OIS::InputManager *mpInputManager;
    OIS::Mouse *mpMouse;
    OIS::Keyboard *mpKeyBoard;

    CeguiMgr *mpCEGUIMgr;

    Ogre::Real mMouvement;
    Ogre::Real mVitesse;
    Ogre::Real mVitesseRotation;

    Ogre::Radian mRotationX;
    Ogre::Radian mRotationY;
};