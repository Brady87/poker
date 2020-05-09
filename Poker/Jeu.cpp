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

int* Jeu::combinaison(const int idJoueur)
{
	int combinaison[3];
	int idCombinaison=0;// De 0 à 9
	int idValeurCombinaison=0;// De 0 à 12
	int idValeurCombinaison1 = 0;
	//On prend la main du joueur ayant idJoueur
	Cartes* main1 = joueurs_[idJoueur].get_main();
	Cartes* mainTable = cartesTable_;
	//On sort les valeurs
	int tabCouleur[4];
	int tabSymbole[13];
	int tabId[52];
	bool trouve = false;

	for (int i = 0; i < 52; i++) { //on initialise le tableau à zéro
		tabId[i] = 0;
	}
	for (int i = 0; i < 13; i++) { //on initialise le tableau à zéro
		tabSymbole[i] = 0;
	}
	for (int i = 0; i < 4; i++) { //on initialise le tableau à zéro
		tabCouleur[i] = 0;
	}

	for (int i = 0; i < 2; i++) {//Parcours de la main du joueur
		tabCouleur[main1[i].get_couleur()] ++;
		tabSymbole[main1[i].get_symbole()] ++;
		tabId[main1[i].get_idCarte()]++;//on incrémente chaque valeur
	}
	for (int i = 0; i < 5; i++) {//Parcours des cartes de la table
		tabCouleur[mainTable[i].get_couleur()] ++;
		tabSymbole[mainTable[i].get_symbole()] ++;
		tabId[mainTable[i].get_idCarte()]++;//on incrémente chaque valeur
	}


	//Test Quinte flush royale
	if (!trouve) {
		for (int i = 0; i < 4; i++) {
			if (tabId[51 - i * 13] == 1 && tabId[50 - i * 13] == 1 && tabId[49 - i * 13] == 1 && tabId[48 - i * 13] == 1 && tabId[47 - i * 13] == 1) {
				idCombinaison = 9;
				idValeurCombinaison = i; // Couleur inutile pour comparasion juste affichage
				trouve = true;
			}
		}
	}

	//Test Quinte flush 
	if (!trouve) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				if (tabId[50 - j - i * 13] == 1 && tabId[49 - j - i * 13] == 1 && tabId[48 - j - i * 13] == 1 && tabId[47 - j - i * 13] == 1 && tabId[46 - j - i * 13] == 1) {
					idCombinaison = 8;
					idValeurCombinaison = 12 - j;
					trouve = true;
				}
			}
		}
	}

	//Test Carrée
	if (!trouve) {
		for (int i = 0; i < 13; i++) {
			if (tabSymbole[i] >= 4) {
				idCombinaison = 7;
				idValeurCombinaison = i;
				trouve = true;
			}
		}
	}
	//Test Full 
	if (!trouve) {
		for (int i = 0; i < 13; i++) {
			if (tabSymbole[i] >= 3) {
				for (int j = 0; j < 13; j++) {
					if (j != i && tabSymbole[j] >= 2) {
						idCombinaison = 6;
						idValeurCombinaison = i;
						idValeurCombinaison1 = j;
						trouve = true;
					}
				}
			}
		}
	}

	//Test Couleur
	if (!trouve) {
		for (int i = 0; i < 4; i++) {
			if (tabCouleur[i] >= 5) {
				idCombinaison = 5;
				int j = 0;
				while (tabId[13 * (i + 1) - j - 1] == 0) {
					j++;
				}
				idValeurCombinaison = 12 - j;
				trouve = true;
			}
		}
	}

	//Test Suite
	if (!trouve) {
		for (int i = 0; i < 10; i++) {
			if (tabSymbole[i] == 1 && tabSymbole[i + 1] == 1 && tabSymbole[i + 2] == 1 && tabSymbole[i + 3] == 1 && tabSymbole[i + 4] == 1) {
				idCombinaison = 4;
				idValeurCombinaison = i;
				trouve = true;
			}
		}
	}

	//Test Brelan
	if (!trouve) {
		for (int i = 0; i < 13; i++) {
			if (tabSymbole[i] >= 3) {
				idCombinaison = 3;
				idValeurCombinaison = i;
				trouve = true;
			}
		}
	}

	//Test Double Paire et Paire
	if (!trouve) {
		for (int i = 0; i < 13; i++) {
			if (tabSymbole[i] >= 2) {
				idCombinaison = 1; // C'est une paire
				idValeurCombinaison = i; //Prend automatiquement la paire la plus haute
				trouve = true;
				for (int j = 0; j < 13; j++) {
					if (j != i, tabSymbole[j] >= 2) {
						idCombinaison = 2; //C'est une double paire
						idValeurCombinaison1 = j;
					}
				}
			}
		}
	}

	//Test Carte Haute
	if (!trouve) {
		int i = 0;
		while (tabSymbole[12 - i] == 0) {
			i++;
		}
		idCombinaison = 0;
		idValeurCombinaison = 12 - i;
		trouve = true;
	}

	combinaison[0] = idCombinaison;
	combinaison[1] = idValeurCombinaison;
	combinaison[2] = idValeurCombinaison1;
	return combinaison;
}

