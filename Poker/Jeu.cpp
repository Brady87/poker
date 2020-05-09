#include "Jeu.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include<list>
using namespace std;

Jeu::Jeu(int manche, int tour, int pot, Cartes* cartesTable, vector<Cartes> pioche, int* idJoueur, Joueur* joueurs)
{
	manche_ = manche;
	tour_ = tour;
	pot_ = pot;
	cartesTable_ = cartesTable;
	pioche_ = pioche;
	idJoueur_ = idJoueur;
	joueurs_ = joueurs;
}

Jeu::~Jeu()
{
	delete idJoueur_;
}

void Jeu::afficher_cartes_tables()
{
	cout << "Cartes sur la table : ";
	if (tour_ == 1) { //1er tour : on affiche rien
		cout << endl;
	}
	else if (tour_ == 2) {//2e tour : on affiche les 3 premières cartes
		for (int i = 0; i < 3; i++) {
			cartesTable_[i].afficher_cartes;
			cout << "  ";
		}
	}
	else if (tour_ == 3) {// 3e tour : on affiche les 4 premières cartes
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
	Cartes* cartesDistrib = new Cartes[nbre]; //Initialisation du tableau à renvoyer
	for (int i = 0; i < nbre; i++) {
		cartesDistrib[i] = pioche_.back; //Affectation du vecteur à la liste
		pioche_.push_back; //Suppression de la carte du vecteur
	}
	return cartesDistrib; 
}

void Jeu::melangerCartes()
{
	unsigned seed = chrono::system_clock::now()//Génération d'une graine pour shuffle
		.time_since_epoch()
		.count();
	shuffle(pioche_.begin(), pioche_.end(), std::default_random_engine(seed));//Mélange
}

void Jeu::comparer(const int idJoueur)
{
	//On prend la main du joueur ayant idJoueur
	Cartes* main1 = joueurs_[idJoueur].get_main();
	Cartes* mainTable = cartesTable_;
	//On sort les valeurs
	int listeCouleur[7];
	int listeSymbole[7];
	for (int i = 0; i <2; i++){
		listeCouleur[i] = main1[i].get_couleur();// Ajoute les couleurs de la main du joueur
	}
	for (int i = 0; i < 5; i++) {
		listeCouleur[i+2]=mainTable[i].get_couleur();// Ajoute les couleurs de la table
	}
	for (int i = 0; i < 2; i++) {
		listeCouleur[i]=main1[i].get_symbole();// Ajoute les couleurs de la main du joueur
	}
	for (int i = 0; i < 5; i++) {
		listeCouleur[i+2]=mainTable[i].get_symbole();// Ajoute les couleurs de la table
	}

// Tri des listes
		for (int i = 0; i < 6; i++) {
			for (int j = i + 1; j < 6; j++) {
				if (i > listeCouleur[j]) {
					int c = listeCouleur[i];
					listeCouleur[i] = listeCouleur[j];
					listeCouleur[j] = c;
				}
			}
		}

		for (int i = 0; i < 6; i++) {
			for (int j = i + 1; j < 6; j++) {
				if (i > listeSymbole[j]) {
					int c = listeSymbole[i];
					listeSymbole[i] = listeSymbole[j];
					listeSymbole[j] = c;
				}
			}
		}

	//test de "La quinte flush royale"
		if (listeSymbole[6] == 14 ) {
	}
}


