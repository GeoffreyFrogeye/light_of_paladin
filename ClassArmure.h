#pragma once

#include "classitem.h"

class Armure : public Item
{
protected:
    int mPtsProtection;
    float mEtat;

public:

    /* Constructeur */
    /* id, un identifiant unique */
    /* pNode, adresse du noeud de Ogre */
    /* prix, poid, nom, caract�ristiques de l'item */
    /* IsUnique, true si l'armure ne peut se trouver 2 fois dans un m�me inventaire, false par d�faut */
    /* IsVisible, true si l'armure doit �tre rendue par Ogre */
    /* pointProtection, etat, caract�ristiques de l'armure */
    Armure(unsigned long id, Ogre::SceneNode *pNode, int prix=0, float poid=1.0f, std::string nom="DefaultArmor", bool IsUnique=false, bool IsVisible=true, int pointProtection=0, float etat=1.0f);

    /* Destructeur */
    virtual ~Armure();

    /* Renvoie le nombre de points de protection de la pi�ce d'armure */
    int getPtsProtection() const;

    /* Change le nombre de points de protection fourni par la pi�ce d'armure */
    /* pts, le nouveau nombre de points */
    void setPtsProtection(int pts);

    /* Renvoie l'�tat de la pi�ce d'armure 0.0 -> 1.0 */
    float getEtat() const;

    /* Change l'�tat de la pi�ce d'armure */
    /* etat, le nouvel �tat de la pi�ce 0.0 -> 1.0 */
    void setEtat(float etat);
};

