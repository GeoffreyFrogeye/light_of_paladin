#pragma once

#include <OgreFrameListener.h>

#include "Structures.h"

namespace Ogre
{
	class Camera;
}

class hkpRigidBody;
class GestionnaireTerrain;

class Chunk: public Ogre::FrameListener
{
private:
	TableauChunks mActualChunk;
	unsigned int mSizeMap, mChunkSize, mMaxChunkCoo;
	hkpRigidBody **mppChunks;
	bool mReady;
	GestionnaireTerrain *mpGestTerrain;
	Ogre::Camera* mpCam;

public:

	/* Constructeur */
	/* sizeMap, taille du monde */
	/* chunkSize, taille d'un chunk en m�tres */
	Chunk(unsigned int sizeMap, unsigned int chunkSize, GestionnaireTerrain* pGestTer, Ogre::Camera *pCam);

	virtual ~Chunk();

	/* Ajoute l'adresse d'un �l�ment du terrain */
	/* pShape, un �l�ment du terrain de la taille pass�e en param�tre au constructeur */
	/* x, la position en x du chunk dans la grille */
	/* y, la position en y du chunk dans la grille */
	/* Note: Acquiert une r�f�rence sur l'objet */
	bool addChunkPtr(hkpRigidBody* pBody, unsigned int x, unsigned int y);

	/* Valide la construction de la grille de chunks, tous les chunks doivent avoir �t� ajout�s, sinon l�ve une exception */
	void ready();

	/* Supprime le chunk enregistr� en x et y dans la grille */
	/* Lib�re la r�f�rence */
	/* L'objet peut s'auto-d�truire */
	bool removeChunkPtr(unsigned int x, unsigned int y);

	/* Renvoie un tableau de 9 chunks  avec celui o� se trouve le joueur au centre */
	/* Si le joueur est au bord de la map certains pointeurs seront nullptr */
	TableauChunks const& getCurrentChunks() const;

	/* Mise � jour des chunks */
	/* L�ve une exception si les chunks ne sont pas 'ready' */
	virtual bool frameRenderingQueued(Ogre::FrameEvent const& rEv) override; 
};