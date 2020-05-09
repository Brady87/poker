#include "Cartes.h"


Cartes::Cartes(int idCarte) {
	idCarte_ = idCarte;
	//Gestion des couleurs
	if (idCarte <= 13) {
		couleur_ = 1; //Coeur
	}
	else if (idCarte>=14 && idCarte<=26) {
		couleur_ = 2; //Carreau
	}
	else if (idCarte >= 27 && idCarte <= 39) {
		couleur_ = 3; //Trèfle
	}
	else {
		couleur_ = 4; //Pique
	}
	if (idCarte % 13 == 0) {
		symbole_ = 14;
	}
	else {
		symbole_ = idCarte % 13 + 1;
	}
}

void Cartes::afficher_cartes()
{
	//Affichage des symboles
	if (get_symbole() < 11) { //si le symbole est un nombre
		cout << get_symbole();
	}
	else {
		char symbole;
		switch(get_symbole()){ // sinon si c'est un as ou une figure
		case 11:
			symbole = 'V'; //Valet
			break;
		case 12:
			symbole = 'D'; //Dame
			break;
		case 13:
			symbole = 'R'; //Roi
			break;
		case 14:
			symbole = 'A'; //As
			break;
		default:
			symbole = '!'; //Non défini
			break;
		}
		cout << symbole;
	}
	//Affichage des couleurs
	switch (get_couleur())
	{
	case 1:
		cout <<"Co"; //Coeur
		break;
	case 2:
		cout << "Ca";//Carreau
		break;
	case 3:
		cout << "Tr"; //Trèfle
		break;
	case 4:
		cout << "Pi"; //Pique
	default:
		cout << "!"; //Non défini
		break;
	}
}
