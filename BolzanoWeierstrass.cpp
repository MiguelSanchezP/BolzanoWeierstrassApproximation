/*REVISAR PER VEURE SI REALMENT ESTA BEN FET (APROXIMACIÓ RAONADA) PER QUE ES MANTÉ CONSTANT*/

#include <iostream>

using namespace std;

void processar(char* e, int l);
bool conte (char* a, char c, int l);
double ele(double b, int e);
void aproximacioSecant(int iteracions, int decimals);
void aproximacioBolzano(int iteracions, int decimals);
double evaluar (double x);
void menu ();

char numeros[] = {'0','1','2','3','4','5','6','7','8','9'};
int coeficients [100];
int exponents [100];
bool termeIndependent = false;
int grau = 0;
double valSecant = 1;
double valBolzano = 1;

int main () {
	int l = 100;
	char expressio [l];
	int decisio;
	int iteracions;
	int precisioDecimals;
	bool sortir = false;
	while (!sortir) {
		cout << "Introduir l'expressio: ";
		cin.getline(expressio, l);
		processar (expressio, l);
		menu();
		cin >> decisio;
		cout << "Numero de iteracions: ";
		cin >> iteracions;
		cout << "Quantitat de decimals: ";
		cin >> precisioDecimals;
		cin.ignore();
		cout << "\nEvaluant una funcio de grau " << grau << endl;
		switch (decisio) {
			case 1:
				aproximacioBolzano(iteracions, precisioDecimals);
				break;
			case 2:
				aproximacioSecant(iteracions, precisioDecimals);
				break;
			case 3:
				aproximacioBolzano(iteracions, precisioDecimals);
				aproximacioSecant(iteracions, precisioDecimals);
				cout << "La aproximacio de la secant ha estat " << valBolzano/valSecant << " vegades mes eficient" << endl;
				break;
			case 0:
				sortir = true;
				break;
		}
		cout << "\n\n";
	}
	return 0;
}

void processar (char* e, int l) {
	int ronda=0;
	for (int i=0; i<l; i++) {
		bool negative = false;
		int numero = 0;
		int exponent = 0;
		if (e[i] == 'x') {
			int k=1;
			while (conte(numeros, e[i-k], 10)) {
				k++;
			}
			for (int j=k-1; j>0; j--) {
				numero += (e[i-j]-48)*ele((double)10, j-1);
			}
			if (e[i-k] == '-') {
				negative=true;
			}
			int m=1;
			while (conte(numeros, e[i+m], 10)) {
				m++;
			}
			for (int j=0; j<m-1; j++) {
				exponent += (e[i+j+1]-48)*ele((double)10, m-j-2);
			}
			if (negative) {
			numero = numero*-1;
		}
		coeficients[ronda] = numero;
		exponents [ronda] = exponent;
		if (exponent == 0) {
			termeIndependent=true;
		}
		if (exponent >= grau) {
			grau = exponent;
		}
		ronda += 1;
		}
	}
}

bool conte (char* a, char c, int l) {
	for (int i = 0; i<l; i++) {
		if (a[i] == c) {
			return true;
		}
	}
	return false;
}

double ele (double b, int e) {
	double resultat = (double)1;
	for (int i = 0; i<e; i++) {
		resultat*=b;
	}
	return resultat;
}

void aproximacioSecant (int iteracions, int decimals) {
	cout << "\nMetode de la secant" << endl;
	cout << "-------------------" << endl;
	cout << "Nombre de iteracions: " << iteracions << endl;
	double X1 = (double)0.1;
	double X2 = (double)-0.1;
	double Y1 = evaluar(X1);
	double Y2 = evaluar(X2);
	bool perfecte = false;
	double puntTall;
	cout.precision(decimals);
	bool parell = true;
	while (!((Y2 < 0 && Y1 > 0) || (Y2 > 0 && Y1 < 0))) {
		if (parell) {
			X1 += 0.1;
			Y1 = evaluar(X1);
			parell = false;
		}else{
			X2 -= 0.1;
			Y2 = evaluar(X2);
			parell = true;
		}
	}
	for(int i = 0; i<iteracions; i++) {
		Y1 = evaluar(X1);
		Y2 = evaluar(X2);
		double pendent = (Y2-Y1)/(X2-X1);
		double ordenada = Y1-pendent*X1;
		puntTall = (ordenada/pendent)*-1;
		
		if (evaluar (puntTall) > 0) {
			X1 = puntTall;
		}
		if (evaluar (puntTall) < 0) {
			X2 = puntTall;
		}
		if (evaluar(puntTall) == 0) {
			perfecte = true;
		}
	}
	if (perfecte) {
		cout << "La solucio es: " << fixed << puntTall << endl;
	}else{
		cout << "S. Evaluacio amb valor: " << fixed << puntTall << endl;
		cout << "S. Hi ha present un error de: " << fixed << evaluar(puntTall) << endl;
	}
	valSecant = evaluar(puntTall);
}

void aproximacioBolzano (int iteracions, int decimals) {
	cout << "\nMetode Bolzano-Weierstrass" << endl;
	cout << "--------------------------" << endl;
	cout << "Nombre de iteracions: " << iteracions << endl;
	double X1 = (double)0.1;
	double X2 = (double)-0.1;
	double Y1 = evaluar(X1);
	double Y2 = evaluar(X2);
	cout.precision(decimals);
	bool perfecte = false;
	double puntTall;
	bool parell = true;
	while(!((Y2>0 && Y1<0) || (Y2<0 && Y1>0))) {
		if (parell) {
			X1 += 0.1;
			Y1 = evaluar(X1);
			parell = false;	
		}else{
			X2 -= 0.1;
			Y2 = evaluar(X2);
			parell = true;
		}
	}
	for (int i = 0; i<iteracions; i++) {
		puntTall = (double)(X2+X1)/2;
		if (evaluar(puntTall) > 0) {
			X1 = puntTall;
		}
		if (evaluar(puntTall) < 0) {
			X2 = puntTall;
		}
		if (evaluar(puntTall) == 0) {
			perfecte = true;
		} 
	}
	if (perfecte) {
		cout << "BW. La solucio es: " << fixed << puntTall << endl;
	}else{
		cout << "BW. Evaluacio amb valor: " << fixed << puntTall << endl;
		cout << "BW. Hi ha present un error de: " << fixed << evaluar(puntTall) << endl;
	}
	valBolzano = evaluar(puntTall);
}

double evaluar (double x) {
	double resultat = (double)0;
	for (int i = 0; i<=grau; i++) {
		resultat += (double)coeficients[i]*(ele(x, exponents[i]));
	}
	return resultat;
}

void menu () {
	cout << "Decisio: " << endl;
	cout << "1. Aproximacio amb metode Bolzano-Weierstrass" << endl;
	cout << "2. Aproximacio amb metode de la secant" << endl;
	cout << "3. Comparacio entre els dos metodes" << endl;
	cout << "0. Sortir" << endl;
	cout << "Opcio: ";
}
