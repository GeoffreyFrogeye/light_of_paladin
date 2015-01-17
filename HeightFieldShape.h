#pragma once

#include <Physics2012/Collide/hkpCollide.h>
#include <Physics2012/Collide/Shape/hkpShape.h>
#include <Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShape.h>
#include <Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldBaseCinfo.h>

class GestionnaireTerrain;

class HeightFieldShape: public hkpSampledHeightFieldShape
{
private:
	float const *mpHeightData;
public:

	/* Destructeur */
	HeightFieldShape(hkpSampledHeightFieldBaseCinfo const& rInfo, GestionnaireTerrain const *pTerrains);

	/* Destructeur */
	virtual ~HeightFieldShape();

	/* R�cup�ration de la hauteur du terrain */
	HK_FORCE_INLINE hkReal getHeightAtImpl(int x, int z) const;

	/* Sens de d�coupage des rectangles en triangles */
	HK_FORCE_INLINE hkBool getTriangleFlipImpl() const;

	/* D�termine la collision avec une sph�re */
	virtual void collideSpheres(CollideSpheresInput const& input, SphereCollisionOutput* outputArray) const;
};

