#include <iostream>
#include <math.h>
using namespace std;

int main() {
	//Affichage de "Hello World"
	cout << "Hello World !"<<endl;
	double p = 1 / 512;
	double s = 0;
	int nbre = 0;
	cout << "Saisir le nombre de répétition" << endl;
	cin >> nbre;
	for (int i = 0; i < nbre; i++) {
		s = pow((511 / 512), i);
	}
	cout << "Probabilite chromatique apres " << nbre << " repetitions : " << s << "." << endl;
	return 0;
}