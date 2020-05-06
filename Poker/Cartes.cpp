#include "Cartes.h"

Cartes::Cartes(int idCarte) {
	idCarte_ = idCarte;
	//Gestion des couleurs
	if (idCarte <= 13) {
		couleur_ = 1;// Coeur
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
	symbole_ = idCarte % 13 + 2;
}