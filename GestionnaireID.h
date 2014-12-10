#pragma once

#include <set>
#include <vector>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

/* Classe utilis�e pour g�n�rer les identifiants unique de chaque item du jeu */
/* Classe finale, non d�rivable */
/* Singleton */
class GestionnaireID
{
private:
	static GestionnaireID *mpInstanceUnique;

    boost::random::mt19937 mEngine;
    boost::random::uniform_int_distribution<unsigned long> *mpLongDistrib;
    std::set<unsigned long> mIDExistants;

    /* Constructeur interne du singleton */
    GestionnaireID();

	/* Constructeur par copie interdit */
	GestionnaireID(GestionnaireID const& rOriginal);

	/* Op�rateur d'assignement interdit */
	GestionnaireID& operator=(GestionnaireID const& rOriginal);

    /* Destructeur interdit */
    ~GestionnaireID();

public:

	/* Renvoie un pointeur vers l'unique instance du gestionnaire d'ID */
	static GestionnaireID* getInstance();

	/* D�truit l'unique instance */
	static void destroy();

    /* G�n�re un nouvel ID unique, s'il n'y a plus d'ID disponible l�ve une exception */
    unsigned long newID();

    /* Retourne true s'il reste encore des IDs diponibles */
    bool isMoreIDFree() const;

    /* Retourne true si l'ID existe d�j� */
    bool IsIDPresent(unsigned long id) const;

    /* Memorise une liste d'IDs d�j� utilis�s afin qu'il ne soit plus g�n�rer */
    /* liste, un std::vector<unsigned long> contenant les IDs */
    /* Retourne true s'il reste des IDs disponibles apr�s m�morisation */
    bool memoriseID(std::vector<unsigned long> liste);
};