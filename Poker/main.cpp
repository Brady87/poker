#include <iostream>
#include"Cartes.h"
#include"Jeu.h"
#include"Joueur.h"
#include<time.h>
using namespace std;



int main() {
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
	Joueur vous; //Cr�ation de votre profil
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
	if (rep == 0) //On d�finit dans quel fichier on va lire/�crire
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
	ofstream sauvegardeAdv; // On place le flux sauv adv ici pour �viter la perte de donn�es
	ofstream sauvegardeJeu;
	ifstream lectJeu("jeu.txt");
	Joueur adversaire;
	vous.sauver_joueur(maSauvegarde,monfichier); // On sauvegarde nos infos
	//maLecture.close();
	while (adversaire.get_id() != 1 - rep) { //Tant que le joueur n'a pas choisi l'option ad�quate
		//ectAdv.open(fichieradv); // On ouvre le fichier de l'adversaire
		adversaire.lire_joueur(lectAdv,fichieradv); //On r�cup�re les infos li�es � l'adversaire
		cout << "En attente de votre adversaire ..." << endl;
		system("cls");
		//lectAdv.close();
	}
	jeu.set_joueurs(adversaire);
	jeu.set_joueurs(vous); // affectation des joueurs au jeu
	if (rep == 1) {// Si serveur on fait les tirages 
		srand(time(NULL)); // Initialisation de rand
		int aleat = rand() % 2; //Choisi un nombre entre 0 et 1
		if (aleat == 1) {
			//Le serveur distribue
			vous.set_distributeur(true);
			adversaire.set_distributeur(false);
			vous.set_quiParle(false);//Vous ne jouez pas en 1er
			adversaire.set_quiParle(true);
		}
		else {
			// Le client distribue
			vous.set_distributeur(false);
			adversaire.set_distributeur(true);
			vous.set_quiParle(true);//Vous jouez en premier
			adversaire.set_quiParle(false);
		}
		//M�lange et distribution des cartes
		jeu.melangerCartes();
		vous.set_main(jeu.distribuerCartes(2));
		adversaire.set_main(jeu.distribuerCartes(2));
		jeu.set_cartesTable(jeu.distribuerCartes(5));
		//On sauvegarde une nouvelle fois les joueurs et le jeu, seul le serveur r�colte les donn�es du client
		vous.sauver_joueur(maSauvegarde,monfichier); //on sauvegarde
		adversaire.sauver_joueur(sauvegardeAdv,fichieradv);
		jeu.sauver_jeu(sauvegardeJeu,"jeu.txt");

	}
	else {//Si client, on r�cup�re les infos venant du serveur
		while (!vous.get_quiParle() && !adversaire.get_quiParle()) {// Tant qu'on ne sait pas qui commence
			//Sauvegarde 
			vous.lire_joueur(maLecture,monfichier);
			adversaire.lire_joueur(lectAdv,fichieradv);
			jeu.lire_jeu(lectJeu,"jeu.txt");
		}
	}
	do {//Nouvelle partie
		do {//Nouvelle manche
			int petiteMise = 10;
			int grandeMise = 20;
			do {//Nouveau tour
				// On actualise les profils
				vous.lire_joueur(maLecture,monfichier);
				adversaire.lire_joueur(lectAdv,fichieradv);
				jeu.lire_jeu(lectJeu,"jeu.txt");
				while (manche != jeu.get_manche()) {// Permet synchro au fichier jeu.txt
					cout << "En attente du serveur ..." << endl;
					//On actualise les profils
					vous.lire_joueur(maLecture,monfichier);
					adversaire.lire_joueur(lectAdv,fichieradv);
					jeu.lire_jeu(lectJeu,"jeu.txt");
					system("cls");
				}
				while (!vous.get_quiParle()) {//Ce n'est pas � vous de parler
					jeu.affichage(rep);
					cout << "Votre adversaire joue..." << endl;
					vous.lire_joueur(maLecture,monfichier); // On r�cup�re les infos
					system("cls");
				}
				system("cls");
				vous.lire_joueur(maLecture,monfichier); // On r�cup�re les infos
				adversaire.lire_joueur(lectAdv,fichieradv);
				jeu.lire_jeu(lectJeu,"jeu.txt");
				if (jeu.get_tour() < 5) {
					if (jeu.get_tour() == 1 && !vous.get_distributeur()) {//Mise de d�part g�r� par le premier a parle
						vous.set_mise(petiteMise);
						vous.set_jetons(vous.get_jetons() - petiteMise);
						adversaire.set_jetons(adversaire.get_jetons() - grandeMise);
						adversaire.set_mise(grandeMise);
						jeu.set_pot(petiteMise + grandeMise);

					}
					jeu.affichage(rep); //Affiche les diff�rentes caract�ristiques du jeu en cours
					if (adversaire.get_choix() == 4 || adversaire.get_choix() == 3 || (adversaire.get_choix() == 1 && vous.get_choix() == 1) || vous.get_jetons()==0 || adversaire.get_jetons()==0) {// Si l'adversaire suit ou que les deux checkent
					//On ne propose pas de choix
					}
					else {
						jeu.choix(rep); //Choix du joueur
						vous.set_quiParle(!vous.get_quiParle());//On a fini de parler
						if (jeu.get_tour() < 5) {
							adversaire.set_quiParle(!adversaire.get_quiParle());// On notifie que �a va �tre au tour de l'adversaire si ce n'est pas la fin
						}
					}
					vous.sauver_joueur(maSauvegarde,monfichier); // On met � jour les joueurs dans les fichiers
					adversaire.sauver_joueur(sauvegardeAdv,fichieradv);
					jeu.sauver_jeu(sauvegardeJeu,"jeu.txt");
				}
			} while (!((vous.get_choix() == 1 && adversaire.get_choix() == 1) || (vous.get_mise() == adversaire.get_mise() && (vous.get_choix() != 1 && adversaire.get_mise() != 1) || vous.get_choix() == 4 || adversaire.get_choix() == 4)));// Tant que personne n'est couch� et que les mises ne sont pas �gales
			jeu.set_tour(jeu.get_tour() + 1);//Tour +1
				vous.set_mise(0);// On remet � z�ro les mises
				adversaire.set_mise(0);
				if (vous.get_choix() != 4 && adversaire.get_choix() != 4) {// Si personne ne s'est couche
					vous.set_choix(0); //R�Z des choix
					adversaire.set_choix(0);
				}
				vous.set_quiParle(!vous.get_distributeur()); // On red�finit qui parle en premier
				adversaire.set_quiParle(!adversaire.get_distributeur());
				vous.sauver_joueur(maSauvegarde,monfichier);// On met � jour les joueurs
				adversaire.sauver_joueur(sauvegardeAdv,fichieradv);
				jeu.sauver_jeu(sauvegardeJeu,"jeu.txt");//On met � jour le jeu
		} while (!(jeu.get_tour() >= 5 || vous.get_choix() == 4 || adversaire.get_choix() == 4||vous.get_jetons()==0||adversaire.get_jetons()==0)); //Tant que personne n'est couch�, a sec, et qu'il reste des tours
		if (vous.get_choix() != 4 && adversaire.get_choix() != 4) {// Si les deux joueurs jouent encore
			system("cls");
			jeu.set_tour(5); //Pour afficher toutes les cartes
			jeu.afficher_cartes_tables();
			cout << endl<<endl;
			cout << "Vous : "; //On affiche le nom des mains des joueurs
			vous.afficher_cartes_joueur();
			jeu.nomCombinaison(rep);
			cout << endl;
			cout << "Votre adversaire : ";
			adversaire.afficher_cartes_joueur();
			jeu.nomCombinaison(1 - rep);
			cout << endl;
			if (jeu.gagnant() == rep) { //Calcul du gagnant et r�compense
				cout << "Vous gagnez " << jeu.get_pot() << endl;
				vous.set_jetons(vous.get_jetons() + jeu.get_pot());
			}
			else if (jeu.gagnant() == 1 - rep) {
				cout << "Votre adversaire gagne " << jeu.get_pot() << endl;
				adversaire.set_jetons(adversaire.get_jetons() + jeu.get_pot());
			}
			else {
				cout << "Egalite" << endl;
				vous.set_jetons(vous.get_jetons() + (jeu.get_pot() / 2));
				adversaire.set_jetons(adversaire.get_jetons() + jeu.get_pot() / 2);
			}
		}
		else if (vous.get_choix() == 4) { //Si vous vous couchez
			adversaire.set_jetons(adversaire.get_jetons() + jeu.get_pot());
			cout << "L'adversaire remporte le pot" << endl;
		}
		else {// Si votre adversaire se couche
			vous.set_jetons(vous.get_jetons() + jeu.get_pot());
			cout << "Vous remportez le pot" << endl;
		}
		system("pause");
		if (rep == 1) { // Seul le serveur effectue les modifs et la sauvegarde
			jeu.set_pot(0); // Pot remis � z�ro
			jeu.set_manche(jeu.get_manche() + 1); // Nouvelle manche
			jeu.set_tour(1); // On repart au premier tour
			vous.set_distributeur(!vous.get_distributeur());// On change de distributeur
			adversaire.set_distributeur(!adversaire.get_distributeur());
			vous.set_quiParle(!vous.get_distributeur()); //Si on ne distribue pas on parle en premier
			adversaire.set_quiParle(!adversaire.get_distributeur());
			jeu.nouvelle_donne();//On R�Z la pioche
			vous.set_choix(0); //R�Z les choix
			adversaire.set_choix(0);
			//M�lange et distribution des cartes
			jeu.melangerCartes();
			vous.set_main(jeu.distribuerCartes(2));
			adversaire.set_main(jeu.distribuerCartes(2));
			jeu.set_cartesTable(jeu.distribuerCartes(5));
			vous.sauver_joueur(maSauvegarde,monfichier);// On met � jour les joueurs
			adversaire.sauver_joueur(sauvegardeAdv,fichieradv);
			jeu.sauver_jeu(sauvegardeJeu,"jeu.txt");//On met � jour le jeu
		}
		manche++;
	}while (vous.get_jetons() > 0 && adversaire.get_jetons() > 0); // Tant que personne n'a plus de jetons
	if (vous.get_jetons() > 0) {
		cout << "Felicitations vous avez gagne !" << endl;
	}
	else {
		cout << "Votre adversaire l'emporte." << endl;
	}
	system("pause");
	return 0;
}