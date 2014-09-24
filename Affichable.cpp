#include "Affichable.h"

using namespace Ogre;

Affichable::Affichable(SceneNode *pNode, bool IsVisible)
{
    mpNoeud = pNode;
    mIsVisible = IsVisible;
}

Affichable::~Affichable()
{
    mpNoeud = nullptr;     //On ne d�truit pas le noeud de sc�ne, il est g�r� par Ogre
}

void Affichable::setVisibility(bool visible)
{
    mIsVisible = visible;
}

bool Affichable::getVisibility() const
{
    return mIsVisible;
}

bool Affichable::setNode(SceneNode *pNoeud)
{
    if(mpNoeud != nullptr)
    {
        mpNoeud = pNoeud;
        return true;
    }
    else
    {
        mpNoeud = pNoeud;
        return false;
    }
}

SceneNode* Affichable::getNode() const
{
    return mpNoeud;
}
