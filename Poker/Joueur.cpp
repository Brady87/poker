#include "Joueur.h"
#include<iostream>
using namespace std;

Joueur::Joueur(int id, string pseudo, int jetons, bool distributeur,bool quiParle, int mise)
{
	id_ = id;
	pseudo_ = pseudo;
	jetons_ = jetons;
	distributeur_ = distributeur;
	quiParle_ = qui parle;
	mise_ = mise;
}

Joueur::~Joueur()
{
}

void Joueur::afficher_cartes_joueur()
{
	main_[0].afficher_cartes; //Affichage de la première carte
	cout << " | ";
	main_[1].afficher_cartes; // Affichage de la seconde carte
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




