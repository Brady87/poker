#pragma once
#include<string>
using namespace std;

class Joueur
{	
		//Déclaration des attributs de la classe joueur 
		int id_;
		int jetons_ ;
		bool distributeur_ ;
		Main* main_;
	public :
		//Déclaration des méthodes de la classe joueur 
		Joueur(int id, int jetons = 1000 , bool distributeur=false); //Déclaration du constructeur
		~Joueur();//Déclaration du destructeur
		const int get_id() const {return id_;} 
		void set_id(const int id) {id_ = id; }
		const int get_jetons() const {return jetons_;}
		void set_jetons(const int jetons) {jetons_ = jetons;}
		bool get_distributeur()  {return distributeur_;}
		void set_distributeur(bool distributeur) { distributeur_ = distributeur; }
		void afficher_cartes_joueur(); //Méthode afficher les cartes du joueur
		void affciher_jetons(); //Méthode afficher les jetons du joueur

};