#pragma once
#include<string>
#include"Cartes.h"
using namespace std;

class Joueur
{	
		//D�claration des attributs de la classe joueur 
		int id_;
		string pseudo_;
		int jetons_ ;
		bool distributeur_ ;
		Cartes* main_= new Cartes [2];
	public :
		//D�claration des m�thodes de la classe joueur 
		Joueur(int id=0,string pseudo="Inconnu", int jetons = 1000 , bool distributeur=false); //D�claration du constructeur
		~Joueur();//D�claration du destructeur
		const int get_id() const {return id_;} 
		void set_id(const int id) {id_ = id; }
		const int get_jetons() const {return jetons_;}
		void set_jetons(const int jetons) {jetons_ = jetons;}
		Cartes* get_main() { return main_; }
		void set_main(Cartes* main) { main_ = main; }
		bool get_distributeur()  {return distributeur_;}
		void set_distributeur(bool distributeur) { distributeur_ = distributeur; }
		string get_pseudo() { return pseudo_; }
		void set_pseudo(string pseudo) { pseudo_ = pseudo; }
		void afficher_cartes_joueur(); //M�thode afficher les cartes du joueur
		void affciher_jetons(); //M�thode afficher les jetons du joueur

};