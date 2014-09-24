#pragma once

#include <string>
#include <Ogre.h>

#include "Affichable.h"

class EntiteVivante: public Affichable
{
protected:
    int mVie;
    std::string mNom;

public:

    /* Constructeur */
    /* pNode, adresse du noeud de sc�ne li� � l'objet */
    /* IsVisible, true si l'objet doit �tre rendu */
    /* vie, la vie de l'entit� */
    /* nom, le nom de l'entit� */
    EntiteVivante(Ogre::SceneNode *pNode, bool IsVisible, int vie, std::string nom="DefaultName");

    /* Destructeur */
    virtual ~EntiteVivante();
};

