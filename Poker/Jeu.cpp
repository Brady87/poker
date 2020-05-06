#include "Jeu.h"

Jeu::Jeu(int manche, int tour, int pot, int *idJoueur)
{
	manche_ = manche;
	tour_ = tour;
	pot_ = pot;
	idJoueur_ = idJoueur;
}

Jeu::~Jeu()
{
	delete idJoueur_;
}

void Jeu::afficher_cartes_tables()
{

}
