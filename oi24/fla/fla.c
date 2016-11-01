#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
} pozycja;

typedef struct {
	int x;
	int a;
	int b;
} przeszkoda;

int main(void) {
	int liczba_przeszkod = 0;
	int meta = 0;
	przeszkoda* przeszkody;
	int* droga;
	// wczytujemy rozmiar
	scanf("%d %d", &liczba_przeszkod, &meta);
	
	// brak przeszkod, brak klikania
	if (liczba_przeszkod == 0) {
		printf("0\n");
		return 0;
	}

	// tworzymy tablice
	przeszkody = calloc(liczba_przeszkod, sizeof (przeszkoda));
	droga = calloc(meta, sizeof (int));
	// wczytujemy przeszkody
	int i;
	for (i=0; i<liczba_przeszkod; ++i) {
		scanf("%d %d %d", &przeszkody[i].x, &przeszkody[i].a, &przeszkody[i].b);
	}

	////////// program //////////
	pozycja j = { .x = 0, .y = 0 };
	int najblizsza_przeszkoda = 0;
	while (j.x < meta) {
		// pilnujemy najblizszej przeszkody zeby ulatwic obliczenia
		if (przeszkody[najblizsza_przeszkoda].x < j.x && najblizsza_przeszkoda < liczba_przeszkod-1)
			++najblizsza_przeszkoda;
#ifdef DEBUG
		printf("Jestesmy w %d, %d\n", j.x, j.y);
#endif
		// dla naszego x mamy przeszkode
		if (j.x == przeszkody[najblizsza_przeszkoda].x
				&& (j.y <= przeszkody[najblizsza_przeszkoda].a
					|| j.y >= przeszkody[najblizsza_przeszkoda].b)) {
#ifdef DEBUG
			printf("PRZESZKODA\n");
#endif
			// cofamy sie
			droga[j.x] = 0; j.x -= 1; j.y += 1;
			while (droga[j.x] == 1) {
				//j.y += 1;
				j.y -= droga[j.x];
				droga[j.x] = 0;
				j.x -= 1;
				if (j.x < 0) {
					// nie da się
					printf("NIE\n");
					return 0;
				}
				// pilnujemy najblizszej przeszkody zeby ulatwic obliczenia
				while (przeszkody[najblizsza_przeszkoda].x > j.x && najblizsza_przeszkoda > 0)
					--najblizsza_przeszkoda;
			}
#ifdef DEBUG
			printf("cofamy sie az do %d\n", j.x);
#endif
			droga[j.x] = 1;
			j.x += 1;
			j.y += 1;
		} else {
			// krok
			droga[j.x] = -1;
			j.x += 1;
			j.y -= 1;
		}
	}
#ifdef DEBUG
	printf("Droga:\n");
	for (i=0; i<meta; ++i) {
		printf("%d: %d\n", i, droga[i]);
	}
	j.x = 0; j.y = 0;
	for (i=0; i<meta; ++i) {
		printf("%d %d\n", j.x, j.y);
		j.x += 1;
		if (droga[i] == 1) {
			j.y += 1;
		} else {
			j.y -= 1;
		}
	}
	printf("%d %d\n", j.x, j.y);
#else
	int wynik = 0;
	for (i=0; i<meta; ++i) {
		if (droga[i] == 1)
			wynik += 1;
	}
	printf("%d\n", wynik); 
#endif
}
