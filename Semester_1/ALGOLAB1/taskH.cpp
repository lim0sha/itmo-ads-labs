#include <iostream>

using namespace std;


int main() {
    int n, s = 0, total = 0, index_first=-10, index_last;
    int answer = 10000;
    bool flag = true;
    bool change = false;
    cin >> n;
    int rooms[n];
    for (int i = 0; i < n; i++) {
        cin >> rooms[i];
    }

    for (int j = 0; j < 10; j++) {
        if (j != 0) {
            for (int m = 0; m < 1; m++) {

                int temp = rooms[0];
                for (int i = 1; i < n; i++) {
                    rooms[i - 1] = rooms[i];
                }
                rooms[n - 1] = temp;

            }

        }

        index_first=-10;
        for (int i = 0; i < n; i++) {
            if ((s & rooms[i]) != 0) {
                s = rooms[i];
                total += 1;
                if (flag) {
                    index_first = i;
                    flag = false;
                }
            } else {
                s = (s | rooms[i]);
            }
        }

        int new_array[n + index_first];
        for (int i = 0; i < n + 2; i++) {
            if (i < n) {
                new_array[i] = rooms[i];
            } else {
                new_array[i] = rooms[i - n];
            }
        }


        total = 0;
        for (int i = 0; i < n; i++) {
            if ((s & new_array[i]) != 0) {
                s = new_array[i];
                total += 1;

            } else {
                s = (s | new_array[i]);
            }
        }
        if (total < answer) {
            answer = total;
            change = true;
        }


    }
    if (change = false) {
        cout << 1;
    } else {
        cout << answer;
    }

    return 0;
}