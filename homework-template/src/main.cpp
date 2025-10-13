#include <iostream>
#include <cstdlib>
using namespace std;

const int MAX_STACK = 10000; // 記憶體限制

int ackermann_non_recursive(int m, int n) {
    int stack[MAX_STACK];
    int top = -1;

    stack[++top] = m;

    while (top >= 0) {
        m = stack[top--];

        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            stack[++top] = m - 1;
            n = 1;
        } else {
            stack[++top] = m - 1;
            stack[++top] = m;
            n = n - 1;
        }
    }
    return n;
}

int main() {
    int m, n;
    cout << "Enter m and n: ";
    cin >> m >> n;
    cout << "Ackermann(" << m << ", " << n << ") = " << ackermann_non_recursive(m, n) << endl;
    return 0;
}
