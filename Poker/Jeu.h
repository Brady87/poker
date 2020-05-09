#pragma once
#include<string>
#include<iostream>
#include"Cartes.h"
#include <vector>
#include "Joueur.h"
using namespace std;

class Jeu
{
		//Déclaration des attributs de la classe Jeu
		int manche_;
		int tour_;
		int couleur_;
		int pot_;
		Cartes* cartesTable_= new Cartes[5];
		vector<Cartes> pioche_;
		int* idJoueur_ = new int[2];
		Joueur* joueurs_ = new Joueur[2];
	public:
		Jeu(int manche = 1, int tour = 1, int pot = 0, Cartes* cartesTable = nullptr, vector<Cartes> pioche = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51}, int* idJoueur = nullptr, Joueur* joueurs_=nullptr); //Déclaration du constructeur
		~Jeu(); //Déclaration du destructeur
		//Déclaration des méthodes de la classe Joueur
		const int get_manche() { return manche_; }
		void set_manche(const int manche) { manche_ = manche; }
		const int get_tour() {return couleur_;}
		void set_tour(const int tour) { couleur_ = tour; } 
		const int get_pot() { return pot_; };
		void set_pot(const int pot) { pot_ = pot; }
		void afficher_cartes_tables();
		Cartes* distribuerCartes(const int nbre); //distribue les cartes en les prenant dans la pioche
		void melangerCartes(); //Mélange les cartes
		int* combinaison(const int idJoueur);


};

