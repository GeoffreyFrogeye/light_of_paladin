#include <string>

#include "ClassItem.h"
#include "GestionnaireID.h"

using namespace std;

Item::Item(Ogre::SceneNode *pNode, int prix, float poid, string const& nom, bool IsUnique, bool IsVisible): Affichable(pNode, IsVisible)
{
    mID = GestionnaireID::getInstance()->newID();

    if (prix >= 0)
    {
        mPrix = prix;
    } 
    else
    {
        mPrix = 0;
    }

    if (poid >= 0.0f)
    {
        mPoid = poid;
    } 
    else
    {
        mPoid = 1.0f;
    }

    mNom = nom;
    mIsUnique = IsUnique;
}

Item::~Item()
{
    mID = 0;
    mPrix = 0;
    mPoid = 0.0f;
}

unsigned long Item::getID() const 
{
    return mID;
}

int Item::getPrix() const
{
    return mPrix;
}

float Item::getPoid() const 
{
    return mPoid;
}

string const& Item::getNom() const
{
    return mNom;
}

void Item::setPrix(int prix)
{
    if (prix >= 0)
    {
        mPrix = prix;
    }
}

void Item::setPoid(float poid)
{
    if (poid >= 0.0f)
    {
        mPoid = poid;
    }
}

void Item::setNom(std::string const& nom)
{
    if (nom.length() > 0)
    {
        mNom = nom;
    }
}

void Item::setIsUnique(bool IsUnique)
{
    mIsUnique = IsUnique;
}

#ifdef _DEBUG
void Item::afficheDebug(std::ostream& rOst) const 
{
	rOst << "Nom:" << mNom << endl;
	Affichable::afficheDebug(rOst);
	rOst << "ID:" << mID << endl << "Prix:" << mPrix << endl << "Poid:" << mPoid << endl;
}
#endif


/* Surcharge opérateurs externes */

/* == */
bool operator==(Item const& item1, Item const& item2)
{
	if (typeid(item1) == typeid(item2))
	{
		return item1.compare(item2);	//Comportement polymorphique
	} 
	else
	{
		return false;
	}
}

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Item const& obj)
{
	obj.afficheDebug(rOst);

	return rOst;
}
#endif