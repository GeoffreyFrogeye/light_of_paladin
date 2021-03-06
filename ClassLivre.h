#pragma once

#include "ClassDocument.h"

class Livre :public Document
{
public:

    /* Constructeur */
    /* pNode, l'adresse du noeud de Ogre */
    /* prix, poid, nom, caract�ristiques de l'item */
    /* IsUnique, true si l'item ne peut se trouver 2 fois dans un m�me inventaire, false par d�faut */
    /* IsVisible, true si l'item doit �tre rendu par Ogre */
    Livre(Ogre::SceneNode *pNode, int prix=0, float poid=1.0, std::string const& nom="defaultBook", bool IsUnique=false, bool IsVisible=true);

    /* Destructeur */
    virtual ~Livre();
};

