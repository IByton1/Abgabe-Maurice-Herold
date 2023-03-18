#include <iostream>
#include <vector>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<int> p(n), q(n);
        for (int i = 0; i < n; i++) {
            p[i] = q[i] = i;
        }

        bool found = false;
        for (int i = 0; i < n; i++) {
            if (a[i] != i + 1) {
                p[a[i] - 1] = i;
                q[i] = a[i] - 1;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Possible\n";
            for (int i = 0; i < n; i++) {
                cout << i + 1 << " ";
            }
            cout << "\n";
            for (int i = 0; i < n; i++) {
                cout << i + 1 << " ";
            }
            cout << "\n";
            continue;
        }

        for (int i = 0; i < n; i++) {
            if (p[i] == i) {
                for (int j = 0; j < n; j++) {
                    if (p[j] != i) {
                        swap(p[i], p[j]);
                        swap(q[i], q[j]);
                        break;
                    }
                }
            }
        }

        bool possible = true;
        for (int i = 0; i < n; i++) {
            if (a[p[q[i]]] != i + 1) {
                possible = false;
                break;
            }
        }

        if (possible) {
            cout << "Possible\n";
            for (int i = 0; i < n; i++) {
                cout << p[i] + 1 << " ";
            }
            cout << "\n";
            for (int i = 0; i < n; i++) {
                cout << q[i] + 1 << " ";
            }
            cout << "\n";
        } else {
            cout << "Impossible\n";
        }
    }
    return 0;
}
