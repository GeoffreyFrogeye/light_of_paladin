#pragma once

#include <OgreFrameListener.h>

#include "Structures.h"

namespace Ogre
{
	class Camera;
}

class hkpRigidBody;
class GestionnaireTerrain;
class Chunk;

class ChunkManager: public Ogre::FrameListener
{
private:
	TableauChunks mActualChunk;
	int mMaxChunkCoo;
	Chunk ***mpppChunks;
	std::pair<int, int> mOffset;
	GestionnaireTerrain *mpGestTerrain;
	Ogre::Camera* mpCam;

public:

	/* Constructeur */
	/* pCam, pointeur sur la cam�ra d'Ogre (pour conna�tre la position du joueur) */
	/* pTerrainMgr, pointeur sur les gestionnaire de terrain */
	/* DEBUG: assert si la taille du monde n'est pas un multiple de la taille d'un chunk */
	ChunkManager(Ogre::Camera *pCam, GestionnaireTerrain *pTerrainMgr);

	virtual ~ChunkManager();

	/* Cr�e un �l�ment du terrain */
	/* coo, une paire d'entier repr�sentant les coordonn�es du chunk dans la grille */
	/* Renvoie true si le terrain a bien �t� g�n�r�, l'op�ration peut �chouer si le couple(x,y) est incorrect */
	bool createChunk(std::pair<int, int> coo);

	/* Enregistre un �l�ment de terrain dans la grille (3x3) */
	/* coo, une paire d'entier repr�sentant les coordonn�es du chunk dans la grille */
	void addChunkInGrid(hkpRigidBody* pRigidBody, std::pair<int, int> coo);

	/* Supprime de la m�moire le chunk */
	/* coo, une paire d'entier repr�sentant les coordonn�es du chunk dans la grille */
	/* Renvoie True si un chunk a �t� d�truit, False s'il n'y en avait pas pour ces coordonn�es */
	bool destroyChunk(std::pair<int, int> coo);

	/* Renvoie un tableau de 9 chunks  avec celui o� se trouve le joueur au centre */
	/* Si le joueur est au bord de la map certains pointeurs seront nullptr */
	TableauChunks const& getCurrentChunks() const;

	/* Mise � jour des chunks en fonction de la position du joueur */
	virtual bool frameRenderingQueued(Ogre::FrameEvent const& rEv) override; 
};