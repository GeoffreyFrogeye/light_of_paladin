#pragma once

#include <OgreVector2.h>

#include <Physics2012/Collide/hkpCollide.h>
#include <Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShape.h>

class GestionnaireTerrain;
class hkpSampledHeightFieldBaseCinfo;
class CollideSpheresInput;
class SphereCollisionOutput;

/* Classe pour repr�senter un chunk de terrain dans Havok */
/* D�rive de hkSampleHeightFieldShape */
/* S�mantique d'entit� */
class HeightFieldShape: public hkpSampledHeightFieldShape
{
private:
	float const *mpHeightData;
	Ogre::Vector2 mCooHeightField;

	/* Constructeur de copie interdit */
	HeightFieldShape(HeightFieldShape const& rOriginal);

	/* Op�rateur d'assignement interdit */
	HeightFieldShape& operator=(HeightFieldShape const& rOriginal);

public:

	/* Constructeur */
	/* rInfo, r�f�rence sur une structure qui d�crit les param�tres de la HeightMap */
	/* pTerrain, adresse du gestionnaire de terrains */
	/* cooHeightField, Ogre::Vector2 avec les coordonn�es (en chunk) de la zone de terrain � cr�er */
	HeightFieldShape(hkpSampledHeightFieldBaseCinfo const& rInfo, GestionnaireTerrain const *pTerrains, Ogre::Vector2 cooHeightField);

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

