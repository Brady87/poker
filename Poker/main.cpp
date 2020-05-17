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
		system("cls");
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
	//Flux ecriture-lecture
	ofstream maSauvegarde(monfichier); // Tout le monde peut ecrire dans son fichier
	ifstream maLecture(monfichier); //Ecrire dans son fichier
	ifstream lectAdv(fichieradv); //Lire dans le fichier adverse
	ofstream sauvegardeAdv; // On place le flux sauv adv ici pour éviter la perte de données
	ofstream sauvegardeJeu;
	ifstream lectJeu("jeu.txt");
	Joueur adversaire;
	vous.sauver_joueur(maSauvegarde); // On sauvegarde nos infos
	maLecture.close();
	while (adversaire.get_id() != 1 - rep) { //Tant que le joueur n'a pas choisi l'option adéquate
		lectAdv.open(fichieradv); // On ouvre le fichier de l'adversaire
		adversaire.lire_joueur(lectAdv); //On récupère les infos liées à l'adversaire
		cout << "En attente de votre adversaire ..." << endl;
		system("cls");
		lectAdv.close();
	}
	jeu.set_joueurs(adversaire);
	jeu.set_joueurs(vous); // affectation des joueurs au jeu
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
		sauvegardeAdv.open(fichieradv); // Seul le serveur récolte les données du client
		sauvegardeJeu.open("jeu.txt");
		maSauvegarde.open(monfichier);
		vous.sauver_joueur(maSauvegarde); //on sauvegarde
		adversaire.sauver_joueur(sauvegardeAdv);
		jeu.sauver_jeu(sauvegardeJeu);
		maSauvegarde.close();
		sauvegardeAdv.close();
		sauvegardeJeu.close();
		
	}
	else {//Si client, on récupère les infos venant du serveur
		while (!vous.get_quiParle() && !adversaire.get_quiParle()) {// Tant qu'on ne sait pas qui commence
			 // On ouvre les fichiers
			lectAdv.open(fichieradv);
			maLecture.open(monfichier);
			lectJeu.open("jeu.txt");
			// On actualise les profils
			vous.lire_joueur(maLecture); 
			adversaire.lire_joueur(lectAdv);
			jeu.lire_jeu(lectJeu);
			// On ferme les flux
			lectAdv.close();
			maLecture.close();
			lectJeu.close();
		}
	}

//Début du jeu 
	do {
		do {
			while (!vous.get_quiParle()) {//Ce n'est pas à vous de parler
				system("cls");
				maLecture.open(monfichier); // On ouvre notre fichier
				vous.lire_joueur(maLecture); // On récupère les infos
				maLecture.close();//On ferme notre fichier
				cout << "Votre adversaire joue..." << endl;
			}
			system("cls");
			maLecture.close();//On ferme nos fichiers
			lectAdv.close();
			lectJeu.close();
			maLecture.open(monfichier); // On récupère les infos
			lectAdv.open(fichieradv);
			lectJeu.open("jeu.txt");
			vous.lire_joueur(maLecture); 
			adversaire.lire_joueur(lectAdv);
			jeu.lire_jeu(lectJeu);
			maLecture.close();//On ferme nos fichiers
			lectAdv.close();
			lectJeu.close();
			jeu.affichage(rep); //Affiche les différentes caractéristiques du jeu en cours
			jeu.choix(rep); //Choix du joueur
			vous.set_quiParle(!vous.get_quiParle());//On a fini de parler
			adversaire.set_quiParle(!adversaire.get_quiParle());// On notifie que ça va être au tour de l'adversaire
			maSauvegarde.open(monfichier); // On récupère les infos
			sauvegardeAdv.open(fichieradv);
			sauvegardeJeu.open("jeu.txt");
			vous.sauver_joueur(maSauvegarde); // On met à jour les joueurs dans les fichiers
			adversaire.sauver_joueur(sauvegardeAdv);
			jeu.sauver_jeu(sauvegardeJeu);
			maSauvegarde.close();//On ferme nos fichiers
			sauvegardeAdv.close();
			sauvegardeJeu.close();
		} while (vous.get_choix() != 4 || adversaire.get_choix() != 4||vous.get_mise()!=adversaire.get_mise());// Tant que personne n'est couché et que les mises ne sont pas égales
		jeu.set_tour(jeu.get_tour() + 1);//Tour +1
		vous.set_mise(0);// On remet à zéro les mises
		adversaire.set_mise(0);
		maSauvegarde.open(monfichier); // On récupère les infos
		sauvegardeAdv.open(fichieradv);
		sauvegardeJeu.open("jeu.txt");
		vous.sauver_joueur(maSauvegarde);// On met à jour les joueurs
		adversaire.sauver_joueur(sauvegardeAdv);
		jeu.sauver_jeu(sauvegardeJeu);//On met à jour le jeu
		maSauvegarde.close();//On ferme nos fichiers
		sauvegardeAdv.close();
		sauvegardeJeu.close();
	} while (jeu.get_tour() < 4 || vous.get_choix() != 4 || adversaire.get_choix() != 4); //Tant que personne n'est couché et qu'il reste des tours
}

