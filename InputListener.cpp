#include "InputListener.h"

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreRenderWindow.h>
#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>
#include <OIS//OISInputManager.h>

using namespace Ogre;

InputListener::InputListener(RenderWindow *pWindow, Camera *pCam)
{
	mpWindow = pWindow;
	mpCamera = pCam;

	mToucheAppuyee = false;
	mVitesse = 600.0;
	mVitesseRotation = 0.25;

	startOIS(); //Initialisation d'OIS
}

InputListener::~InputListener()
{
	WindowEventUtilities::removeWindowEventListener(mpWindow, this);    //On d�r�f�rence cet �couteur d'�v�nements
	windowClosed(mpWindow); //Appel�e manuellement dans le destructeur si on ferme sans utiliser la croix
}

bool InputListener::frameRenderingQueued(const FrameEvent& evt)
{
	/* Si la fen�tre s'est ferm�e on coupe Ogre */
	if (mpWindow->isClosed())
	{
		return false;
	}

	/* Mise � jour des p�riph�riques d'entr�e */
	mpMouse->capture();
	mpKeyBoard->capture();

	/* On arr�te Ogre si ECHAP est enfonc�e */
	if (mpKeyBoard->isKeyDown(OIS::KC_ESCAPE))
	{
		return false;
	}

	/* De m�me pour alt+F4 */
	if (mpKeyBoard->isKeyDown(OIS::KC_F4) && mpKeyBoard->isModifierDown(OIS::Keyboard::Modifier::Alt))
	{
		return false;
	}

	Ogre::Vector3 deplacement = Ogre::Vector3::ZERO;    //Vecteur de d�placement
	mMouvement = mVitesse * evt.timeSinceLastFrame; //Valeur du d�placement en fonction des FPS

	/* La touche A d'un clavier QWERTY correspond au Q sur un AZERTY */
	if(mpKeyBoard->isKeyDown(OIS::KC_LEFT) || mpKeyBoard->isKeyDown(OIS::KC_A))
	{
		deplacement.x -= mMouvement;
	}
	if(mpKeyBoard->isKeyDown(OIS::KC_RIGHT) || mpKeyBoard->isKeyDown(OIS::KC_D))
	{
		deplacement.x += mMouvement;
	}
	if(mpKeyBoard->isKeyDown(OIS::KC_UP) || mpKeyBoard->isKeyDown(OIS::KC_W)) // W correspond au Z du AZERTY
	{
		deplacement.z -= mMouvement;
	}
	if(mpKeyBoard->isKeyDown(OIS::KC_DOWN) || mpKeyBoard->isKeyDown(OIS::KC_S))
	{
		deplacement.z += mMouvement;
	}

	/* On r�cup�re l'�tat de la souris */
	const OIS::MouseState &mouseState = mpMouse->getMouseState();

	/* On calcule la rotation � partir des coordonn�es relatives � la derni�re position */
	mRotationX = Degree(-mouseState.Y.rel * mVitesseRotation);
	mRotationY = Degree(-mouseState.X.rel * mVitesseRotation);

	/* Enfin on d�place la cam�ra */
	mpCamera->yaw(mRotationY);
	mpCamera->pitch(mRotationX);
	mpCamera->moveRelative(deplacement);

	return true;    //Ogre continue
}

void InputListener::startOIS()
{
	LogManager::getSingletonPtr()->logMessage("**** Init OIS ****");

	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	/* On r�cup�re les infos sur la fen�tre depuis l'OS */
	mpWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	/* On cr�e le gestionnaire */
	mpInputManager = OIS::InputManager::createInputSystem(pl);

	/* On cr�e les objets relatifs � chaque p�riph�rique */
	mpMouse = static_cast<OIS::Mouse*>(mpInputManager->createInputObject(OIS::OISMouse, false));
	mpKeyBoard = static_cast<OIS::Keyboard*>(mpInputManager->createInputObject(OIS::OISKeyboard, false));

	windowResized(mpWindow);    //On appelle manuellement cette m�thode une fois pour initialiser la taille de la fen�tre

	WindowEventUtilities::addWindowEventListener(mpWindow, this);   //On lie l'�couteur avec la fen�tre
}

void InputListener::windowResized(RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;

	/* On r�cup�re les nouvelles dimensions/positions de la fen�tre */
	rw->getMetrics(width, height, depth, left, top);

	/* On r�cup�re l'�tat de la souris */
	const OIS::MouseState &ms = mpMouse->getMouseState();

	/* On le met � jour avec les nouvelles valeurs */
	ms.width = width;
	ms.height = height;
}

void InputListener::windowClosed(RenderWindow* rw)
{
	if (rw == mpWindow)  //Si la fen�tre ferm�e est bien la notre
	{
		/* On test si le gestionnaire existe toujours. On d�truit les objets du gestionnaire, puis le gestionnaire */
		if (mpInputManager != nullptr)  
		{
			mpInputManager->destroyInputObject(mpMouse);
			mpInputManager->destroyInputObject(mpKeyBoard);

			OIS::InputManager::destroyInputSystem(mpInputManager);

			mpInputManager = nullptr;
		}
	}
}