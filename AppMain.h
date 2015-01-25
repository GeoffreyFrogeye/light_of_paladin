#pragma once

#include <OGRE/Ogre.h>
#include <Ogre/Terrain/OgreTerrain.h>

#include <SkyX.h>
#include <PagedGeometry.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <Physics2012/Dynamics/hkpDynamics.h>
#include <Physics2012/Dynamics/World/hkpWorld.h>

#include <map>

#include "Eau.h"
#include "Lumiere.h"
#include "HeightFieldShape.h"
#include "Structures.h"

class GestionnaireTerrain;
class Personnage;
class Item;
class Inventaire;

class AppMain
{
protected:
	Ogre::Root *mpRoot;
	Ogre::RenderWindow *mpWindow;
	Ogre::SceneManager *mpSceneMgr;
	Ogre::Camera *mpCam;

	CEGUI::OgreRenderer *mpCeguiMain;

	GestionnaireTerrain *mpTerrain;
	Eau *mpWater;
	GestionnaireLight* mpLum;

	SkyX::SkyX *mpSky;
	Forests::PagedGeometry *mpTrees;

	hkpWorld *mpHkWorld;

	std::map<std::string, Personnage*> mmapPersonnages;
	std::map<std::string, Item*> mmapItem;
	std::map<std::string, Inventaire*> mmapInventaire;

public:

	/* Constructeur */
	AppMain();

	/* Destructeur */
	virtual ~AppMain();

	/* Lance le jeu */
	/* Retourne toujours true (syst�me d'exception si erreur) */
	void start();

	/* Cr�e la sc�ne, appel�e par start() */
	/* Retourne false en cas d'erreur */
	bool createScene();

	/* Cr�e les �l�ments basiques de la sc�ne, viewport, cam�ra, �clairage ambient */
	/* Appel�e par createScene() */
	/* Retourne false en cas d'erreur */
	bool createBase();

	/* Cr�e le terrain */
	/* Appel�e par createScene() */
	/* Retourne false en cas d'erreur */
	bool createTerrain();

	/* Cr�e le ciel */
	/* Appel�e par createScene() */
	/* Retourne false en cas d'erreur */
	bool createSky();

	/* Cr�e les objets autres que les personnages */
	/* Appel�e par createScene() */
	/* Retourne false en cas d'erreur */
	bool createObject();

	/* Cr�e les personnages */
	/* Appel�e par createScene() */
	/* Retourne false en cas d'erreur */
	bool createPersonnage();

	/* Cr�e et enregistre le gestionnaire des lumi�res */
	/* Appel�e par createScene() */
	/* Retourne false en cas d'erreur */
	bool createLight();

	/* Charge et initialise Ogre, appel�e par start() */
	/* Retourne false en cas d'erreur */
	bool initOGRE();

	/* Lance la boucle de rendu, appel�e par start() */
	void infiniteLoop();

	/* Ajoute un nouveau Personnage */
	/* Retourne false en cas d'erreur */
	bool ajoutPersonnage(Ogre::SceneNode *pNoeud, std::string nom, int stat[EStat::ESTATMAX], int niveau, int XP, Ogre::Vector3 position, Ogre::Vector3 rotation);

	/* Retourne un personnage en fonction de son nom */
	/* Renvoie un pointeur vers ce personnage */
	/* L�ve une exception sinon */
	Personnage* getPersonnage(std::string nom) const;

	/* Initialise Havok */
	bool initHavok();
};