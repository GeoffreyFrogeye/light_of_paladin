#pragma once

#include "Affichable.h"

namespace Ogre
{
	class SceneNode;
}

class Inventaire;

/* Classe de base abstraite pour les entit�s vivantes du jeu */
/* S�mantique d'entit� */
class EntiteVivante: public Affichable
{
protected:
	int mVie;
	std::string mNom;
	Inventaire *mpInventaire;

public:

	/* Constructeur */
	/* pNode, adresse du noeud de sc�ne li� � l'objet */
	/* IsVisible, true si l'objet doit �tre rendu */
	/* vie, la vie de l'entit� */
	/* nom, le nom de l'entit� */
	EntiteVivante(Ogre::SceneNode *pNode, bool IsVisible, int vie, std::string nom="DefaultName");

	/* Destructeur */
	virtual ~EntiteVivante();

	/* Clonage, m�thode virtuelle pure */
	virtual EntiteVivante* clone() const override=0;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG  */
	virtual void afficheDebug(std::ostream& rOst) const override=0;
#endif
};


/* Surcharge des op�rateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, EntiteVivante const& obj);
#endif