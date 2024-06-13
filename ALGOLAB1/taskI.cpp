#include <iostream>
#include <cmath>

using namespace std;


int main() {
    long long x, y, i, k, j, n;
    long count = 0;

    cin >> x >> y;

    for (i = 1; i < 60; i++) {
        for (k = 1; k < 60; k++) {
            for (j = 1; j < 60; j++) {
                n = (pow(2, j) - 1) + pow(2, k + j) * (pow(2, i) - 1);
                // cout << i << " " << k << " " << j << " " << n << "\n";
                if (x <= n and n <= y) {
                    //cout << x << " "<< n<< " " << y << "\n";
                    count += 1;
                }
            }
        }
    }
    cout << count;
    return 0;
}