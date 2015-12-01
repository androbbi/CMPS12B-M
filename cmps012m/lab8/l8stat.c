//Antony Robbins androbbi@ucsc.edu
//Brandon Gomez brlgomez@ucsc.edu
#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <utime.h>
#include <sys/types.h>
#include<sys/stat.h>
#include <unistd.h>

int EXIT_STATUS = EXIT_SUCCESS;

void l8stat(char *filename) {
   struct stat sb;
   int time180 = 180 * 24 * 60 * 60;
   char link[1024];
   int info = lstat(filename, &sb);
   if(info != 0){
     printf("Stat failure\n");
     fflush(NULL);
     fprintf(stderr,"%s: %s\n",
              filename, strerror(errno));
      fflush(NULL);
     EXIT_STATUS = EXIT_FAILURE;
   } else {
      printf("%06o %9d ", (int)sb.st_mode, (int)sb.st_size);
     char buff[256];
     char *timeformat = NULL;
     time_t current;
     time(&current);
     struct tm *tm = localtime(&sb.st_mtime);
     if(current - sb.st_mtime > time180){
        timeformat = "%b %e %Y";
     } else {
        timeformat = "%b %e %R";
     }
     strftime (buff, sizeof(buff),timeformat, tm);
      printf("%12s %s", buff, filename);
     
     int link_status = readlink(filename, link, sizeof(link));
      if(link_status != -1) {
         printf(" -> %s", link);
      }
   }
   printf("\n");
}

int main (int argc, char **argv) {
   if(argc == 1) {
      l8stat(".");
   }
   else {
      for(int i = 1; i < argc; i++){
        l8stat(argv[i]);
      }
   }
   return EXIT_STATUS;
}
