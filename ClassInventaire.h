#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>

class Item;

/* Classe pour g�rer un inventaire, s�mantique de valeur */
class Inventaire
{
protected:

    std::multimap<unsigned long, Item*> mStuff;
    int mNb, mMax;
    float mPoidTotal;

public:

    /* Constructeur */
    Inventaire(int max=10);

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

    /* Surcharge des op�rateurs unaires */
    void operator+=(Inventaire const& inv);
};


/* Surcharge des op�rateurs binaires */

/* + */
Inventaire operator+(Inventaire const& inv1, Inventaire const& inv2);