#pragma once
class Cartes
{
	    //D�claration des attributs de la classe Cartes
		int idCarte_; //1-13 Coeur | 14-26 Carreau | 27-39 Tr�fle | 40-52 Pique
		int couleur_; //1 Coeur | 2 Carreau | 3 Tr�fle | 4 Pique
		int symbole_; //2=2 ... 11=V 12=Re 13=Roi 14=As
	private :
		//D�claration des m�thodes de la classe Cartes
		Cartes(int idCarte);
		const int get_idCarte() { return idCarte_; }
		void set_idCarte(const int idCarte) { idCarte_ = idCarte; }
		const int get_couleur() { return couleur_; }
		void set_couleur(const int couleur) { couleur_ = couleur; }
		const int get_symbole() { return symbole_; };
		void set_symbole(const int symbole) { symbole_ = symbole; }

};

