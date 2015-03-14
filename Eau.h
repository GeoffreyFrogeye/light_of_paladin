#pragma once

#include <OgreFrameListener.h>
#include <boost/noncopyable.hpp>

namespace Hydrax
{
	class Hydrax;
}

namespace SkyX
{
	class SkyX;
}

/* Classe non d�rivable pour g�rer l'eau, h�rite de Ogre::FrameListener */
/* S�mantique d'entit�, h�rite de boost::noncopyable */
/* Doit �tre ajouter � la liste des frameListener de Ogre */
class Eau: public Ogre::FrameListener, private boost::noncopyable
{
private:

	Hydrax::Hydrax* mpHydrax;
	SkyX::SkyX* mpSky;
	Ogre::Real mH;
	bool mNeedUpdate;

public:

	/* Constructeur */
	/* pMgn, pointeur vers le SceneManager */
	/* pCam, pointeur sur la cam�ra */
	/* pView, pointeur sur le viewPort */
	/* pSky, pointeur vers l'objet SkyX qui repr�sente le ciel */
	Eau(Ogre::SceneManager* pMgn, Ogre::Camera* pCam, Ogre::Viewport* pView, SkyX::SkyX* pSky);

	/* Destructeur */
	virtual ~Eau();

	/* D�finie la hauteur de l'eau */
	/* h, la hauteur en coordonn�es du monde (m�tres) */
	void setHauteur(Ogre::Real h);

	/* Renvoie la hauteur actuelle de l'eau */
	Ogre::Real getHauteur() const;

	/* Initialise Hydrax avec les valeurs fournies et d�marre le rendu */
	/* Renvoie true si cette m�thode avait d�j� �tait appel�e */
	bool create();

	/* Renvoie l'adresse du gestionnaire hydrax */
	Hydrax::Hydrax* getHydrax() const;

	bool frameStarted(Ogre::FrameEvent const& rEvt) override;
};