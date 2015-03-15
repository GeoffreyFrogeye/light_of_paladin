#pragma once

#include "ClassEntiteVivante.h"

/* Classe abstraite pour g�rer les humano�des, s�mantique d'entit� */
class Humanoide :public EntiteVivante
{
private:
	int mana;

public:

	/* Constructeur */
	/* pNode, adresse du noeud de sc�ne li� � l'objet */
	/* IsVisible, true si l'objet doit �tre rendu */
	/* vie, la vie de l'entit� */
	/* nom, le nom de l'entit� */
	Humanoide(Ogre::SceneNode *pNode, bool IsVisible, int vie, std::string const& nom="DefaultHuma");

	/* Destructeur */
	virtual ~Humanoide();

	/* Clonage, m�thode virtuelle pure */
	virtual Humanoide* clone() const override=0;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
	virtual void afficheDebug(std::ostream& rOst) const override=0;
#endif
};


/* Surcharge des op�rateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Humanoide const& obj);
#endif