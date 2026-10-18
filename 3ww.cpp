#include <stdio.h>

void ham1() { printf("Chua trien khai\n"); }
void ham2() { printf("Chua trien khai\n"); }
void ham3() { printf("Chua trien khai\n"); }

int main() {
    int chon;
    do {
        printf("\n1. Chuc nang 1\n2. Chuc nang 2\n3. Chuc nang 3\n0. Thoat\nChon: ");
        scanf("%d", &chon);
        if (chon == 1) ham1();
        else if (chon == 2) ham2();
        else if (chon == 3) ham3();
    } while (chon != 0);
    return 0;
}t
