#include <iostream>
#include"Cartes.h"
#include"Jeu.h"
#include"Joueur.h"
#include<time.h>
using namespace std;



void main() {
	int recomm = 1;
	do { //Début du jeu 
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

		cout << "------------------------Bienvenue a PokerTSE------------------------" << endl; //Message de bienvenue
		string pseudo;
		int rep = -1;
		int manche = 1;
		int phase = 1;
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
			if (rep != 0 && rep != 1) {
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
			int aleat = rand() % 2; //Choisi un nombre entre 0 et 1
			if (aleat == 1) {
				cout << "Le serveur distribue." << endl;
				vous.set_distributeur(true);
				adversaire.set_distributeur(false);
				vous.set_quiParle(false);//Vous ne jouez pas en 1er
				adversaire.set_quiParle(true);
			}
			else {
				cout << "Le client distribue." << endl;
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
		do {//Nouvelle partie
			do {//Nouvelle manche
				do {//Nouveau tour
					// On récupère les infos une première fois
					maLecture.close();//On ferme nos fichiers
					lectAdv.close();
					lectJeu.close();
					// On ouvre les fichiers
					lectJeu.open("jeu.txt");
					lectAdv.open(fichieradv);
					maLecture.open(monfichier);
					// On actualise les profils
					vous.lire_joueur(maLecture);
					adversaire.lire_joueur(lectAdv);
					jeu.lire_jeu(lectJeu);
					// On referme les flux
					lectAdv.close();
					maLecture.close();
					lectJeu.close();
					while (manche != jeu.get_manche()) {// Permet synchro au fichier jeu.txt
						cout << "En attente du serveur ..." << endl;
						maLecture.close();//On ferme nos fichiers
						lectAdv.close();
						lectJeu.close();
						// On ouvre les fichiers
						lectJeu.open("jeu.txt");
						lectAdv.open(fichieradv);
						maLecture.open(monfichier);
						// On actualise les profils
						vous.lire_joueur(maLecture);
						adversaire.lire_joueur(lectAdv);
						jeu.lire_jeu(lectJeu);
						// On referme les flux
						lectAdv.close();
						maLecture.close();
						lectJeu.close();
						system("cls");
					}
					while (!vous.get_quiParle()) {//Ce n'est pas à vous de parler
						cout << "Votre adversaire joue..." << endl;
						maLecture.close();//On ferme notre fichier
						maLecture.open(monfichier); // On ouvre notre fichier
						vous.lire_joueur(maLecture); // On récupère les infos
						maLecture.close();//On ferme notre fichier
						system("cls");
					}
					system("cls");
					maLecture.close();//On ferme les flux
					lectAdv.close();
					lectJeu.close();
					maLecture.open(monfichier); //On ouvre les flux
					lectAdv.open(fichieradv);
					lectJeu.open("jeu.txt");
					vous.lire_joueur(maLecture); // On récupère les infos
					adversaire.lire_joueur(lectAdv);
					jeu.lire_jeu(lectJeu);
					maLecture.close();//On ferme les flux
					lectAdv.close();
					lectJeu.close();
					if (jeu.get_tour() < 5) {
						jeu.affichage(rep); //Affiche les différentes caractéristiques du jeu en cours
						if (adversaire.get_choix() == 3 || (adversaire.get_choix() == 1 && vous.get_choix() == 1)) {// Si l'adversaire suit ou que les deux checkent
						//GERER MISES EGALES
						//On ne propose pas de choix
						}
						else if (adversaire.get_choix() == 4) {// Si l'adversaire se couche
							vous.set_jetons(vous.get_jetons() + jeu.get_pot());
							cout << "Vous remportez " << jeu.get_pot() << endl;
							cout << "Appuyer sur une touche pour continuer" << endl;
							system("pause");
						}
						else {
							jeu.choix(rep); //Choix du joueur
							vous.set_quiParle(!vous.get_quiParle());//On a fini de parler
							if (jeu.get_tour() < 5) {
								adversaire.set_quiParle(!adversaire.get_quiParle());// On notifie que ça va être au tour de l'adversaire si ce n'est pas la fin
							}
						}
						maSauvegarde.close();//On ferme nos fichiers
						sauvegardeAdv.close();
						sauvegardeJeu.close();
						maSauvegarde.open(monfichier); // On récupère les flux
						sauvegardeAdv.open(fichieradv);
						sauvegardeJeu.open("jeu.txt");
						vous.sauver_joueur(maSauvegarde); // On met à jour les joueurs dans les fichiers
						adversaire.sauver_joueur(sauvegardeAdv);
						jeu.sauver_jeu(sauvegardeJeu);
						maSauvegarde.close();//On ferme nos fichiers
						sauvegardeAdv.close();
						sauvegardeJeu.close();
					}
				} while ((vous.get_choix() != 4 && adversaire.get_choix() != 4) && (vous.get_mise() != adversaire.get_mise() || (vous.get_choix() != 1 || adversaire.get_choix() != 1)) && (vous.get_choix() != 1 || adversaire.get_choix() != 1));// Tant que personne n'est couché et que les mises ne sont pas égales
					jeu.set_tour(jeu.get_tour() + 1);//Tour +1
					vous.set_mise(0);// On remet à zéro les mises
					adversaire.set_mise(0);
					if (vous.get_choix() != 4 && adversaire.get_choix() != 4) {// Si personne ne s'est couche
						vous.set_choix(0); //RàZ des choix
						adversaire.set_choix(0);
					}
					maSauvegarde.close();//On ferme nos fichiers
					sauvegardeAdv.close();
					sauvegardeJeu.close();
					maSauvegarde.open(monfichier); // On récupère les flux
					sauvegardeAdv.open(fichieradv);
					sauvegardeJeu.open("jeu.txt");
					vous.sauver_joueur(maSauvegarde);// On met à jour les joueurs
					adversaire.sauver_joueur(sauvegardeAdv);
					jeu.sauver_jeu(sauvegardeJeu);//On met à jour le jeu
					maSauvegarde.close();//On ferme nos fichiers
					sauvegardeAdv.close();
					sauvegardeJeu.close();
			} while (jeu.get_tour() < 5 && vous.get_choix() != 4 && adversaire.get_choix() != 4); //Tant que personne n'est couché et qu'il reste des tours
			if (jeu.get_tour() >= 5) { // Si on est dans le dernier tour
				if (vous.get_choix() != 4 && adversaire.get_choix() != 4) {// Si les deux joueurs jouent encore
					system("cls");
					jeu.afficher_cartes_tables();
					cout << endl;
					cout << "Vous : "; //On affiche le nom des mains des joueurs
					vous.afficher_cartes_joueur();
					cout << endl;
					jeu.nomCombinaison(rep);
					cout << endl;
					cout << "Votre adversaire : ";
					adversaire.afficher_cartes_joueur();
					cout << endl;
					jeu.nomCombinaison(1 - rep);
					cout << endl;
					if (jeu.gagnant() == rep) { //Calcul du gagnant et récompense
						cout << "Vous gagnez " << jeu.get_pot() << endl;
						vous.set_jetons(vous.get_jetons() + jeu.get_pot());
					}
					else if (jeu.gagnant() == 1 - rep) {
						cout << "Votre adversaire gagne" << jeu.get_pot() << endl;
						adversaire.set_jetons(adversaire.get_jetons() + jeu.get_pot());
					}
					else {
						cout << "Egalite" << endl;
						vous.set_jetons(vous.get_jetons() + (jeu.get_pot() / 2));
						adversaire.set_jetons(adversaire.get_jetons() + jeu.get_pot() / 2);
					}
				}
				else if (vous.get_choix() == 4) {
					adversaire.set_jetons(adversaire.get_jetons() + jeu.get_pot());
					cout << "L'adversaire remporte le pot" << endl;
				}
				else {
					vous.set_jetons(vous.get_jetons() + jeu.get_pot());
					cout << "Vous remportez le pot" << endl;
				}
				system("pause");
			}

			if (rep == 1) { // Seul le serveur effectue les modifs et la sauvegarde
				jeu.set_manche(jeu.get_manche() + 1); // Nouvelle manche
				jeu.set_tour(1); // On repart au premier tour
				vous.set_distributeur(!vous.get_distributeur());// On change de distributeur
				adversaire.set_distributeur(!adversaire.get_distributeur());
				vous.set_quiParle(!vous.get_distributeur()); //Si on ne distribue pas on parle en premier
				adversaire.set_quiParle(!adversaire.get_distributeur());
				jeu.nouvelle_donne();//On RàZ la pioche
				vous.set_choix(0); //RàZ les choix
				adversaire.set_choix(0);
				//Mélange et distribution des cartes
				jeu.melangerCartes();
				vous.set_main(jeu.distribuerCartes(2));
				adversaire.set_main(jeu.distribuerCartes(2));
				jeu.set_cartesTable(jeu.distribuerCartes(5));
				maSauvegarde.open(monfichier); // On récupère les flux
				sauvegardeAdv.open(fichieradv);
				sauvegardeJeu.open("jeu.txt");
				vous.sauver_joueur(maSauvegarde);// On met à jour les joueurs
				adversaire.sauver_joueur(sauvegardeAdv);
				jeu.sauver_jeu(sauvegardeJeu);//On met à jour le jeu
				maSauvegarde.close();//On ferme nos fichiers
				sauvegardeAdv.close();
				sauvegardeJeu.close();
			}
			manche++;
		}while (vous.get_jetons() > 0 && adversaire.get_jetons() > 0); // Tant que personne n'a plus de jetons
		if (vous.get_jetons() > 0) {
			cout << "Félicitations vous avez gagne !" << endl;
		}
		else {
			cout << "Votre adversaire l'emporte." << endl;
		}
		do {
			cout << "Recommencez une partie ?" << endl;
			cout << "1- Oui" << endl;
			cout << "2- Non" << endl;
			cin >> recomm;
			if (recomm != 1 && recomm != 2) {
				system("cls");
				cout << "Choix errone, veuillez ressayer." << endl;
			}
		} while (recomm != 1 && recomm != 2);
	} while (recomm == 1);
}