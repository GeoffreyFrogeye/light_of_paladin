#pragma once

#include "classitem.h"

class Consommable :public Item
{
public:
    
    /* Constructeur */
    /* id, un identifiant unique */
    /* pNode, l'adresse du noeud de Ogre */
    /* prix, poid, nom, caract�ristiques de l'item */
    /* IsUnique, true si l'item ne peut se trouver 2 fois dans un m�me inventaire, false par d�faut */
    /* IsVisible, true si l'item doit �tre rendu par Ogre */
    Consommable(unsigned long id, Ogre::SceneNode *pNode, int prix=0, float poid=1.0, std::string nom="defaultConsommable", bool IsUnique=false, bool IsVisible=true);

    /* Destructeur */
    virtual ~Consommable();
};

