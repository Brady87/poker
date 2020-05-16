#include "Joueur.h"
#include<iostream>
using namespace std;


Joueur::Joueur(int id, string pseudo, int jetons, bool distributeur, bool quiParle, int mise, int choix)
{
	id_ = id;
	pseudo_ = pseudo;
	jetons_ = jetons;
	distributeur_ = distributeur;
	quiParle_ = quiParle;
	mise_ = mise;
	choix_ = choix;
}

Joueur::~Joueur()
{
	delete main_;
}

void Joueur::afficher_cartes_joueur()
{
	main_[0].afficher_cartes(); //Affichage de la première carte
	cout << " | ";
	main_[1].afficher_cartes(); // Affichage de la seconde carte
}

void Joueur::affciher_jetons()
{
	if (jetons_ == 0) //Cas singulier
	{
		cout << jetons_ << " jeton." << endl;
	}
	else { // Cas pluriel
		cout << jetons_ << " jetons." << endl;
	}
}

void Joueur::sauver_joueur(ofstream& flux)
{
	//Recopie dans le fichier texte
	/*if (!flux.is_open()) {
		cout << "Erreur d'ouverture" << endl;
	}
	else
	{*/
		flux << id_ << endl; // Ecriture de l'id
		flux << pseudo_ << endl; // Ecriture du pseudo
		flux << choix_ << endl; //Ecriture du choix
		flux << jetons_ << endl; // Ecriture du nbre jetons
		flux << distributeur_ << endl; //Ecriture si distributeur
		flux << quiParle_ << endl; //Ecriture si parle
		flux << mise_ << endl; // Ecriture de la mise
		for (int i = 0; i < 2; i++) {
			flux << main_[i].get_idCarte() << endl; // Ecriture des cartes du jeu
		}

	//}
	if (!flux.good()) {
		cout << "Erreur d'ecriture" << endl;
	}
	else {
		cout << "Sauvegarde effectuee avec succes" << endl;
	}
	flux.close();
}

void Joueur::lire_joueur(ifstream &flux)
{
	if (!flux.is_open()) {
		cout << "Erreur d'ouverture" << endl;
	}
	else {
		int id0, id1;
		Cartes* main = new Cartes[2];
		flux >> id_;
		flux >> pseudo_;
		flux >> choix_;
		flux >> jetons_;
		flux >> distributeur_;
		flux >> quiParle_;
		flux >> mise_;
		flux >> id0;
		flux >> id1;
		Cartes c0(id0);
		Cartes c1(id1);
		main[0] = c0;
		main[1] = c1;
		main_ = main;
		if (!flux.good()) {
			cout << "Erreur de lecture" << endl;
		}
		else {
			cout << "Lecture terminée" << endl;
		}
	}

}





