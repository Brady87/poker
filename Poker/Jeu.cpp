#include "Jeu.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

Jeu::Jeu(int manche, int tour, int pot, Cartes* cartesTable, vector<Cartes> pioche, int* idJoueur)
{
	manche_ = manche;
	tour_ = tour;
	pot_ = pot;
	cartesTable_ = cartesTable;
	pioche_ = pioche;
	idJoueur_ = idJoueur;
}

Jeu::~Jeu()
{
	delete idJoueur_;
}

void Jeu::afficher_cartes_tables()
{
	cout << "Cartes sur la table : ";
	if (tour_ == 1) { //1er tour : on affiche rien
		
	}
	else if (tour_ == 2) {//2e tour : on affiche les 3 premi�res cartes
		for (int i = 0; i < 3; i++) {
			cartesTable_[i].afficher_cartes;
			cout << "  ";
		}
	}
	else if (tour_ == 3) {// 3e tour : on affiche les 4 premi�res cartes
		for (int i = 0; i < 4; i++) {
			cartesTable_[i].afficher_cartes;
			cout << "  ";
		}
	}
	else { //4e et dernier tour : on affiche les 5 cartes
		for (int i = 0; i < 5; i++) {
			cartesTable_[i].afficher_cartes;
			cout << "  ";
		}
	}
}

Cartes* Jeu::distribuerCartes(const int nbre)
{
	Cartes* cartesDistrib = new Cartes[nbre]; //Initialisation du tableau � renvoyer
	for (int i = 0; i < nbre; i++) {
		cartesDistrib[i] = pioche_.back; //Affectation du vecteur � la liste
		pioche_.push_back; //Suppression de la carte du vecteur
	}
	return cartesDistrib; 
}

void Jeu::melangerCartes()
{
	unsigned seed = chrono::system_clock::now()//G�n�ration d'une graine pour shuffle
		.time_since_epoch()
		.count();
	shuffle(pioche_.begin(), pioche_.end(), std::default_random_engine(seed));//M�lange
}

void Jeu::gagnant()
{
	//On prend la main du joueur 1
	joueurs_[0].get_main;
}
