#pragma once
#include<string>
using namespace std;

class Jeu
{
		//D�claration des attributs de la classe Jeu
		int manche_;
		int tour_;
		int pot_;
		//Cartes a rajouter
		int *idJoueur_ = new int[2];
	public:
		Jeu(int manche = 1, int tour = 1, int pot = 0, int* idJoueur=nullptr); //D�claration du constructeur
		~Jeu(); //D�claration du destructeur
		//D�claration des m�thodes de la classe Joueur
		const int get_manche() { return manche_; }
		void set_manche(const int manche) { manche_ = manche; }
		const int get_tour() {return tour_;}
		void set_tour(const int tour) { tour_ = tour; } 
		const int get_pot() { return pot_; };
		void set_pot(const int pot) { pot_ = pot; }
		void afficher_cartes_tables();
	
		//Distribue les cartes en les prenant dans la pioche
		// !!! Besoin de la classe Carte
		//M�lange les cartes
		// !!! Besoin de la classe Carte


};

