#pragma once

#include "ClassItem.h"

enum class ETypeArmure{CASQUE, PLASTRON, GANT_G, GANT_D, BOTTE_G, BOTTE_D, JAMBIERE_G, JAMBIERE_D};

/* Classe finale qui sert � manipuler les diff�rentes parties d'armure */
/* S�mantique d'entit� */
class Armure : public Item
{
private:
	int mPtsProtection;
	float mEtat;
	ETypeArmure mType;

public:

	/* Constructeur */
	/* pNode, adresse du noeud de Ogre */
	/* prix, poid, nom, caract�ristiques de l'item */
	/* IsUnique, true si l'armure ne peut se trouver 2 fois dans un m�me inventaire, false par d�faut */
	/* IsVisible, true si l'armure doit �tre rendue par Ogre */
	/* pointProtection, etat, caract�ristiques de l'armure */
	Armure(Ogre::SceneNode *pNode, ETypeArmure type, int prix=0, float poid=1.0f, std::string nom="DefaultArmor", bool IsUnique=false, bool IsVisible=true, int pointProtection=0, float etat=1.0f);

	/* Destructeur */
	virtual ~Armure();

	/* Renvoie le nombre de points de protection de la pi�ce d'armure */
	int getPtsProtection() const;

	/* Change le nombre de points de protection fourni par la pi�ce d'armure */
	/* pts, le nouveau nombre de points */
	void setPtsProtection(int pts);

	/* Renvoie l'�tat de la pi�ce d'armure 0.0 -> 1.0 */
	float getEtat() const;

	/* Change l'�tat de la pi�ce d'armure */
	/* etat, le nouvel �tat de la pi�ce 0.0 -> 1.0 */
	void setEtat(float etat);

	/* Renvoie le type d'armure, appartient � l'enum ETypeArmure */
	ETypeArmure getType() const;

	/* Modifie le type de l'armure, attention il faut modifier le mesh ! */
	/* type, le nouveau type de l'armure ETypeArmure */
	void setType(ETypeArmure type);

	/* Clonage */
	virtual Armure* clone() const override;

	/* Pr�dicat, renvoie true si le personnage peut s'�quiper de la pi�ce d'armure */
	virtual bool canUse(Personnage *pJoueur) const override;

	/* Pr�dicat, renvoie true si les deux armures sont �quivalentes (les m�mes sauf leur id) */
	virtual bool compare(Item const& rSecondeArmure) const override;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
	virtual void afficheDebug(std::ostream& rOst) const override;
#endif
};

/* Surcharge des op�rateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Armure const& obj);
#endif