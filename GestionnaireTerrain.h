#pragma once

#include "ChunkManager.h"

class GestionnaireID;

namespace Ogre
{
	class TerrainGroup;
	class TerrainGlobalOptions;
	class Camera;
	class Viewport;
	class SceneManager;
	class TerrainLayerBlendMap;
	class Root;
}

/* Classe pour g�rer le terrain: gestionnaire de chunks, cr�ation et chargement des meshs... */
/* Classe non d�rivable */
/* S�mantique d'entit�, h�rite de boost::noncopyable */
class GestionnaireTerrain
{
public:

    /* Constructeur */
    GestionnaireTerrain(unsigned int tailleHeightMap, unsigned int tailleTerrain, Ogre::SceneManager *pSceneMgr, Ogre::Light *pSoleil, Ogre::Camera *pCam, Ogre::Viewport *pViewPort, Ogre::Root *pRoot, hkpWorld *pHavokWorld);

    /* Destructeur */
    ~GestionnaireTerrain();

    /* Renvoie l'adresse de l'objet TerrainGlobalOptions */
    Ogre::TerrainGlobalOptions* getOptions() const;

    /* Renvoie l'adresse de l'objet TerrainGroup */
    Ogre::TerrainGroup* getTerrains() const;

    /* Ajoute un terrain */
    /* x et y, sont les coordonn�es du terrain dans le groupe */
    /* Retourne un ID correspondant au terrain */
    /* L�ve une exception s'il n'y a plus de slot de terrain */
    unsigned long addTerrain(int x, int y, std::string nom);

	/* Renvoie l'adresse du gestionnaire de chunks (frameListener) */
	ChunkManager* getPtrChunk();

private:

    unsigned int mTailleTerrain, mTailleHeightMap;

    Ogre::SceneManager *mpSceneMgr;
    Ogre::TerrainGroup *mpTerrainGroup;
    Ogre::TerrainGlobalOptions *mpOptions;
    Ogre::Light *mpSoleil;
	Ogre::Root *mpRoot;

	hkpWorld *mpHavokWorld;
	ChunkManager *mpChunksMgn;

    GestionnaireID *mpIDGestion;

    std::map<unsigned long, std::pair<int, int>> mID_XY;
};
