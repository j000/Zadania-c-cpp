# ALGORYTMION 2016
## Zadanie 2

Niech dana jest funkcja *y = f(x)* określona dla *x ∈ \<a, b\>* i przyjmująca na tym przedziale dodatnie wartości. Chcemy znaleźć największą wartość tej funkcji w tym przedziale (zakładając, że nie znamy pojęcia pochodnej funkcji). Należy zauważyć, że:

* wartość taka może być osiągana na końcach przedziału,
* wartość taka może być osiągana wewnątrz przedziału,
* wartość taka może być osiągana wielokrotnie w tym przedziale.

Sposób znalezienia tej wartości może być następujący:

1. Losujemy z przedziału *\<a, b\>* n liczb.
2. Dla każdej z nich obliczamy wartość funkcji.
3. Ponieważ poszukujemy wartości największej – sortujemy malejąco wylosowane punkty wg. wartości funkcji.
4. Oczywiście nawet pierwszy z punktów nie musi gwarantować znalezienia wartości największej. Dlatego punkty te muszą „ewoluować”: na podstawie listy punktów tworzyć będziemy kolejną listę, a ponieważ największe znaczenie mają te początkowe (po sortowaniu) punkty, dlatego one powinny „wydać na świat” (porównanie jest nieprzypadkowe – tak właśnie postępuje natura – osobniki najlepiej dostosowane wydają więcej potomstwa) statystycznie więcej „potomków”. Odbywać się to będzie tak, że każdemu z punktów przypisywać będziemy odpowiednią wagę – proporcjonalną do wartości funkcji w tym punkcie (patrz „podział pizzy” na poniższym rysunku). Następnie, z przedziału <0,1>  losujemy n liczb sprawdzając, do którego „kawałka pizzy” należy wylosowana liczba (proporcje podziału odcinka są takie same jak proporcje podziału pizzy). Po każdym takim losowaniu (a jest ich n) otrzymujemy osobnika takiego, jaki tworzył dany „kawałek pizzy”. Populację sortujemy (malejąco po wartościach funkcji), następnie tak utworzona nowa populacja krzyżuje się (krzyżowanie punktów to ich średnia arytmetyczna): pierwszy z drugim, drugi z trzecim,…, przedostatni z ostatnim i, aby otrzymać w sumie n osobników, ostatni z pierwszym. Otrzymujemy w ten sposób pokolenie dzieci z pokolenia rodziców. Obliczamy wartości dla pokolenia dzieci i z obydwu pokoleń wybieramy 90% (z zaokrągleniem do najbliższej liczby naturalnej) z najlepszych osobników, a brakujące około 10% dolosowujemy z przedziału *<a, b>*.
5. Takie nowe pokolenie staje się teraz pokoleniem rodziców i dla niego powtarzamy punkt 4 otrzymując kolejne pokolenie.
6. Czynności 4–5 powtarzamy m razy i z ostatniego pokolenia wybieramy osobnika najlepszego, uznając go za rozwiązanie.

Napisz program, który dla zadanej funkcji (można ograniczyć się do pewnego, znanego wcześniej zbioru funkcji) **f(x)**, dla danego przedziału **\<a, b\>** i dla danych wartości **n** i **m** poszukiwał będzie wartości największej dla dodatniej funkcji *f(x)* na przedziale *\<a, b\>*.

Przykładowo, gdyby po wylosowaniu pięciu punktów posortowane pary (punkt, wartość) były postaci: (x3, 4), (x1, 3), (x2, 2), (x5, 1.5), (x4, 0.5), to w przypadku wylosowania z przedziału <0,1> pięciu liczb: 0.2, 0.75, 0.1, 0.85, 0.3 odpowiadały by im (pierwsi rodzice) następujące punkty: x3, x2, x3, x5, x3.

Program przetestuj np. dla funkcji f(x) = (|x − 1| − 1)|x − 1|(x − 3) + 1 dla x ∈ <0,3>, n = 20 i m = 50. Funkcja osiąga wartość największą równą 7/27 * (1 + 2√7) ≈ 1.63113 dla x = 1/3*(4 − √7) ≈ 0.4514.
