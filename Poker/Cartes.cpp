#include "Cartes.h"


Cartes::Cartes(const int idCarte) {
	idCarte_ = idCarte;
	//Gestion des couleurs
	if (idCarte <= 12) {
		couleur_ = 0; //Coeur
	}
	else if (idCarte>=13 && idCarte<=25) {
		couleur_ = 1; //Carreau
	}
	else if (idCarte >= 26 && idCarte <= 38) {
		couleur_ = 2; //Trèfle
	}
	else {
		couleur_ = 3; //Pique
	}
		symbole_ = idCarte % 13 ;
}

void Cartes::set_idCarte(const int idCarte)
{
	idCarte_ = idCarte;
	//Gestion des couleurs
	if (idCarte <= 12) {
		couleur_ = 0; //Coeur
	}
	else if (idCarte >= 13 && idCarte <= 25) {
		couleur_ = 1; //Carreau
	}
	else if (idCarte >= 26 && idCarte <= 38) {
		couleur_ = 2; //Trèfle
	}
	else {
		couleur_ = 3; //Pique
	}
	symbole_ = idCarte % 13;
}


void Cartes::afficher_cartes()
{
	//Affichage des symboles
	if (get_symbole() < 9) { //si le symbole est un nombre
		cout << get_symbole()+2;
	}
	else {
		char symbole;
		switch(get_symbole()){ // sinon si c'est un as ou une figure
		case 9:
			symbole = 'V'; //Valet
			break;
		case 10:
			symbole = 'D'; //Dame
			break;
		case 11:
			symbole = 'R'; //Roi
			break;
		case 12:
			symbole = 'A'; //As
			break;
		default:
			symbole = '!'; //Non défini
			break;
		}
		cout << symbole;
	}
	cout << " ";
	//Affichage des couleurs
	switch (get_couleur())
	{
	case 0:
		
		cout <<"Coeur"; //Coeur
		break;
	case 1:
		cout << "Carreau";//Carreau
		break;
	case 2:
		cout << "Trefle"; //Trèfle
		break;
	case 3:
		cout << "Pique"; //Pique
		break;
	default:
		cout << "!"; //Non défini
		break;
	}
}
