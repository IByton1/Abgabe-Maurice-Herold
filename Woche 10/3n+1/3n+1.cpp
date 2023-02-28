#include <iostream>
#include <algorithm>

using namespace std;


// A function to calculate the cycle length of a number
int cycleLength(int n) {
    int length = 1;
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        length++;
    }
    return length;
}

// A function to calculate the maximum cycle length between i and j
int maxCycleLength(int i, int j) {
    if (i > j) {
        swap(i, j);
    }
    int maxCycle = 0;
    for (int n = i; n <= j; n++) {
        int cycle = cycleLength(n);
        maxCycle = max(maxCycle, cycle);
    }
    return maxCycle;
}

int main() {
    int i, j;
    while (cin >> i >> j) {
        cout << i << " " << j << " " << maxCycleLength(i, j) << endl;
    }
    return 0;
}
