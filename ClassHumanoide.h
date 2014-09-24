#pragma once

#include "Classentitevivante.h"

class Humanoide :public EntiteVivante
{
public:

    /* Constructeur */
    /* pNode, adresse du noeud de sc�ne li� � l'objet */
    /* IsVisible, true si l'objet doit �tre rendu */
    /* vie, la vie de l'entit� */
    /* nom, le nom de l'entit� */
    Humanoide(Ogre::SceneNode *pNode, bool IsVisible, int vie, std::string nom="DefaultName");

    /* Destructeur */
    virtual ~Humanoide();
};

