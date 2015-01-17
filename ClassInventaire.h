#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>

class Item;

/* Classe pour g�rer un inventaire, s�mantique de valeur */
class Inventaire
{
	friend bool operator==(Inventaire const& inv1, Inventaire const& inv2);
	friend bool operator<(Inventaire const& inv1, Inventaire const& inv2);

protected:

	std::multimap<unsigned long, Item*> mStuff; //Pointeurs sur des Items, rep�r�s par l'id
	int mNb, mMax;
	float mPoidTotal;

public:

	/* Constructeur */
	/* max, le nombre d'emplacements de l'inventaire */
	Inventaire(int max=10);

	/* Constructeur par copie, clone les items */
	Inventaire(Inventaire const& rOriginal);

	/* Op�rateur d'assignement, clone les items */
	Inventaire& operator=(Inventaire const& rOriginal);

	/* Destructeur */
	virtual ~Inventaire();

	/* Renvoie le nombre d'items dans l'inventaire */
	int getNB() const;

	/* Renvoie le nombre max d'emplacement */
	int getMax() const;

	/* Modifie le nombre max d'emplacement */
	/* Renvoie si le nombre max a pu �tre modifi� ( trop d'item ) */
	bool setMax(int newMax);

	/* Renvoie le poid de tous les objets contenus dans l'inventaire */
	float getPoidTotal() const;

	/* Ajoute un item par r�f�rence */
	/* Renvoie l'ID de l'item ajout� ou 0 en cas de probl�me */
	unsigned long ajout(Item& rItem);

	/* Ajoute un item par pointeur */
	/* Renvoie l'ID de l'item ajout� ou 0 en cas de probl�me */
	unsigned long ajout(Item* const pItem);

	/* Supprime un item par son pointeur */
	/* Renvoie true si l'item existait */
	bool suppr(Item* const pItem); 

	/* Supprime un item par son ID */
	/* Renvoie true si l'item existait */
	bool suppr(unsigned long ID);

	/* Vide l'inventaire */
	/* Renvoie si true si l'inventaire �tait vide */
	bool clear();

	/* R�cup�re un item par son ID */
	/* ID, l'identifiant de l'item */
	/* Retourne l'adresse de l'item ou nullptr */
	Item* getItem(unsigned long ID) const;

	/* Renvoie true si l'item demand�, ou son ID, est trouv� */
	bool existe(unsigned long ID) const;
	bool existe(Item* pItem) const;

#ifdef _DEBUG
	/* Affiche des informations sur l'inventaire dans la console, DEBUG */
	void afficheDebugInv(std::ostream& rOst) const;
#endif


	/* Surcharge des op�rateurs internes */

	/* += */
	Inventaire& operator+=(Inventaire const& inv);
};


/* Surcharge des op�rateurs externes*/

/* + */
Inventaire operator+(Inventaire const& inv1, Inventaire const& inv2);

/* == */
/* Deux inventaires sont �gaux s'ils ont le m�me nombre d'objets et que ces objets sont les m�mes */
bool operator==(Inventaire const& inv1, Inventaire const& inv2);

/* < */
/* Un inventaire est inf�rieur � un autre s'il contient moins d'objet */
bool operator<(Inventaire const& inv1, Inventaire const& inv2);

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Inventaire const& inv);
#endif