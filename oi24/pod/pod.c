#include <stdio.h>
#include <stdlib.h>

//#define DEBUG
//#undef DEBUG

// napisz poprawne wypisywanie rozwiązania i usuń poniższą linię :)
#define HUMAN

// cechy podzielności przez 9:
// (w naszym przypadku podzielność przez B-1, dla B=10 => B-1=9)
// suma cyfr jest liczbą podzielną przez 9 (B-1)

// najwieksza liczba:
// mająca najwięcej cyfr, największe na najbardziej znaczących pozycjach

#define NIE_TEDY_DROGA 0
#define ROZWIAZANIE 1

// ten sposob szuka liczb "w głąb"
// tzn. woli sześć jedynek niż dwie ósemki (przykład: pod.trudne.dane)

int czarna_skrzynka(int podstawa, int* cyfry, int nadmiar, int poziom) {
	// szukamy sumy równej nadmiar używając jak najmniej cyfr
#ifdef DEBUG
	printf("%*sczarna_skrzynka: nadmiar: %d\n", poziom*4, "", nadmiar);
#endif
	if (nadmiar < 0)
		return NIE_TEDY_DROGA;
	else if (nadmiar == 0)
		return ROZWIAZANIE;
	int licznik = 0;
	for (int i = podstawa-1; i>0; --i) {
		if (cyfry[i] > 0) {
			++licznik; // nasza pętla coś zrobiła/sprawdziła
			cyfry[i] -= 1;
#ifdef DEBUG
			printf("%*sUsuwamy %d\n", poziom*4, "", i);
#endif
			if (czarna_skrzynka(podstawa, cyfry, nadmiar-i, poziom+1))
				return ROZWIAZANIE;
			cyfry[i] += 1;
#ifdef DEBUG
			printf("%*sPrzywracamy %d\n", poziom*4, "", i);
#endif
		}
	}
	// petla nic nie zrobila:
	// nie ma więcej cyfr, naszą podzielną liczbą będzie 0
	if (licznik == 0)
		return ROZWIAZANIE;
	return NIE_TEDY_DROGA;
}

int czarna_magia(int podstawa, int* cyfry, long int* suma_cyfr, int ilosc, int maksimum, int poziom) {
#ifdef DEBUG
	printf("%*sczarna_magia: suma_cyfr: %ld (reszta %ld)\n", poziom*4, "", *suma_cyfr, *suma_cyfr%(podstawa-1));
#endif
	// czy mamy liczbę podzielną przez podstawa-1
	if (*suma_cyfr%(podstawa-1) == 0)
		return ROZWIAZANIE;
	// limit na rekurencję
	if (ilosc == 0)
		return NIE_TEDY_DROGA;
	for (int i = maksimum; i > 0; --i) {
		if (cyfry[i] > 0) {
#ifdef DEBUG
			printf("%*sUsuwamy %d\n", poziom*4, "", i);
#endif
			cyfry[i] -= 1;
			*suma_cyfr -= i;
			if (czarna_magia(podstawa, cyfry, suma_cyfr, ilosc-1, i, poziom+1))
				return ROZWIAZANIE;
#ifdef DEBUG
			printf("%*sPrzywracamy %d\n", poziom*4, "", i);
#endif
			*suma_cyfr += i;
			cyfry[i] += 1;
		}
	}
	return NIE_TEDY_DROGA;
}

int main(void) {
	int podstawa = 0;
	long long int ilosc_pytan = 0;
	int* cyfry;
	long long int* pytania; // long long int, bo może być bardzo dużo cyfr w naszej liczbie
	// pomocnicze
	int i;
	long int suma_cyfr = 0;
	// wczytujemy rozmiar
	scanf("%d %lld", &podstawa, &ilosc_pytan);
	// tworzymy tablice
	cyfry = calloc(podstawa, sizeof (int));
	pytania = calloc(ilosc_pytan, sizeof (long long int));
	// wczytujemy cyfry
	for (i=0; i<podstawa; ++i) {
		scanf("%d", &cyfry[i]);
		suma_cyfr += i * cyfry[i];
	}
	// wczytujemy pytania
	for (i=0; i<ilosc_pytan; ++i) {
		scanf("%lld", &pytania[i]);
	}
	////////// program //////////
#ifdef DEBUG
	printf("Wczytaliśmy:\n");
	for (i=0; i<podstawa; ++i) {
		printf("%d: %d\n", i, cyfry[i]);
	}
	printf("Suma cyfr:%ld\n", suma_cyfr);
#endif
	// podzielnosc przez 9:
	// jesli suma_cyfr nie jest podzielna przez 9:
	// usuwamy sumę jak największych cyfr
	if (suma_cyfr%(podstawa-1)) {
#ifdef DEBUG
		printf("Nie jest podzielne przez %d!\n", podstawa-1);
#endif
		// usuwamy jedną cyfrę i mamy liczbę podzielną
		if (cyfry[suma_cyfr%(podstawa-1)] > 0) {
#ifdef DEBUG
			printf("Najprostszy przypadek\n");
#endif
			cyfry[suma_cyfr%(podstawa-1)] -= 1;
		} else {
			// i = suma_cyfr%(podstawa-1);
			// while (czarna_skrzynka(podstawa, cyfry, i, 1) == NIE_TEDY_DROGA)
			// 	i += podstawa-1;
			i = 2;
			while (czarna_magia(podstawa, cyfry, &suma_cyfr, i, podstawa-1, 1) == NIE_TEDY_DROGA)
				i += 1;
		}
	}
#ifdef DEBUG
	printf("Nasza liczba:\n");
	for (i=0; i<podstawa; ++i) {
		printf("%d: %d\n", i, cyfry[i]);
	}
#endif
	// najwieksza liczba
#ifdef HUMAN
	suma_cyfr = 0; // tutaj jako ilosc_cyfr
	for (i=1; i<podstawa; ++i) {
		suma_cyfr += cyfry[i];
	}
	if (suma_cyfr == 0) {
		printf("0\n");
	} else {
		for (int j=podstawa-1; j>=0; --j) {
			for (i=0; i<cyfry[j]; ++i) {
				if (podstawa > 10)
					printf("%d ",j);
				else
					printf("%d",j);
			}
		}
		printf("\n");
	}
#else
	printf("Tu powinno być wypisywanie rozwiązania zgodnie z wytycznymi\n");
#endif
	return 0;
}
