#include <stdio.h>

int compute(int a) {
    int b = a * 5;
    return b;
}

int main() {
    int x = 10;
    int y = compute(2 * x);

    printf("%d\n", y);

    return 0;
}

