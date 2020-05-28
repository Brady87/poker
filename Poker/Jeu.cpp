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
	remove("jeu.txt");
	remove("serveur.txt");
	remove("client.txt");
}

const void Jeu::afficher_cartes_tables()
{
	if (tour_ == 1) { //1er tour : on affiche rien
		cout << endl;
	}
	else if (tour_ == 2) {//2e tour : on affiche les 3 premières cartes
		for (int i = 0; i < 3; i++) {
			cartesTable_[i].afficher_cartes();
			cout << " | ";
		}
	}
	else if (tour_ == 3) {// 3e tour : on affiche les 4 premières cartes
		for (int i = 0; i < 4; i++) {
			cartesTable_[i].afficher_cartes();
			cout << " | ";
		}
	}
	else { //4e et dernier tour : on affiche les 5 cartes
		for (int i = 0; i < 5; i++) {
			cartesTable_[i].afficher_cartes();
			cout << " | ";
		}
	}
}

const void Jeu::affichage(int rep)
{
	Joueur vous, adversaire;
	if (rep == 0) {
		vous = *joueurClient_;
		adversaire = *joueurServeur_;
	}
	else {
		vous = *joueurServeur_;
		adversaire = *joueurClient_; 
	}
	cout << "Manche : " << manche_ << endl;
	cout << "Tour : " << tour_ << endl;
	cout << "----------------------------------------" << endl;
	cout << "Vous ";
	if (vous.get_distributeur()) {
		cout << "(D) : ";
	}
	else {
		cout << ": ";
	}
	vous.affciher_jetons();
	cout << "Votre mise : " << vous.get_mise();
	if (vous.get_mise() == 0) {
		cout << " jeton." << endl;
	}
	else {
		cout << " jetons." << endl;
	}
	cout << endl;
	cout <<adversaire.get_pseudo();
	if (adversaire.get_distributeur()) {
		cout << " (D) : ";
	}
	else {
		cout << ": ";
	}
	adversaire.affciher_jetons();
	cout << "Mise adverse : " << adversaire.get_mise();
	if (adversaire.get_mise() == 0) {
		cout<< " jeton." << endl;
	}
	else {
		cout << " jetons." << endl;
	}
	cout << adversaire.get_pseudo()<<" ";
	adversaire.afficher_choix();
	cout << endl;
	cout << "Pot : " << pot_ << endl;
	cout << "Votre main : ";
	vous.afficher_cartes_joueur();
	cout << "Sur la table : ";
	afficher_cartes_tables();
	cout << endl;
	cout << "----------------------------------------" << endl;
}

void Jeu::set_joueurs(Joueur &joueur)
{
	int id = joueur.get_id();
	if (id == 0) {
		joueurClient_ = &joueur;
	}
	if (id == 1) {
		joueurServeur_ = &joueur;
	}
}


void Jeu::choix(int rep)
{

	Joueur vous, adversaire;
	int ch;
	bool valide = false; //Vérifie que le choix effectué est valide
	do
	{
		if (rep == 0) {
			vous = *joueurClient_;
			adversaire = *joueurServeur_;
		}
		else {
			vous = *joueurServeur_;
			adversaire = *joueurClient_;
		}
		cout << "Veuillez rentrer votre choix " << endl;
		cout << "1- Checker " << endl;
		cout << "2- Miser/Relancer " << endl;
		cout << "3- Suivre " << endl;
		cout << "4- Se coucher " << endl;
		cin >> ch;
		switch (ch)
		{
		case 1:
			if ((!vous.get_distributeur() && adversaire.get_mise()==0) || adversaire.get_choix()==1)
			{//Si on est le premier a parlé ou que l'adversaire a checké on peut checker
				cout << "Vous checkez" << endl;
				valide = true;
			}
			else {
				cout << "Vous ne pouvez pas checkez." << endl;
			}
			break;
		case 2:
			int mise;
			if (vous.get_mise() == 0) {
				cout << "Mise de combien ?" << endl;
			}
			else {
				cout << "Vous avez deja mise : " << vous.get_mise() << "." << endl;
				cout << "Remisez de combien ?" << endl;
			}
			cin >> mise;
			if (vous.get_jetons() < mise) {
				cout << "Mise superieure a votre capital. Vous ne pouvez miser que " << vous.get_jetons()<<"."<< endl;
			}
			else if (mise + vous.get_mise() < adversaire.get_mise() ) {
				cout << "Mise insuffisante : vous devez miser au moins : " << adversaire.get_mise()- vous.get_mise() << "." << endl;
			}
			else if (mise == 0) {
				cout << "Vous ne pouvez pas miser zero !" << endl;
			}
			else {
				if (adversaire.get_jetons() + adversaire.get_mise()  - vous.get_mise() <mise) {
					cout << "Votre mise excede les possibilites de l'adversaire." << endl;
					mise = adversaire.get_jetons() + adversaire.get_mise() - vous.get_mise();
					cout << "Vous misez " << mise << "." << endl;
					system("pause");
					
				}
				vous.set_jetons(vous.get_jetons() - mise); // MàJ nbre de jetons
				vous.set_mise(vous.get_mise() + mise); // MàJ mise
				set_pot(get_pot() + mise); // On met à jour le pot
				valide = true;
			break;
		case 3:
			if (adversaire.get_choix() == 0) {
				cout << "Votre adversaire n'a pas encore parle." << endl;
			}
			else if (vous.get_mise()+ vous.get_jetons() < adversaire.get_mise()) {
				cout << "Vous ne pouvez pas suivre." << endl;
			}
			else {
				vous.set_jetons(vous.get_jetons() - (adversaire.get_mise() - vous.get_mise()));
				cout << "Vous vous alignez en misant " << adversaire.get_mise() - vous.get_mise() << endl;
				set_pot(get_pot() + (adversaire.get_mise() - vous.get_mise()));// On s'aligne sur le pot
				vous.set_mise(adversaire.get_mise()); //On s'aligne sur la mise de l'adversaire
				valide = true;
			}
			break;
			case 4:
				cout <<"Vous vous couchez." <<endl;
				valide = true;
				break;
			}

		default:
				cout <<"Choix non valide, veuillez rentrer un choix valide" <<endl;
				break;
		}

	} while (!valide);
	vous.set_choix(ch); // On affecte le choix
	//Réaffectation
	if (rep == 0) {
		*joueurClient_=vous;
		 *joueurServeur_= adversaire;
	}
	else {
		*joueurServeur_= vous ;
		*joueurClient_ = adversaire;
	}
}

void Jeu::nouvelle_donne()
{
	//Pioche par défaut
	vector<Cartes> pioche(52);
	for (int i = 0; i < 52; i++) {
		Cartes c(i);
		pioche[i] = c;
	}
	pioche_ = pioche;
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
	Cartes* mainTable = new Cartes[5];
	Cartes* main1 = new Cartes[2];
	//On prend la main du joueur ayant idJoueur
	if (idJoueur == 0) {
		main1 = joueurClient_->get_main();
		mainTable = cartesTable_;
	}
	if (idJoueur == 1) {
		main1 = joueurServeur_->get_main();
		mainTable = cartesTable_;
	}
	
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
				idValeurCombinaison1 = i;
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
		int j = i+1;
		while (tabSymbole[12 - j] == 0 && j <= 12) {
			j++;
		}
		idCombinaison = 0;
		idValeurCombinaison = 12 - i;
		idValeurCombinaison1 = j;
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
	comb[0] = combinaison(idJoueur)[0];
	comb[1] = combinaison(idJoueur)[1];
	comb[2] = combinaison(idJoueur)[2];
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
		switch (comb[2]) {
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
			cout << "inconnue.";
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
		cout << "Carre ";
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
	int* comb0 = new int[3];
	int* comb1 = new int[3];
	for (int i = 0; i < 3; i++) {
		comb0[i] = combinaison(0)[i];
		comb1[i] = combinaison(1)[i];
	}
	//Renvoie l'id du gagnant, -1 en cas de match nul
	if (comb0[0] > comb1[0]) {
		return 0;
	}
	else if (comb0[0] < comb1[0]) {
		return 1;
	}
	else if (comb0[0] == comb1[0] && comb0[0] == 9) {//Cas deux quintes flushs royales
		return -1;
	}
	else {
		if (comb0[1] > comb1[1]) {
			return 0;
		}
		else if (comb0[1] < comb1[1]) {
			return 1;
		}
		else {
			if (comb0[2] > comb1[2]) {
				return 0;
			}
			else if (comb0[2] < comb1[2]) {
				return 1;
			}
			else {
				return -1;
			}
		}
	}
}

void Jeu::sauver_jeu(ofstream &flux,const string &fichier)
{
		flux.close();
		flux.open(fichier);
		flux <<get_manche() << endl; // Ecriture de la manche
		flux << get_tour() << endl; // Ecriture du tour
		flux << get_phase() << endl; // Ecriture de la phase
		flux << get_pot() << endl; // Ecriture du pot
		for (int i = 0; i < 5; i++) {
			flux << cartesTable_[i].get_idCarte() << endl; // Ecriture des cartes du jeu
		}
		flux.close();
	}
void Jeu::sauver_joueur(const int id,ofstream &flux,const string &fichier)
{
	if (id == 0) {
		joueurClient_->sauver_joueur(flux,fichier);
	}
	if (id == 1) {
		joueurServeur_->sauver_joueur(flux,fichier);
	}
	
}

void Jeu::lire_jeu(ifstream &flux,const string &fichier)
{
	flux.close();
	flux.open(fichier);
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
	flux.close();
}

void Jeu::lire_joueur(const int id, ifstream& flux,const string &fichier)
{
	if (id == 0) {
		joueurClient_->lire_joueur(flux,fichier);
	}
	if (id == 1) {
		joueurServeur_->lire_joueur(flux,fichier);
	}
}


