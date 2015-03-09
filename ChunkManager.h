#pragma once

#include <OgreFrameListener.h>
#include <OgreVector3.h>

#include <boost/chrono/chrono.hpp>

#include "Structures.h"

namespace Ogre
{
	class Camera;
}

class hkpRigidBody;
class hkpWorld;
class GestionnaireTerrain;
class Chunk;

class ChunkManager: public Ogre::FrameListener
{
private:
	TableauChunks mActualChunk;
	int mMaxChunkCoo;
	GestionnaireTerrain *mpGestTerrain;
	hkpWorld *mpHavokWorld;
	Ogre::Camera* mpCam;
	Chunk*** mpppChunk;
	boost::chrono::system_clock::time_point mTimeCount;
	Ogre::Vector3 mOldOffset;

public:

	/* Constructeur */
	/* pCam, pointeur sur la cam�ra d'Ogre (pour conna�tre la position du joueur) */
	/* pTerrainMgr, pointeur sur les gestionnaire de terrain */
	/* DEBUG: assert si la taille du monde n'est pas un multiple de la taille d'un chunk */
	ChunkManager(Ogre::Camera *pCam, GestionnaireTerrain *pTerrainMgr, hkpWorld *pHavokWorld);

	virtual ~ChunkManager();

	/* Active un �l�ment du terrain */
	/* coo, une paire d'entier repr�sentant les coordonn�es du chunk dans la grille */
	/* Renvoie true si le terrain a bien �t� g�n�r�, l'op�ration peut �chouer si le couple(x,y) est incorrect */
	bool activeChunk(std::pair<int, int> coo);

	/* D�sactive le chunk */
	/* coo, une paire d'entier repr�sentant les coordonn�es du chunk dans la grille */
	/* Renvoie True si le chunk a �t� d�sactiv�, False sinon */
	bool releaseChunk(std::pair<int, int> coo);

	/* Renvoie un tableau de 9 chunks  avec celui o� se trouve le joueur au centre */
	/* Si le joueur est au bord de la map certains pointeurs seront nullptr */
	TableauChunks const& getCurrentChunks() const;

	/* Mise � jour des chunks en fonction de la position du joueur */
	virtual bool frameRenderingQueued(Ogre::FrameEvent const& rEv) override;

	/* Calcul la moyenne des moyennes de hauteur de chaque chunks */
	Ogre::Real averageLocalHeight() const;
};