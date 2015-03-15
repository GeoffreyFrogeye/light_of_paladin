#pragma once

#include "ClassCreature.h"

class Magique :public Creature
{
public:

    /* Constructeur */
    /* pNode, adresse du noeud de sc�ne li� � l'objet */
    /* IsVisible, true si l'objet doit �tre rendu */
    /* vie, la vie de l'entit� */
    /* nom, le nom de l'entit� */
    Magique(Ogre::SceneNode *pNode, bool IsVisible, int vie, std::string const& nom="DefaultName");

    /* Destructeur */
    virtual ~Magique();
};

