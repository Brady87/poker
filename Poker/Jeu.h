#pragma once
#include<string>
using namespace std;

class Jeu
{
		//Déclaration des attributs de la classe Jeu
		int manche_;
		int tour_;
		int pot_;
		//Cartes a rajouter
		int *idJoueur_ = new int[2];
	public:
		Jeu(int manche = 1, int tour = 1, int pot = 0, int* idJoueur=nullptr); //Déclaration du constructeur
		~Jeu(); //Déclaration du destructeur
		//Déclaration des méthodes de la classe Joueur
		const int get_manche() { return manche_; }
		void set_manche(const int manche) { manche_ = manche; }
		const int get_tour() {return tour_;}
		void set_tour(const int tour) { tour_ = tour; } 
		const int get_pot() { return pot_; };
		void set_pot(const int pot) { pot_ = pot; }
		void afficher_cartes_tables();
	
		//Distribue les cartes en les prenant dans la pioche
		// !!! Besoin de la classe Carte
		//Mélange les cartes
		// !!! Besoin de la classe Carte


};

