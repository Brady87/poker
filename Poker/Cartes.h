#pragma once
#include<iostream>
using namespace std;
class Cartes
{
	    //D�claration des attributs de la classe Cartes
		int idCarte_; //0-12 Coeur | 13-25 Carreau | 26-38 Tr�fle | 39-51 Pique
		int couleur_; //0 Coeur | 1 Carreau | 2 Tr�fle | 3 Pique
		int symbole_; //0=>2 ... 9=>V 10=>Dame 11=>Roi 12=As
	public :
		//D�claration des m�thodes de la classe Cartes
		Cartes(const int idCarte=0);  // Constructeur
		const int get_idCarte() { return idCarte_; }
		void set_idCarte(const int idCarte);
		const int get_couleur() { return couleur_; }
		const int get_symbole() { return symbole_; };
		void afficher_cartes();
};

