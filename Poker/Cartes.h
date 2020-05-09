#pragma once
#include<iostream>
using namespace std;
class Cartes
{
	    //Déclaration des attributs de la classe Cartes
		int idCarte_; //0-12 Coeur | 13-25 Carreau | 26-38 Trèfle | 39-51 Pique
		int couleur_; //0 Coeur | 1 Carreau | 2 Trèfle | 3 Pique
		int symbole_; //0=>2 ... 9=>V 10=>Dame 11=>Roi 12=As
	public :
		//Déclaration des méthodes de la classe Cartes
		Cartes(int idCarte=0);  // Constructeur
		const int get_idCarte() { return idCarte_; }
		void set_idCarte(const int idCarte) { idCarte_ = idCarte; }
		const int get_couleur() { return couleur_; }
		void set_couleur(const int couleur) { couleur_ = couleur; }
		const int get_symbole() { return symbole_; };
		void set_symbole(const int symbole) { symbole_ = symbole; }
		void afficher_cartes();
};

