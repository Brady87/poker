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
		couleur_ = 2; //Tr�fle
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
		couleur_ = 2; //Tr�fle
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
		cout << get_symbole();
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
			symbole = '!'; //Non d�fini
			break;
		}
		cout << symbole;
	}
	//Affichage des couleurs
	switch (get_couleur())
	{
	case 0:
		cout <<"Co"; //Coeur
		break;
	case 1:
		cout << "Ca";//Carreau
		break;
	case 2:
		cout << "Tr"; //Tr�fle
		break;
	case 3:
		cout << "Pi"; //Pique
	default:
		cout << "!"; //Non d�fini
		break;
	}
}
