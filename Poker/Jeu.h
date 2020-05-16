#pragma once
#include<string>
#include<iostream>
#include"Cartes.h"
#include <vector>
#include "Joueur.h"
#include<fstream>
using namespace std;

class Jeu
{
		//D�claration des attributs de la classe Jeu
		int manche_;
		int tour_;
		int phase_;
		int pot_;
		Cartes* cartesTable_= new Cartes[5];
		vector<Cartes> pioche_;
		int* idJoueur_ = new int[2];
		Joueur* joueurs_ = new Joueur[2];
	public:
		Jeu(int manche = 1, int tour = 1, int pot = 0); //D�claration du constructeur
		~Jeu(); //D�claration du destructeur
		//D�claration des m�thodes de la classe Joueur
		const int get_manche() { return manche_; }
		void set_manche(const int manche) { manche_ = manche; }
		const int get_tour() {return tour_;}
		void set_tour(const int tour) { tour_ = tour; } 
		const int get_pot() { return pot_; };
		void set_pot(const int pot) { pot_ = pot; }
		const int get_phase() { return phase_; };
		void set_phase(const int phase) { phase_ = phase; }
		const void afficher_cartes_tables();
		const void affichage(const int rep) ;
		void set_joueurs(Joueur joueur) { joueurs_[joueur.get_id()] = joueur; }
		void choix(int rep);
		void set_cartesTable(Cartes* cartesTable) { cartesTable_ = cartesTable; }
		Cartes* distribuerCartes(const int nbre); //distribue les cartes en les prenant dans la pioche
		void melangerCartes(); //M�lange les cartes
		int* combinaison(const int idJoueur);
		const void nomCombinaison(const int idJoueur);
		const int gagnant();
		void sauver_jeu(ofstream &flux);
		void sauver_joueur(const int id, ofstream &flux);
		void lire_jeu(ifstream &flux);
		void lire_joueur(const int id, ifstream& flux);
};

