#pragma once
#include<string>
#include"Cartes.h"
#include<fstream>
using namespace std;

class Joueur
{	
		//Déclaration des attributs de la classe joueur 
		int id_;
		string pseudo_;
		int jetons_ ;
		bool distributeur_ ;
		bool quiParle_;
		int mise_;
		Cartes* main_= new Cartes [2];
	public :
		//Déclaration des méthodes de la classe joueur 
		Joueur(int id=0,string pseudo="Inconnu", int jetons = 1000 , bool distributeur=false); //Déclaration du constructeur
		~Joueur();//Déclaration du destructeur
		const int get_id() const {return id_;} 
		void set_id(const int id) {id_ = id; }
		const int get_jetons() const {return jetons_;}
		void set_jetons(const int jetons) {jetons_ = jetons;}
		Cartes* get_main() { return main_; }
		void set_main(Cartes* main) { main_ = main; }
		bool get_distributeur()  {return distributeur_;}
		void set_distributeur(bool distributeur) { distributeur_ = distributeur; }
		bool get_quiParle() { return quiParle_; }
		void set_quiParle(bool quiParle) { quiParle_ = quiParle; }
		void set_mise(const int mise) { mise_ = mise; }
		const int get_mise() const { return mise_; }
		string get_pseudo() { return pseudo_; }
		void set_pseudo(string pseudo) { pseudo_ = pseudo; }
		void afficher_cartes_joueur(); //Méthode afficher les cartes du joueur
		void affciher_jetons(); //Méthode afficher les jetons du joueur
		
};