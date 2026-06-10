#include <stdio.h>

typedef struct {
    int age;
} myStruct;

int main() {
    myStruct m;

    m.age = 21;

    printf("%d", m.age);

    return 0;
}