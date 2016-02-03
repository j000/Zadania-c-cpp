#include <iostream>
#include <cmath>

using namespace std;

int coconuts(int n) {
	if (n < 2) return 0;
	// ...
	// ((((x * n)) * n/(n-1) + 1) * n/(n-1) + 1) * n/(n-1) + 1
	//  (((x * n)) * n/(n-1) + 1) * n/(n-1) + 1
	//   ((x * n)) * n/(n-1) + 1
	//    (x * n)
	// n = 2 => x = 1, cocos = 11
	// n = 3 => x = 2, cocos = 25
	int x = 1;
	do {
#ifdef DEBUG
		cout << x << endl;
#endif
		double cocos = x * n;
		for (int i = 0; i < n; ++i) {
			cocos *= n;
			cocos /= n-1;
			cocos += 1;
#ifdef DEBUG
			cout << "    " << i+1 << " => " << cocos << " (" << floor(cocos) << ")" << endl;
#endif
		}
		if (cocos == floor(cocos))
			return (int)floor(cocos);
		++x;
	} while (1);
}

int main() {
    int sailors;
    cout << "Enter the number of sailors: ";
    cin >> sailors;
    cout << "At least " << coconuts(sailors) << " coconuts" << endl;
    return 0;
}

