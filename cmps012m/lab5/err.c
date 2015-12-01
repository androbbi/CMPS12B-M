#include <stdio.h>
void foo() {
   int x = 20;
   int *p = &x;
}
void bar() {
   int a;
   int *p;
   printf ("%d %p\n", a, p);
}
int main() {
   foo();
   bar();
}
