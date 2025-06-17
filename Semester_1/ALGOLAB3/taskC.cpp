#include <iostream>
#include <string>

using namespace std;

int main() {
    int n, t, k;
    string temp;
    cin >> n >> k >> t;
    string words[n];
    for (int i = 0; i < n; ++i) {
        cin >> temp;
        words[i] = temp;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (words[i].substr(words[i].length() - t) > words[j].substr(words[j].length() - t)) {
                //cout << words[i] << " " << words[j] << "\n";
                swap(words[i], words[j]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << words[i] << endl;
    }
    return 0;
}