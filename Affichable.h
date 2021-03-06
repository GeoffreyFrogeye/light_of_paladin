#pragma once

#include <iostream>
#include <boost/noncopyable.hpp>

namespace Ogre
{
	class SceneNode;
}

/* Classe abstraite servant de base � tous les �l�ments affichables du jeu */
/* S�mantique d'entit�, h�rite de boost::noncopyable */
class Affichable: private boost::noncopyable
{
protected:
	Ogre::SceneNode *mpNoeud;
	bool mIsVisible;

public:

	/* Constructeur */
	/* pNode, adresse du noeud de sc�ne li� � l'objet */
	/* IsVisible, true si l'objet doit �tre rendu, true par d�faut */
	Affichable(Ogre::SceneNode *pNode, bool IsVisible=true);

	/* Clonage, m�thode virtuelle pure */
	virtual Affichable* clone() const =0;

	/* Destructeur */
	/* Le noeud de sc�ne n'est pas d�truit */
	virtual ~Affichable();

	/* Modifie l'�tat d'affichage */
	void setVisibility(bool visible);

	/* Renvoie true si l'objet est rendu par Ogre */
	bool getVisibility() const;

	/* Assigne un nouveau noeud Ogre */
	/* Renvoie true s'il y avait un noeud valide */
	bool setNode(Ogre::SceneNode *pNoeud);

	/* Renvoie l'adresse du noeud Ogre ou nullptr */
	Ogre::SceneNode* getNode() const;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
		virtual void afficheDebug(std::ostream& rOst) const;
#endif
	
};

/* Surcharge op�rateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Affichable const& obj);
#endif
