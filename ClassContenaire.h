#pragma once

#include "ClassInventaire.h"
#include "Affichable.h"


/* Classe finale, non h�ritable */
/* Permet de cr�er des objets affichable avec un inventaire tel des coffres, ... */
/* S�mantique d'entit� */
class Contenaire: public Inventaire, Affichable
{
private:
	std::string mProprietaire, mNom;

	/* Surcharge de la fonction h�rit�e de Inventaire pour emp�cher qu'elle soit appel�e par erreur */
	void afficheDebugInv(std::ostream& rOst) const;

public:

	/* Constructeur */
	/* pNode, adresse du noeud de sc�ne li� � l'objet */
	/* IsVisible, true si l'objet doit �tre rendu, true par d�faut */
	/* max, la taille de l'inventaire du contenaire */
	Contenaire(Ogre::SceneNode *pNode, bool IsVisible=true, int max=10);

	/* Constructeur */
	/* pNode, adresse du noeud de sc�ne li� � l'objet */
	/* IsVisible, true si l'objet doit �tre rendu, true par d�faut */
	/* inv, l'inventaire � partir duquel construire le contenaire, vide cet inventaire */
	Contenaire(Ogre::SceneNode *pNode, Inventaire& inv, bool IsVisible=true);

	/* Destructeur */
	virtual ~Contenaire();

	/* clone un contenaire, devant �tre lib�r� */
	/* Renvoie un pointeur */
	/* clone les objets de l'inventaire du contenaire original */
	virtual Contenaire* clone() const override;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
	virtual void afficheDebug(std::ostream& rOst) const override;
#endif
	/* D�fini le propri�taire du contenaire */
	/* nom, le nom du propri�taire, par d�faut "all", signifiant aucun propri�taire */
	void setProprietaire(std::string const& nom);

	/* Renvoie le nom du propri�taire */
	/* "all" pour aucun propri�taire */
	std::string getProprietaire() const;

	/* D�fini le nom du contenaire */
	/* nom, le nom du contenaire, par d�faut "Coffre" */
	void setNom(std::string const& nom);

	/* Renvoie le nom du contenaire */
	std::string getNom() const;
};

/* Surcharge des op�rateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Contenaire const& obj);
#endif