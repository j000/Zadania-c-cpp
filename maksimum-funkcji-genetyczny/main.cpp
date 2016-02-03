#include <iostream>
#include <iomanip>
#include <cmath>

#if __cplusplus >= 201103L
	#include <random>	/* random generators */
#else
	#warning Używamy "kiepskiego" generatora liczb losowych, lepiej korzystać z C++11.
	#include <stdlib.h>	/* srand, rand */
	#include <time.h>	/* time */
#endif

using namespace std;

////////////////////

#define N (20)
#define M (30)
#define a (0.)
#define b (3.)

#define odpowiedz ((1./3.)*(4. - sqrt(7.)))

//w przedziale <a,b> ma być dodatnia
double f(double x) {
	return ((abs(x-1)-1)*abs(x-1)*(x-3)+1);
}

////////////////////

unsigned int n = N;
unsigned int m = M;

////////////////////

double losowa() {

#if __cplusplus >= 201103L
	static std::random_device seed;
	static std::mt19937 gen(seed());
	static std::uniform_real_distribution<float> dist(0.0, 1.0);
	
	return dist(gen);
#else
	return ( ((double)rand()) / RAND_MAX );
#endif

}

void swap(double* x, double* y) {
	double tmp[2];
	tmp[0] = x[0]; tmp[1] = x[1];
	x[0] = y[0]; x[1] = y[1];
	y[0] = tmp[0]; y[1] = tmp[1];
}

// TODO: inne sortowanie, żeby było szybciej
void sortuj(double tablica[][2], unsigned int ilosc) {
	--ilosc; //zeby w petlach nie liczyc -1
	for (int i = 0; i <= ilosc; ++i) {
		for (int k = 0; k < ilosc; ++k) {
			if (tablica[k][1] < tablica[k+1][1])
				swap(tablica[k], tablica[k+1]);
		}
	}
}

void nowe_pokolenie (double tablica[][2]) {
	// wagi i losowanie
	double suma = 0;
	for (int i = 0; i < n; ++i) {
		suma += tablica[i][1];
	}
	
	double nowe[n][2];
	for (int i = 0; i < n; ++i) {
		// nasza "pizza"/"ruletka" czy jak to nazwać
		int k = 0;
		double tmp = losowa() * suma;
		// na który kawałek trafiliśmy?
		while (tmp > tablica[k][1]) {
			tmp -= tablica[k][1];
			++k;
		}
		// bierzemy wartość tego kawałka
		nowe[i][0] = tablica[k][0];
	}
	
	// krzyżujemy (x1, x2, x3) -> ((x1+x2)/2, (x2+x3)/2, (x3+x1)/2)
	double tmp0 = nowe[0][0];
	for (int i = 0; i < n-1; ++i) {
		// średnia arytmetyczna
		nowe[i][0] += nowe[i+1][0];
		nowe[i][0] /= 2;
		// nowa wartość
		nowe[i][1] = f(nowe[i][0]);
	}
	nowe[n-1][0] += tmp0;
	nowe[n-1][0] /= 2;
	nowe[n-1][1] = f(nowe[n-1][0]);
	
	// sortujemy
	sortuj(nowe, n);
	
	// mieszamy z rodzicami
	int i = 0;
	int j = 0;
	double nowe2[n];
	for (int k = 0; k < n; ++k) {
		if (nowe[i][1] > tablica[j][1])
			nowe2[k] = nowe[i++][0];
		else
			nowe2[k] = tablica[j++][0];

		// czy to jest potrzebne?
		while (tablica[j][0] == nowe2[k])
			++j; //nie uzywaj dwa razy takiej samej wartosci
		while (nowe[i][0] == nowe2[k])
			++i; //nie uzywaj dwa razy takiej samej wartosci
	}
	
	// liczymy wartosci dla 90% N
	j = floor(9. * n / 10.);
	for (i = 0; i < j; ++i) {
		tablica[i][0] = nowe2[i];
		tablica[i][1] = f(tablica[i][0]);
	}
	// losujemy 10% nowych
	for (; i < n; ++i) {
		tablica[i][0] = losowa() * (b - a) + a;
		tablica[i][1] = f(tablica[i][0]);
	}
}

int main (int argc, const char* argv[]) {
	cout.setf( std::ios::fixed, std:: ios::floatfield );
	cout.precision(20);
	
#if __cplusplus >= 201103L
	if (argc > 2) {
		n = stol(argv[1]);
		m = stol(argv[2]);
	}
#else
	//TODO:
	//dodać obsługę n i m jako argumentów
	
	//porzebujemy wywołać przy używaniu rand()
	srand((unsigned int)time(NULL));
#endif
	
	double liczby[n][2];
	
	// losujemy liczby
	for (int i = 0; i < n; ++i) {
		liczby[i][0] = losowa() * (b - a) + a;
		liczby[i][1] = f(liczby[i][0]);
	}
	sortuj(liczby, n);
	
	#ifdef DEBUG
	for (int i = 0; i < n; ++i) {
		cout << liczby[i][0] << " -> " << liczby[i][1] << endl;
	}
	#endif
	
	for (int k = 0; k < m; ++k) {
		#ifdef DEBUG
		cout << setw(3) << (k+1) << "/" << m << ":  " << endl;
		#endif
		
		nowe_pokolenie(liczby);
		
		#ifdef DEBUG
		for (int i = 0; i < n; ++i) {
			cout << "    " << liczby[i][0] << " -> " << liczby[i][1] << endl;
		}
		#endif
	}
	
	cout << "Powinno wyjść: " << odpowiedz << " -> " << f(odpowiedz) << endl;
	cout << "Wyliczyliśmy:  " << liczby[0][0] << " -> " << liczby[0][1] << endl;
	return 0;
}
