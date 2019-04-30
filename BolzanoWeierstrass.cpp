/*REVISAR PER VEURE SI REALMENT ESTA BEN FET (APROXIMACIÓ RAONADA) PER QUE ES MANTÉ CONSTANT*/

#include <iostream>

using namespace std;

void processar(char* e, int l);
bool conte (char* a, char c, int l);
double ele(double b, int e);
void aproximacioSecant(int iteracions, int decimals);
void aproximacioBolzano(int iteracions, int decimals);
double evaluar (double x);

char numeros[] = {'0','1','2','3','4','5','6','7','8','9'};
int coeficients [100];
int exponents [100];
bool termeIndependent = false;
int grau = 0;

int main () {
	int l = 100;
	char expressio [l];
	cin.getline(expressio, l);
	processar (expressio, l);
	cout << "Evaluant una funcio de grau " << grau << endl;
	aproximacioSecant (10, 50);
	aproximacioBolzano (10, 50);
//	for (int i = 0; i<100; i++) {
//		cout << coeficients[i] << " / ";
//	}
//	cout << endl;
//	for (int i = 0; i<100; i++) {
//		cout << exponents[i] << " / ";
//	}
//	cout << endl;
}

void processar (char* e, int l) {
	int ronda=0;
	for (int i=0; i<l; i++) {
//		cout << "Hola " << i << endl;
		bool negative = false;
		int numero = 0;
		int exponent = 0;
		if (e[i] == 'x') {
			int k=1;
			while (conte(numeros, e[i-k], 10)) {
				k++;
			}
//			cout << "valor de k: " << k << endl;
			for (int j=k-1; j>0; j--) {
				numero += (e[i-j]-48)*ele((double)10, j-1);
//				cout << "Dins del metode I" << endl;
			}
//			cout << numero << endl;
//			cout << "Fora del metode I" << endl;
			if (e[i-k] == '-') {
//				cout << "Dins del metode II" << endl;
				negative=true;
			}
//			cout << "Fora del metode II" << endl;
			int m=1;
			while (conte(numeros, e[i+m], 10)) {
//				cout << "Dins del metode III" << endl;
				m++;
			}
//			cout << "Fora del metode III" << endl;
			for (int j=0; j<m-1; j++) {
//				cout << "Dins del metode IIII" << endl;
				exponent += (e[i+j+1]-48)*ele((double)10, m-j-2);
			}
//			cout << "Fora del metode IIII" << endl;
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
	double X1 = (double)1;
	double X2 = (double)-1;
	double Y1 = evaluar(X1);
	double Y2 = evaluar(X2);
	bool perfecte = false;
	double puntTall;
//	cout << "Valors de Y1 i Y2 " << Y1 << " / " << Y2 << endl;
	cout.precision(decimals);
	while (!((Y2 < 0 && Y1 > 0) || (Y2 > 0 && Y1 < 0))) {
//		cout << "Acces" << endl;
		X1 += 1;
		X2 -= 1;
		Y1 = evaluar (X1);
		Y2 = evaluar (X2);
	}
	for(int i = 0; i<iteracions; i++) {
		Y1 = evaluar(X1);
		Y2 = evaluar(X2);
		double pendent = (Y2-Y1)/(X2-X1);
		double ordenada = Y1-pendent*X1;
		puntTall = (ordenada/pendent)*-1;
		
//		cout << "Valor compres entre " << fixed << X1 << " i " << X2 << endl;
//		cout << "Valor aproximat: " << puntTall << endl;
//		cout << "Evaluacio amb valor " << fixed << evaluar(puntTall) << endl;
		if (evaluar (puntTall) > 0) {
			X1 = puntTall;
		}
		if (evaluar (puntTall < 0)) {
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
}

void aproximacioBolzano (int iteracions, int decimals) {
	cout << "\nMetode Bolzano-Weierstrass" << endl;
	cout << "--------------------------" << endl;
	cout << "Nombre de iteracions: " << iteracions << endl;
	double X1 = (double)1;
	double X2 = (double)-1;
	double Y1 = evaluar(X1);
	double Y2 = evaluar(X2);
	cout.precision(decimals);
	bool perfecte = false;
	double puntTall;
	while(!((Y2>0 && Y1<0) || (Y2<0 && Y1>0))) {
		X1 += 1;
		X2 -= -1;
		Y1 = evaluar (X1);
		Y2 = evaluar(X2);
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
}

double evaluar (double x) {
	double resultat = (double)0;
	for (int i = 0; i<=grau; i++) {
		resultat += (double)coeficients[i]*(ele(x, exponents[i]));
	}
	return resultat;
}
