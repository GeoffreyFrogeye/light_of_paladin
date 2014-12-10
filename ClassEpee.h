#pragma once

#include "ClassArme.h"

/* Classe finale, g�re les �p�es */
class Epee:public Arme
{
private:

	/* Constructeur de copie interdit */
	Epee(Epee const& original);

	/* Op�rateur d'assignement interdit */
	Epee& operator=(Epee const& original);

public:

	/* Constructeur */
	/* pNode, adresse du noeud de Ogre */
	/* prix, poid, nom, caract�ristiques de l'item */
	/* IsUnique, true si l'item ne peut se trouver 2 fois dans un m�me inventaire, false par d�faut */
	/* degat, vitesse, resistance, caract�ristiques de l'�p�e */
	/* IsVisible, true si l'�p�e doit �tre rendue par Ogre */
	Epee(Ogre::SceneNode *pNode, int degat, float vitesse=1.0f, float resistance=1.0f, int prix=0, float poid=1.0f, std::string nom="defaultWeapon", bool IsUnique=false, bool IsVisible=true);

	virtual ~Epee();

	/* Pr�dicat, renvoie true si les deux �p�es sont �quivalentes (les m�mes sauf leur id) */
	virtual bool compare(Item const& rSecondeEpee) const override;

	/* Clonage */
	virtual Epee* clone() const override;

	/* Le personnage peut-il s'�quiper de cette �p�e */
	virtual bool canUse(Personnage *pJoueur) const override;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
	virtual void afficheDebug(std::ostream& rOst) const override;
#endif
};

/* Surcharge op�rateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Epee const& obj);
#endif