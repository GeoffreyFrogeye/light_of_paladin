#include "ClassEpee.h"

using namespace Ogre;

Epee::Epee(SceneNode *pNode, int degat, float vitesse, float resistance, int prix, float poid, std::string nom, bool IsUnique, bool IsVisible): Arme(pNode, degat, vitesse, resistance, prix, poid, nom, IsUnique, IsVisible)
{
}

Epee::~Epee()
{
}

#ifdef _DEBUG
void Epee::afficheDebug(std::ostream& rOst) const 
{
	rOst << "Type:Epee" << std::endl;
	Arme::afficheDebug(rOst);
}

#endif
Epee* Epee::clone() const 
{
	return new Epee(mpNoeud, mDegat, mVitesse, mResistance, mPrix, mPoid, mNom, mIsUnique, mIsVisible);
}

bool Epee::canUse(Personnage *pJoueur) const 
{
	//TODO
	return true;
}

bool Epee::compare(Item const& rSecondeEpee) const 
{
	/* D'apr�s le RTTI l'Item pass� en param�tre est une Ep�e */

	const Epee& rSecondeEpeeConvertie = dynamic_cast<Epee const&>(rSecondeEpee);

	/* Leur id, leur �tat, leur affichage peuvent �tre diff�rent mais le reste doit �tre identique */
	return (mIsUnique == rSecondeEpeeConvertie.mIsUnique && 
		mNom == rSecondeEpeeConvertie.mNom && 
		mPoid == rSecondeEpeeConvertie.mPoid && 
		mPrix == rSecondeEpeeConvertie.mPrix && 
		mResistance == rSecondeEpeeConvertie.mResistance && 
		mDegat == rSecondeEpeeConvertie.mDegat && 
		mVitesse == rSecondeEpeeConvertie.mVitesse);
}

/* Surcharge des op�rateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Epee const& obj)
{
	obj.afficheDebug(rOst);

	return rOst;
}
#endif