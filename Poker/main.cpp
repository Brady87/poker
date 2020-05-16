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
	} while (rep != 0 && rep != 1);
	vous.set_id(rep); // Client ou serveur
	string monfichier, fichieradv;
	if (rep == 0) //On définit dans quel fichier on va lire/écrire
	{
		monfichier = "client.txt";
		fichieradv = "serveur.txt";
	}
	else {
		monfichier = "serveur.txt";
		fichieradv = "client.txt";
	}
	ofstream maSauvegarde(monfichier);
	ifstream lectAdv(fichieradv);
	ifstream maLecture(monfichier);
	ofstream sauvegardeJeu("jeu.txt");
	ifstream lectJeu("jeu.txt");
	Joueur adversaire;
	vous.sauver_joueur(maSauvegarde); // On stocke nos infos
	while (adversaire.get_id() != 1-rep) { //Tant que le joueur n'a pas choisi l'option adéquate
		adversaire.lire_joueur(lectAdv); //On récupère les infos liées à l'adversaire
		vous.sauver_joueur(maSauvegarde); // On stocke nos infos
		cout << "En attente de votre adversaire ..." << endl;
	}
	ofstream sauvegardeAdv(fichieradv); // On place le flux sauv adv ici pour éviter la perte de données
	jeu.set_joueurs(vous); // affectation des joueurs au jeu
	jeu.set_joueurs(adversaire);
	if (rep == 1) {// Si serveur on fait les tirages 
		srand(time(NULL)); // Initialisation de rand
		int aleat = rand() % 2;
		if (aleat == vous.get_id()) {
			cout << "Vous etes le distributeur." << endl;
			vous.set_distributeur(true);
			adversaire.set_distributeur(false);
			vous.set_quiParle(false);//Vous ne jouez pas en 1er
			adversaire.set_quiParle(true);
		}
		else {
			cout << "Votre adversaire distribue les cartes." << endl;
			vous.set_distributeur(false);
			adversaire.set_distributeur(true);
			vous.set_quiParle(true);//Vous jouez en premier
			adversaire.set_quiParle(false);
		}
		//Mélange et distribution des cartes

		jeu.melangerCartes(); 
		vous.set_main(jeu.distribuerCartes(2));
		adversaire.set_main(jeu.distribuerCartes(2));
		jeu.set_cartesTable(jeu.distribuerCartes(5));
		//On sauvegarde une nouvelle fois les joueurs et le jeu
		vous.sauver_joueur(maSauvegarde);
		adversaire.sauver_joueur(sauvegardeAdv);
		jeu.sauver_jeu(sauvegardeJeu);
	}
	else {//On récupère les infos venant du serveur
		while(!vous.get_quiParle() && !adversaire.get_quiParle())// Tant qu'on ne sait pas qui commence
		vous.lire_joueur(maLecture); //On actualise les profils
		adversaire.lire_joueur(lectAdv);
	}
	do {
		while (!vous.get_quiParle()) {//Ce n'est pas à vous de parler
			vous.lire_joueur(maLecture); // On récupère les infos
			adversaire.lire_joueur(lectAdv);
			jeu.lire_jeu(lectJeu);
		}
		do {
			jeu.affichage(rep); //Affiche les différentes caractéristique du jeu en cours
			jeu.choix(rep); //Choix du joueur
			vous.set_quiParle(!vous.get_quiParle());//On a fini de parler
			adversaire.set_quiParle(!adversaire.get_quiParle());// On notifie que ça va être au tour de l'adversaire
		} while (vous.get_choix() != 4 && adversaire.get_choix() != 4);// Tant que personne n'est couché
		jeu.set_tour(jeu.get_tour() + 1);
		vous.sauver_joueur(maSauvegarde);// On met à jour les joueurs
		adversaire.sauver_joueur(sauvegardeAdv);
		jeu.sauver_jeu(sauvegardeJeu);//On met à jour le jeu
	} while (jeu.get_tour() < 4 && vous.get_choix() != 4 && adversaire.get_choix() != 4); //Tant que personne n'est couché et qu'il reste des tours
}

