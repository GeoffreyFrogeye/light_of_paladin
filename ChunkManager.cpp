#include "ChunkManager.h"
#include "ExceptionPerso.h"
#include "HeightFieldShape.h"
#include "Chunk.h"

#include <boost/timer/timer.hpp>

#include <OgreCamera.h>
#include <Physics2012/Dynamics/World/hkpWorld.h>

using namespace Ogre;

ChunkManager::ChunkManager(Ogre::Camera *pCam, GestionnaireTerrain *pTerrainMgr, hkpWorld *pHavokWorld)
{
	assert(TAILLE_MONDE%TAILLE_CHUNK == 0);

	mMaxChunkCoo = TAILLE_MONDE / TAILLE_CHUNK;
	mpCam = pCam;
	mpGestTerrain = pTerrainMgr;
	mpHavokWorld = pHavokWorld;

	mpppChunk = new Chunk**[mMaxChunkCoo];

	for (int i=0; i<mMaxChunkCoo; ++i)
	{
		mpppChunk[i] = new Chunk*[mMaxChunkCoo];

		for (int j=0; j<mMaxChunkCoo; ++j)
		{
			mpppChunk[i][j] = new Chunk(pTerrainMgr, std::make_pair(i,j));
		}
	}

	mOldOffset = Vector3::ZERO;
	mActualChunk.positionJoueur = Vector3::ZERO;
}


ChunkManager::~ChunkManager()
{
	for (int i=0; i<mMaxChunkCoo; ++i)
	{
		for (int j=0; j<mMaxChunkCoo; ++j)
		{
			delete mpppChunk[i][j];
			mpppChunk[i][j] = nullptr;
		}
		delete[] mpppChunk[i];
		mpppChunk[i] = nullptr;
	}

	delete[] mpppChunk;
	mpppChunk = nullptr;

	mpGestTerrain=nullptr;
	mpCam=nullptr;
}

bool ChunkManager::activeChunk(std::pair<int, int> const& coo)
{
	if (coo.first >= mMaxChunkCoo || coo.second >= mMaxChunkCoo || coo.first < 0 || coo.second < 0)
	{
		return false;
	} 
	else
	{
		mpppChunk[coo.first][coo.second]->loadBody();
		return true;
	}
}

bool ChunkManager::releaseChunk(std::pair<int, int> const& coo)
{
	if (coo.first >= mMaxChunkCoo || coo.second >= mMaxChunkCoo || coo.first < 0 || coo.second < 0)
	{
		return false;
	}
	else
	{
		mpppChunk[coo.first][coo.second]->destroyBody();
		return true;
	}
}

TableauChunks const& ChunkManager::getCurrentChunks() const
{
	return mActualChunk;
}

bool ChunkManager::frameRenderingQueued(Ogre::FrameEvent const& rEv)
{
	boost::chrono::system_clock::time_point debut = boost::chrono::system_clock::now();

	boost::chrono::milliseconds elapsedTime = boost::chrono::duration_cast<boost::chrono::milliseconds>(debut - mTimeCount);
	static boost::chrono::milliseconds ref(1000);

	if (elapsedTime >= ref)
	{
		boost::timer::auto_cpu_timer timerStart;

		TableauChunks tmp;

		mpHavokWorld->lock();
		mpHavokWorld->markForWrite();

		for (Chunk* it : mActualChunk.vectPtrChunk)
		{
			mpHavokWorld->removeEntity((hkpEntity*)(it->getBodyPtr()));
		}
	
		Vector3 pos = mpCam->getDerivedPosition();
	
		tmp.positionJoueur = pos;
	
		/* Coordonnées du chunk sur lequel est le joueur */
		pos.x = Real(int(pos.x)/TAILLE_CHUNK);
		pos.z = Real(int(pos.z)/TAILLE_CHUNK);
	
		for (Chunk* it : mActualChunk.vectPtrChunk)
		{
			std::pair<int, int> t = it->getPosition();

			if (t.first >= pos.x-1 && t.first <= pos.x+1 && t.second >= pos.z-1 && t.second <= pos.z+1)
			{
				activeChunk(t);
				tmp.vectPtrChunk.push_back(mpppChunk[t.first][t.second]);
			}
			else
			{
				releaseChunk(t);
			}
		}
				
	
		mActualChunk = tmp;

		//--------------------------------------------------

		Ogre::Vector3 posJoueurReal = mActualChunk.positionJoueur;
		std::pair<int, int> posJoueur = std::make_pair(static_cast<int>(posJoueurReal.x)/TAILLE_CHUNK, static_cast<int>(posJoueurReal.z)/TAILLE_CHUNK);
		Ogre::Vector2 centre = Ogre::Vector2::ZERO;

		for (Chunk* it : mActualChunk.vectPtrChunk)
		{
			if (it->getPosition() == posJoueur)
			{
				centre = it->getCentre();
			}
		}

		Vector3 newOffset(centre.x, averageLocalHeight(), centre.y);

		mpHavokWorld->shiftBroadPhase(hkVector4(newOffset.x - mOldOffset.x, newOffset.y - mOldOffset.y, newOffset.z - mOldOffset.z), hkVector4(), hkpWorld::SHIFT_BROADPHASE_UPDATE_ENTITY_AABBS);

		mOldOffset = newOffset;

		for (Chunk* it : mActualChunk.vectPtrChunk)
		{
			mpHavokWorld->addEntity((hkpEntity*)(it->getBodyPtr()));
		}

		mpHavokWorld->unmarkForWrite();
		mpHavokWorld->unlock();

		mTimeCount = boost::chrono::system_clock::now();
	}

	return true;
}

Ogre::Real ChunkManager::averageLocalHeight() const
{
	int denom = mActualChunk.vectPtrChunk.size();
	assert(denom <=9);

	if (denom == 0)
	{
		return 0.0f;
	}

	Ogre::Real num = 0.0f;

	for (auto it : mActualChunk.vectPtrChunk)
	{
		num += it->getAverageHeight();
	}

	return num/denom;
}
