// $Id: uninit.c,v 1.3 2014-02-18 15:08:14-08 - - $

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   int *pointer;
   printf ("pointer=%p\n", pointer);
   printf ("*pointer=%d\n", *pointer);
   int foo;
   printf ("foo=%d\n", foo);
}
