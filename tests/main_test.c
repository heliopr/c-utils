#include <stdio.h>


void testList();

void test(const char *name, void (*testFun)()) {
    printf("TEST %s\n", name);
    (*testFun)();
    printf("TEST %s passed\n", name);
}

int main() {
    test("List", testList);
}