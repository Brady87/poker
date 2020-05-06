#pragma once
#include<string>
using namespace std;

class Joueur
{	
		//D�claration des attributs de la classe joueur 
		int id_;
		int jetons_ ;
		bool distributeur_ ;
		Main* main_;
	public :
		//D�claration des m�thodes de la classe joueur 
		Joueur(int id, int jetons = 1000 , bool distributeur=false); //D�claration du constructeur
		~Joueur();//D�claration du destructeur
		const int get_id() const {return id_;} 
		void set_id(const int id); 
		const int get_jetons() const {return jetons_;}
		void set_jetons(const int jetons);
		bool get_distributeur()  {return distributeur_;}
		void set_distributeur(bool distributeur);
		void afficher_cartes_joueur(); //M�thode afficher les cartes du joueur
		void affciher_jetons(); //M�thode afficher les jetons du joueur

};