// # $ID$
// Antony Robbins androbbi@ucsc.edu
import static java.lang.System.*;
class exit1{
   public static final int EXIT_FAILURE = 255;
   public static int exit_status = EXIT_FAILURE;

   public static void main(String[] args){  
      err.printf ("%s%n", "EXIT 255");
      exit (exit_status);
   }
}
