#pragma once

#include <Physics2012/Collide/hkpCollide.h>
#include <Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShape.h>

#include <boost/noncopyable.hpp>

#include "Structures.h"

class GestionnaireTerrain;
class hkpSampledHeightFieldBaseCinfo;
class CollideSpheresInput;
class SphereCollisionOutput;

/* Classe pour repr�senter un chunk de terrain dans Havok */
/* H�rite de hkSampleHeightFieldShape */
/* S�mantique d'entit�, h�rite boost::noncopyable */
class HeightFieldShape: public hkpSampledHeightFieldShape, private boost::noncopyable
{
private:
	float **mpHeightData;

public:

	/* Constructeur */
	/* rInfo, r�f�rence sur une structure qui d�crit les param�tres de la HeightMap */
	/* pTerrain, adresse du gestionnaire de terrains */
	/* cooHeightField, paire de coordonn�es (en chunk) de la zone de terrain � cr�er */
	HeightFieldShape(hkpSampledHeightFieldBaseCinfo const& rInfo, GestionnaireTerrain const *pTerrains, std::pair<int, int> coo);

	/* Destructeur */
	virtual ~HeightFieldShape();

	/* R�cup�ration de la hauteur du terrain */
	HK_FORCE_INLINE hkReal getHeightAtImpl(int x, int z) const;

	/* Sens de d�coupage des rectangles en triangles */
	HK_FORCE_INLINE hkBool getTriangleFlipImpl() const;

	/* D�termine la collision avec une sph�re */
	/* Fonction par d�faut de Havok */
	virtual void collideSpheres(CollideSpheresInput const& input, SphereCollisionOutput* outputArray) const;
};

