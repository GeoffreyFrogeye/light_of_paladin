#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "Affichable.h"

class Personnage;

class Item: public Affichable
{
protected:

    unsigned long mID;
    int mPrix;
    float mPoid;
    std::string mNom;
    bool mIsUnique;

public:

    /* Constructeur */
    /* id, un identifiant unique */
    /* pNode, l'adresse du noeud de Ogre */
    /* prix, poid, nom, caract�ristiques de l'item */
    /* IsUnique, true si l'item ne peut se trouver 2 fois dans un m�me inventaire, false par d�faut */
    /* IsVisible, true si l'item doit �tre rendu par Ogre */
    Item(unsigned long id, Ogre::SceneNode *pNode, int prix=0, float poid=1.0, std::string nom="defaultItem", bool IsUnique=false, bool IsVisible=true);    

    /* Destructeur */
    virtual ~Item();

    /* Renvoie true si le joueur peut utiliser l'item */
    /* M�thode virtuelle pure */
    virtual bool canUse(Personnage *pJoueur) const = 0;

    /* Renvoie le prix de l'item */
    int getPrix() const;

    /* Change le prix de l'item */
    void setPrix(int prix);

    /* Renvoie le poid de l'item */
    float getPoid() const;

    /* Change le poid de l'item */
    void setPoid(float poid);

    /* Renvoie l'ID de l'item */
    unsigned long getID() const;

    /* Renvoie le nom de l'item */
    std::string getNom() const;

    /* Change le nom de l'item */
    void setNom(std::string nom);

    /* Renvoie true si l'item ne peut �tre 2 fois dans un m�me inventaire */
    bool getIsUnique() const;

    /* D�fini si un item peut �tre plusieurs fois dans un m�me inventaire */
    void setIsUnique(bool IsUnique);
};