#include <stdio.h>
#include <string.h>
int main (void) {
   char *p = 20;
   int c = strcmp (p, "foo");
   printf ("%d\n", c);
   return 0;
}
