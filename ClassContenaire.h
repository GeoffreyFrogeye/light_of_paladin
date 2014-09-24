#pragma once

#include "classinventaire.h"
#include "Affichable.h"

class Contenaire : public Inventaire, Affichable
{
public:

    /* Constructeur */
    /* pNode, adresse du noeud de sc�ne li� � l'objet */
    /* IsVisible, true si l'objet doit �tre rendu, true par d�faut */
    /* max, la taille de l'inventaire du contenaire */
    Contenaire(Ogre::SceneNode *pNode, bool IsVisible=true, int max=10);

    /* Destructeur */
    virtual ~Contenaire();
};

