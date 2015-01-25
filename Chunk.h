#pragma once

#include <Ogre.h>

#include "Structures.h"

class GestionnaireTerrain;
class HeightFieldShape;

class Chunk: public Ogre::FrameListener
{
private:
	TableauChunks mActualChunk;
	unsigned int mSizeMap, mChunkSize, mMaxChunkCoo;
	HeightFieldShape **mppChunks;
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
	bool addChunkPtr(HeightFieldShape* pShape, unsigned int x, unsigned int y);

	/* Valide la construction de la grille de chunks, tous les chunks doivent avoir �t� ajout�s, sinon l�ve une exception */
	void ready();

	/* Supprime le chunk enregistr� en x et y dans la grille */
	bool removeChunkPtr(unsigned int x, unsigned int y);

	/* Renvoie un tableau de 9 chunks (ou moins) avec celui o� se trouve le joueur au centre */
	TableauChunks const& getCurrentChunks() const;

	/* Mise � jour des chunks */
	/* L�ve une exception si les chunks ne sont pas 'ready' */
	virtual bool frameRenderingQueued(Ogre::FrameEvent const& rEv) override; 
};