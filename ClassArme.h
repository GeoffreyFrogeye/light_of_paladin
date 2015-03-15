#pragma once

#include "ClassItem.h"

class Personnage;

/* Classe pour g�rer les armes, s�mantique d'entit� */
/* Classe abstraite */
class Arme: public Item
{
protected:

	int mDegat;
	float mVitesse, mResistance;

public:

	/* Constructeur */
	/* pNode, adresse du noeud de Ogre */
	/* prix, poid, nom, caract�ristiques de l'item */
	/* IsUnique, true si l'item ne peut se trouver 2 fois dans un m�me inventaire, false par d�faut */
	/* degat, vitesse, resistance, caract�ristiques de l'arme */
	/* IsVisible, true si l'arme doit �tre rendue par Ogre */
	Arme(Ogre::SceneNode *pNode, int degat, float vitesse=1.0f, float resistance=1.0f, int prix=0, float poid=1.0f, std::string const& nom="defaultWeapon", bool IsUnique=false, bool IsVisible=true);

	/* Destructeur */
	virtual ~Arme();

	/* Renvoie les d�gat qu'inflige l'arme seule */
	int getDegat() const;

	/* Modifie les d�gats de l'arme */
	void setDegat(int degat);

	/* Renvoie la vitesse de frappe de l'arme /seconde */
	float getVitesse() const;

	/* Modifie la vitesse d'attaque */
	/* vitesse, vitesse d'attaque en coup/seconde */
	void setVitesse(float vitesse);

	/* Renvoie la r�sistance actuelle de l'arme 0.0 -> 1.0 */
	float getResistance() const;

	/* Change la r�sistance actuelle de l'arme */
	/* resistance, entre 0.0 et 1.0 */
	void setResistance(float resistance);

	/* Diminue la r�sistance de l'arme, � appeler � chaque utilisation de l'arme */
	void decreaseResistance();

	/* Clonage, m�thode virtuelle pure */
	virtual Arme* clone() const override =0;

	/* Le personnage peut-il s'�quiper de cette arme, m�thode virtuelle pure */
	virtual bool canUse(Personnage *pJoueur) const override =0;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
	virtual void afficheDebug(std::ostream& rOst) const override;
#endif
};

/* Surcharge op�rateurs externes */

/* == */ 
bool operator==(Item const& inv1, Item const& inv2);

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Arme const& obj);
#endif
