#pragma once

#include "ClassItem.h"

/* Classe abstraite servant de base pour tous les objets consommables (potions, ect), objets stackables */
/* S�mantique d'entit� */
class Consommable :public Item
{
private:
	unsigned int mNombre;

	/* Constructeur par copie interdit */
	Consommable(Consommable const& rOriginal);

	/* Op�rateur d'assignement interdit */
	Consommable& operator=(Consommable const& rOriginal);

public:
    
    /* Constructeur */
    /* pNode, l'adresse du noeud de Ogre */
    /* prix, poid, nom, caract�ristiques de l'item */
    /* IsUnique, true si l'item ne peut se trouver 2 fois dans un m�me inventaire, false par d�faut */
    /* IsVisible, true si l'item doit �tre rendu par Ogre */
    Consommable(Ogre::SceneNode *pNode, int prix=0, float poid=1.0, std::string nom="defaultConsommable", bool IsUnique=false, bool IsVisible=true);

    /* Destructeur */
    virtual ~Consommable();

	/* Renvoie le nombre d'objets stack�s */
	unsigned int getNombre() const;

	/* Ajoute un objet dans le stack */
	void addObjet();

	/* Ajoute plusieurs objets dans le stack */
	/* nbr, le nombre d'objets � ajouter */
	void addObjet(unsigned int nbr);

	/* Enl�ve un objet du stack */
	/* Renvoie true s'il reste encore des objets */
	bool supprObjet();

	/* Enl�ve nbr objets du stack */
	/* Renvoie true s'il reste encore des objets */
	bool supprObjet(unsigned int nbr);

	/* Renvoie true si le joueur peut consommer, m�thode virtuelle pure */
	virtual bool canUse(Personnage *pJoueur) const override =0;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
	virtual void afficheDebug(std::ostream& rOst) const override =0;
#endif
};

/* Surcharge des op�rateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Consommable const& obj);
#endif