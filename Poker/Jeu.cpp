#include "Jeu.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include<list>
#include <fstream>
#include <iostream>
using namespace std;


Jeu::Jeu(int manche, int tour, int pot)
{
	manche_ = manche;
	tour_ = tour;
	pot_ = pot;
	//Pioche par défaut
	vector<Cartes> pioche(52);
	for (int i = 0; i < 52; i++) {
		Cartes c(i);
		pioche[i] = c;
	}
	pioche_ = pioche;
}

Jeu::~Jeu()
{
	delete idJoueur_;
}

const void Jeu::afficher_cartes_tables()
{
	cout << "Cartes sur la table : ";
	if (tour_ == 1) { //1er tour : on affiche rien
		cout << endl;
	}
	else if (tour_ == 2) {//2e tour : on affiche les 3 premières cartes
		for (int i = 0; i < 3; i++) {
			cartesTable_[i].afficher_cartes();
			cout << "  ";
		}
	}
	else if (tour_ == 3) {// 3e tour : on affiche les 4 premières cartes
		for (int i = 0; i < 4; i++) {
			cartesTable_[i].afficher_cartes();
			cout << "  ";
		}
	}
	else { //4e et dernier tour : on affiche les 5 cartes
		for (int i = 0; i < 5; i++) {
			cartesTable_[i].afficher_cartes();
			cout << "  ";
		}
	}
}

const void Jeu::affichage(int rep)
{
	cout << "Manche " << manche_ << endl;
	cout << "Tour " << tour_ << endl;
	cout << "------------------------------" << endl;
	cout << "Vous : ";
	joueurs_[rep].affciher_jetons();
	cout << "Votre mise : " << joueurs_[rep].get_mise() << endl;
	cout << endl;
	cout << "Adversaire : ";
	joueurs_[rep - 1].afficher_choix();
	cout << "Mise adverse : " << joueurs_[rep-1].get_mise() << endl;
	joueurs_[rep - 1].affciher_jetons();
	cout << endl;
	cout << "Pot : " << pot_ << " jetons." << endl;
	cout << "Votre main : ";
	joueurs_[rep].afficher_cartes_joueur();
	cout << "Sur la table : ";
	afficher_cartes_tables();
	cout << "------------------------------" << endl;
}

void Jeu::set_joueurs(Joueur joueur)
{
	const int id = joueur.get_id();
	joueurs_[id] = joueur;
}


void Jeu::choix(int rep)
{

	int ch;
	bool valide = false; //Vérifie que le choix effectué est valide
	do
	{
		cout << "Veuillez rentrer votre choix " << endl;
		cout << "1- Checker " << endl;
		cout << "2- Miser/Relancer " << endl;
		cout << "3- Suivre " << endl;
		cout << "4- Se coucher " << endl;
		cin >> ch;
		switch (ch)
		{
		case 1:
			if (!joueurs_[rep].get_distributeur())
			{
				cout <<"Vous checkez" <<endl;
				valide = true;
			}
			else {
				cout << "Vous ne pouvez pas checkez." << endl;
			}
			break;
		case 2:
			int mise;
			if (joueurs_[rep].get_mise() == 0) {
				cout << "Mise de combien ?" << endl;
			}
			else {
				cout << "Remisez de combien ?" << endl;
			}
			cin >> mise;
			if (joueurs_[rep].get_jetons() < mise) {
				cout << "Mise supérieure a votre capital" << endl;
			}
			else if (mise+ joueurs_[rep].get_mise() < joueurs_[rep - 1].get_mise()) {
				cout << "Mise insuffisante : vous devez miser au moins : " << joueurs_[rep - 1].get_mise()- joueurs_[rep].get_mise() << "." << endl;
			}
			else {
				joueurs_[rep].set_jetons(joueurs_[rep].get_jetons() - mise); //On met à jour son nbre de jetons
				joueurs_[rep].set_mise(joueurs_[rep].get_mise() + mise); // Mise total durant ce tour
				set_pot(get_pot() + mise); // On met à jour le pot
				valide = true;
			break;
		case 3:
			if (joueurs_[rep].get_mise()+ joueurs_[rep].get_jetons() < joueurs_[rep - 1].get_mise()) {
				cout << "Vous ne pouvez pas suivre." << endl; //CAS TAPIS
			}
			else {
				joueurs_[rep].set_jetons(joueurs_[rep].get_jetons() - (joueurs_[rep - 1].get_mise() - joueurs_[rep].get_mise()));
				cout << "Vous vous alignez en misant " << joueurs_[rep - 1].get_mise() - joueurs_[rep].get_mise() << endl;
				joueurs_[rep].set_mise(joueurs_[rep-1].get_mise());
				valide = true;
			}
			break;
			case 4:
				cout <<"Vous vous couchez." <<endl;
				joueurs_[rep - 1].set_jetons(joueurs_[rep - 1].get_jetons() + get_pot());
				valide = true;
				break;
			}

		default:
				cout <<"Choix non valide, veuillez rentrer un choix valide" <<endl;
				break;
		}

	} while (!valide);
	joueurs_[rep].set_choix(ch); // On affecte le choix

}

Cartes* Jeu::distribuerCartes(const int nbre)
{
	Cartes* cartesDistrib = new Cartes[nbre]; //Initialisation du tableau à renvoyer
	for (int i = 0; i < nbre; i++) {
		cartesDistrib[i] = pioche_[pioche_.size()-1]; //Affectation du vecteur à la liste
		pioche_.pop_back(); //Suppression de la carte du vecteur
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


	//Test Quinte Flush Royale
	if (!trouve) {
		for (int i = 0; i < 4; i++) {
			if (tabId[51 - i * 13] == 1 && tabId[50 - i * 13] == 1 && tabId[49 - i * 13] == 1 && tabId[48 - i * 13] == 1 && tabId[47 - i * 13] == 1) {
				idCombinaison = 9;
				idValeurCombinaison = i; // Couleur inutile pour comparasion juste affichage
				trouve = true;
			}
		}
	}

	//Test Quinte Flush 
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

	//Test Carré
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
			if (tabSymbole[i] >= 1 && tabSymbole[i + 1] >= 1 && tabSymbole[i + 2] >= 1 && tabSymbole[i + 3] >= 1 && tabSymbole[i + 4] >= 1) {
				idCombinaison = 4;
				idValeurCombinaison = i+4;
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
					if (j != i && tabSymbole[j] >= 2) {
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

const void Jeu::nomCombinaison(const int idJoueur)
{
	int* comb = new int[3];
	comb=combinaison(idJoueur);
	switch (comb[0]) {
	case 0:
		cout << "Main haute ";
		switch (comb[1]) {
		case 0:
			cout << "au 2." << endl;
			break;
		case 1:
			cout << "au 3." << endl;
			break;
		case 2:
			cout << "au 4." << endl;
			break;
		case 3:
			cout << "au 5." << endl;
			break;
		case 4:
			cout << "au 6." << endl;
			break;
		case 5:
			cout << "au 7." << endl;
			break;
		case 6:
			cout << "au 8." << endl;
			break;
		case 7:
			cout << "au 9." << endl;
			break;
		case 8:
			cout << "au 10." << endl;
			break;
		case 9:
			cout << "au Valet." << endl;
			break;
		case 10:
			cout << "a la Dame." << endl;
			break;
		case 11:
			cout << "au Roi." << endl;
			break;
		case 12:
			cout << "a l'As." << endl;
			break;
		default:
			cout << "Inconnu" << endl;
			break;
		}
		break;
	case 1:
		cout << "Paire ";
		switch (comb[1]) {
		case 0:
			cout << "de 2." << endl;
			break;
		case 1:
			cout << "de 3." << endl;
			break;
		case 2:
			cout << "de 4." << endl;
			break;
		case 3:
			cout << "de 5." << endl;
			break;
		case 4:
			cout << "de 6." << endl;
			break;
		case 5:
			cout << "de 7." << endl;
			break;
		case 6:
			cout << "de 8." << endl;
			break;
		case 7:
			cout << "de 9." << endl;
			break;
		case 8:
			cout << "de 10." << endl;
			break;
		case 9:
			cout << "de Valets." << endl;
			break;
		case 10:
			cout << "de Dames." << endl;
			break;
		case 11:
			cout << "de Rois." << endl;
			break;
		case 12:
			cout << "d'As." << endl;
			break;
		default:
			cout << "Inconnu" << endl;
			break;
		}
		break;
	case 2:
		cout << "Double paire ";
		switch (comb[1]) {
		case 0:
			cout << "de 2 et ";
			break;
		case 1:
			cout << "de 3 et " ;
			break;
		case 2:
			cout << "de 4 et ";
			break;
		case 3:
			cout << "de 5 et " ;
			break;
		case 4:
			cout << "de 6 et " ;
			break;
		case 5:
			cout << "de 7 et " ;
			break;
		case 6:
			cout << "de 8 et " ;
			break;
		case 7:
			cout << "de 9 et " ;
			break;
		case 8:
			cout << "de 10 et ";
			break;
		case 9:
			cout << "de Valets et " ;
			break;
		case 10:
			cout << "de Dames et " ;
			break;
		case 11:
			cout << "de Rois et " ;
			break;
		case 12:
			cout << "d'As et " ;
			break;
		default:
			cout << "Inconnu" << endl;
			break;
		}
		switch (comb[2]) {
		case 0:
			cout << "de 2." << endl;
			break;
		case 1:
			cout << "de 3." << endl;
			break;
		case 2:
			cout << "de 4." << endl;
			break;
		case 3:
			cout << "de 5." << endl;
			break;
		case 4:
			cout << "de 6." << endl;
			break;
		case 5:
			cout << "de 7." << endl;
			break;
		case 6:
			cout << "de 8." << endl;
			break;
		case 7:
			cout << "de 9." << endl;
			break;
		case 8:
			cout << "de 10." << endl;
			break;
		case 9:
			cout << "de Valets." << endl;
			break;
		case 10:
			cout << "de Dames." << endl;
			break;
		case 11:
			cout << "de Rois." << endl;
			break;
		case 12:
			cout << "d'As." << endl;
			break;
		default:
			cout << "Inconnu" << endl;
			break;
		}
		break;
	case 3:
		cout << "Brelan ";
		switch (comb[1]) {
		case 0:
			cout << "de 2." << endl;
			break;
		case 1:
			cout << "de 3." << endl;
			break;
		case 2:
			cout << "de 4." << endl;
			break;
		case 3:
			cout << "de 5." << endl;
			break;
		case 4:
			cout << "de 6." << endl;
			break;
		case 5:
			cout << "de 7." << endl;
			break;
		case 6:
			cout << "de 8." << endl;
			break;
		case 7:
			cout << "de 9." << endl;
			break;
		case 8:
			cout << "de 10." << endl;
			break;
		case 9:
			cout << "de Valets." << endl;
			break;
		case 10:
			cout << "de Dames." << endl;
			break;
		case 11:
			cout << "de Rois." << endl;
			break;
		case 12:
			cout << "d'As." << endl;
			break;
		default:
			cout << "Inconnu" << endl;
			break;
		}
		break;
	case 4:
		cout << "Suite ";
		switch (comb[1]) {
		case 0:
			cout << "au 2." << endl;
			break;
		case 1:
			cout << "au 3." << endl;
			break;
		case 2:
			cout << "au 4." << endl;
			break;
		case 3:
			cout << "au 5." << endl;
			break;
		case 4:
			cout << "au 6." << endl;
			break;
		case 5:
			cout << "au 7." << endl;
			break;
		case 6:
			cout << "au 8." << endl;
			break;
		case 7:
			cout << "au 9." << endl;
			break;
		case 8:
			cout << "au 10." << endl;
			break;
		case 9:
			cout << "au Valet." << endl;
			break;
		case 10:
			cout << "a la Dame." << endl;
			break;
		case 11:
			cout << "au Roi." << endl;
			break;
		case 12:
			cout << "a l'As." << endl;
			break;
		default:
			cout << "Inconnu" << endl;
			break;
		}
		break;
	case 5:
		cout << "Couleur ";
		switch (comb[1]) {
		case 0:
			cout << "a coeur.";
			break;
		case 1:
			cout << "a carreau.";
			break;
		case 2:
			cout << "a trefle.";
			break;
		case 3:
			cout << "a pique.";
			break;
		default:
			cout << "Couleur inconnue";
			break;
		}
		break;
	case 6:
		cout << "Full ";
		switch (comb[1]) {
		case 0:
			cout << "aux 2 " << endl;
			break;
		case 1:
			cout << "aux 3 " << endl;
			break;
		case 2:
			cout << "aux 4 " << endl;
			break;
		case 3:
			cout << "aux 5 " << endl;
			break;
		case 4:
			cout << "aux 6 " << endl;
			break;
		case 5:
			cout << "aux 7 " << endl;
			break;
		case 6:
			cout << "aux 8 " << endl;
			break;
		case 7:
			cout << "aux 9 " << endl;
			break;
		case 8:
			cout << "aux 10 " << endl;
			break;
		case 9:
			cout << "aux Valets " << endl;
			break;
		case 10:
			cout << "aux Dames " << endl;
			break;
		case 11:
			cout << "aux Rois " << endl;
			break;
		case 12:
			cout << "aux As " << endl;
			break;
		default:
			cout << "Inconnu" << endl;
			break;
		}
		break;
		switch (comb[2]) {
		case 0:
			cout << "par les 2." << endl;
			break;
		case 1:
			cout << "par les 3." << endl;
			break;
		case 2:
			cout << "par les 4." << endl;
			break;
		case 3:
			cout << "par les 5." << endl;
			break;
		case 4:
			cout << "par les 6." << endl;
			break;
		case 5:
			cout << "par les 7." << endl;
			break;
		case 6:
			cout << "par les 8." << endl;
			break;
		case 7:
			cout << "par les 9." << endl;
			break;
		case 8:
			cout << "par les 10." << endl;
			break;
		case 9:
			cout << "par les Valets." << endl;
			break;
		case 10:
			cout << "par les Dames." << endl;
			break;
		case 11:
			cout << "par les Rois." << endl;
			break;
		case 12:
			cout << "par les As." << endl;
			break;
		default:
			cout << "Inconnu" << endl;
			break;
		}
	case 7:
		cout << "Carré ";
		switch (comb[1]) {
		case 0:
			cout << "de 2." << endl;
			break;
		case 1:
			cout << "de 3." << endl;
			break;
		case 2:
			cout << "de 4." << endl;
			break;
		case 3:
			cout << "de 5." << endl;
			break;
		case 4:
			cout << "de 6." << endl;
			break;
		case 5:
			cout << "de 7." << endl;
			break;
		case 6:
			cout << "de 8." << endl;
			break;
		case 7:
			cout << "de 9." << endl;
			break;
		case 8:
			cout << "de 10." << endl;
			break;
		case 9:
			cout << "de Valets." << endl;
			break;
		case 10:
			cout << "de Dames." << endl;
			break;
		case 11:
			cout << "de Rois." << endl;
			break;
		case 12:
			cout << "d'As." << endl;
			break;
		default:
			cout << "Inconnu" << endl;
			break;
		}
		break;
	case 8:
		cout << "Quinte flush ";
		switch (comb[1]) {
		case 0:
			cout << "au 2." << endl;
			break;
		case 1:
			cout << "au 3." << endl;
			break;
		case 2:
			cout << "au 4." << endl;
			break;
		case 3:
			cout << "au 5." << endl;
			break;
		case 4:
			cout << "au 6." << endl;
			break;
		case 5:
			cout << "au 7." << endl;
			break;
		case 6:
			cout << "au 8." << endl;
			break;
		case 7:
			cout << "au 9." << endl;
			break;
		case 8:
			cout << "au 10." << endl;
			break;
		case 9:
			cout << "au Valet." << endl;
			break;
		case 10:
			cout << "a la Dame." << endl;
			break;
		case 11:
			cout << "au Roi." << endl;
			break;
		case 12:
			cout << "a l'As." << endl;
			break;
		default:
			cout << "Inconnu" << endl;
			break;
		}
		break;
	case 9:
		cout << "Quinte flush royale ";
		switch (comb[1]) {
		case 0:
			cout << "a coeur.";
			break;
		case 1:
			cout << "a carreau.";
			break;
		case 2:
			cout << "a trefle.";
			break;
		case 3:
			cout << "a pique.";
			break;
		default:
			cout << "Couleur inconnue";
			break;
		}
		break;
	default:
		cout << "Combinaison inconnue ";
		break;
	}
	
	
}

const int Jeu::gagnant()
{
	//Renvoie l'id du gagnant, -1 en cas de match nul
	if (combinaison(0)[0] > combinaison(1)[0]) {
		return 0;
	}
	else if (combinaison(0)[0] < combinaison(1)[0]) {
		return 1;
	}
	else if (combinaison(0)[0] == combinaison(1)[0] && combinaison(0)[0] == 9) {//Cas deux quintes flushs royales
		return -1;
	}
	else {
		if (combinaison(0)[1] > combinaison(1)[1]) {
			return 0;
		}
		else if (combinaison(0)[1] < combinaison(1)[1]) {
			return 1;
		}
		else {
			if (combinaison(0)[2] > combinaison(1)[2]) {
				return 0;
			}
			else if (combinaison(0)[2] < combinaison(1)[2]) {
				return 1;
			}
			else {
				return -1;
			}
		}
	}
}

void Jeu::sauver_jeu(ofstream &flux)
{
	//Recopie dans le fichier texte
	if (!flux.is_open()) {
		cout << "Erreur d'ouverture" << endl;
	}
	else
	{
		flux <<get_manche() << endl; // Ecriture de la manche
		flux << get_tour() << endl; // Ecriture du tour
		flux << get_phase() << endl; // Ecriture de la phase
		flux << get_pot() << endl; // Ecriture du pot
		for (int i = 0; i < 5; i++) {
			flux << cartesTable_[i].get_idCarte() << endl; // Ecriture des cartes du jeu
		}
					
		}
		if (!flux.good()) {
			cout << "Erreur d'ecriture" << endl;
		}
		else {
			cout << "Sauvegarde effectuee avec succes" << endl;
		}
		flux.close();
	}
void Jeu::sauver_joueur(const int id,ofstream &flux)
{
	joueurs_[id].sauver_joueur(flux);
}

void Jeu::lire_jeu(ifstream& flux)
{
	if (!flux.is_open()) {
		cout << "Erreur d'ouverture" << endl;
		system("cls");
	}
	else{
		int id0 ,id1, id2, id3, id4;
		flux >> manche_;
		flux >> tour_;
		flux >> phase_;
		flux >> pot_;
		flux >> id0;
		flux >> id1;
		flux >> id2;
		flux >> id3;
		flux >> id4;
		cartesTable_[0].set_idCarte(id0);
		cartesTable_[1].set_idCarte(id1);
		cartesTable_[2].set_idCarte(id2);
		cartesTable_[3].set_idCarte(id3);
		cartesTable_[4].set_idCarte(id4);
		/*if (!flux.good()) {
			cout << "Erreur de lecture" << endl;
		}
		else {
			cout << "Lecture terminée" << endl;
		}*/
		}
	flux.close();

}

void Jeu::lire_joueur(const int id, ifstream& flux)
{
	joueurs_[id].lire_joueur(flux);

}


