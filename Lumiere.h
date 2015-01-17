#pragma once

#include <Ogre.h>
#include <SkyX.h>

#include "Eau.h"

/* Classe non d�rivable pour g�rer les diff�rentes lumi�res de la sc�nes et les mettre � jour, h�rite FrameListener */
/* S�mantique d'entit� */
class GestionnaireLight: public Ogre::FrameListener
{
private:

	/* Constructeur par copie interdit */
	GestionnaireLight(GestionnaireLight const& rOriginal);

	/* Op�rateur d'assignement */
	GestionnaireLight& operator=(GestionnaireLight const& rOriginal);

	Ogre::Light* mpSoleil;
	Ogre::ColourValue mLumAmbiente;
	Ogre::SceneManager* mpSceneMgr;

	SkyX::SkyX* mpSky;
	Eau* mpEauMgr;

public:

	/* Constructeur */
	/* pSoleil, pointeur vers une Ogre::Light de type directional qui servira de soleil */
	/* pSky, pointeur vers l'objet SkyX qui s'occupe du ciel */
	/* pEau, pointeur vers les gestionnaire d'eau */
	/* lumAmbiente, Ogre::Vector3 qui contient la valeur de la lumi�re ambiente */
	GestionnaireLight(Ogre::SceneManager* pSceneMgr, Ogre::Light* pSoleil, SkyX::SkyX* pSky, Eau* pEau, Ogre::ColourValue lumAmbiente=Ogre::ColourValue(0.0f, 0.0f, 0.0f));

	/* Destructeur */
	~GestionnaireLight();

	/* Pr�dicat, renvoie true s'il fait nuit, false sinon */
	bool IsNuit() const;

	bool frameStarted(Ogre::FrameEvent const& rEvt) override;
};