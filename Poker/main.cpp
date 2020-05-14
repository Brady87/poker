#include <iostream>
#include"Cartes.h"
#include"Jeu.h"
#include"Joueur.h"
#include<time.h>

using namespace std;



void main() {
	cout << "                                                                   " << endl;
    cout << "                                                                   " << endl;
    cout << "                                                                   " << endl;
    cout << "     .:XHHHHk.              db.   .;;.     .:XHHHHk.               " << endl;
    cout << "   oMMMMMMMMMMM       ~MM  dMMP :MMMMMR  oMMMMMMMMMMM              " << endl;
    cout << "   QMMMMMb  \"MMX       MMMMMMP !MX' :M~ QMMMMMb  \"MMX            " << endl;
    cout << "     `MMMM.  )M> :X!Hk. MMMM   XMM.o\"  . `MMMM.  )M>              " << endl;
    cout << "      'MMMb.dM! XM M'?M MMMMMX.`MMMMMMMM~  'MMMb.dM!               " << endl;
    cout << "       ~MMMMM~ XMM. .XM XM`\"MMMb.~*?**~ .   ~MMM~\"MMb            " << endl;
    cout << "        ?MMM>  YMMMMMM! MM   `?MMRb.         ?MMM>  `?MRb.         " << endl;
    cout << "         MMMX   \"MMMM\"  MM       ~%:          MMMX   `?MRb.      " << endl;
    cout << "         'MMM.                                 'MMM.    `?MRb.     " << endl;
    cout << "          ~M!M                                  ~M!M         ~%:   " << endl << endl;

	cout << "------------------------Bienvenue a PokerTSE------------------------"<<endl; //Message de bienvenue
	string pseudo;
	int rep = -1;
	Jeu jeu; //Initialisation du jeu
	Joueur vous; //Création de votre profil
	cout << "Saisir un pseudo : " << endl;
	cin >> pseudo;
	vous.set_pseudo(pseudo); //Affectattion du pseudo
	do {
		cout << "Bienvenue " << pseudo << ". Veuillez choisir votre role: Client ou Serveur" << endl;
		cout << "0 - Client" << endl << "1 - Serveur" << endl;
		cin >> rep;
		if (rep != 0 && rep != 1 ) {
			cout << "Erreur de saisie !" << endl;
		}
	} while (rep != 0 || rep != 1);
	vous.set_id(rep);
	//CONNEXION A L'AUTRE JOUEUR A COMPLETER
	Joueur adversaire(1-rep,"Inconnu");//INFO A RECUPERER
	srand(time(NULL)); // Initialisation de rand
	int aleat = rand() % 2;
	if (aleat == vous.get_id()) {
		cout << "Vous etes le distributeur." << endl;
		vous.set_distributeur = true;
		adversaire.set_distributeur = false;
	}
	else {
		cout << "Votre adversaire distribue les cartes." << endl;
		vous.set_distributeur = false;
		adversaire.set_distributeur = true;
	}
	//Distribution des cartes
	vous.set_main(jeu.distribuerCartes(2));
	adversaire.set_main(jeu.distribuerCartes(2));
	jeu.set_cartesTable(jeu.distribuerCartes(5));
	do {
		cout << "Manche " << jeu.get_manche() << endl;
		cout << "Tour " << jeu.get_tour() << endl;
		cout << "------------------------------" << endl;
		cout << "Vous : ";
		vous.affciher_jetons();
		cout << "Adversaire : ";
		adversaire.affciher_jetons();
		cout << "Pot : " << jeu.get_pot << " jetons." << endl;
		cout << "Votre main : ";
		vous.afficher_cartes_joueur();
		cout << "Sur la table : ";
		jeu.afficher_cartes_tables();
		cout << "------------------------------" << endl;
		if()
	} while (jeu.get_tour < 4);
}

