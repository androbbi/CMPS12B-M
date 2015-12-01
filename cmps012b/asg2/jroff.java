// $Id: jroff.java,v 1.34 2014-02-04 15:05:38-08 - - $
// Antony Robbins androbbi@ucsc.edu
// Brandon Gomez brlgomez@ucsc.edu

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class jroff{
   static final String STDIN_NAME = "-";
   static int count = 0;
   static boolean format = true;
   static void scanfile (String filename, Scanner infile) {
      linkedqueue <String> queue = new linkedqueue <String> ();
      int num = 0;
      int i = 1;
      //out.printf ("STUB: filename = %s%n", filename);
      while(infile.hasNextLine()) {
         String line = infile.nextLine();
         //out.printf ("STUB: %s: %4d: [%s]%n", filename, linenr, line);
         String[] words = line.split ("\\s+");
         if (words.length > 0 && words[0].startsWith (".")) {
            if(words.length > 1 && (words[1]).matches(".*\\d.*")){
               num = Integer.parseInt(words[1]);
               i = 2;
            }
            try {
               for (int j = i; j < words.length; j++){ 
                  String word = words[j];
                  queue.insert(word);                  
               }
               format = true;
               commands.do_command (words, queue, num);
            }catch (IllegalArgumentException error) {
               auxlib.warn (filename, words[0],
                     "invalid command");
            }
         }else {
            for (String word: words) 
               queue.insert(word);
            auxlib.printparagraph(queue, 65);
            out.printf ("%n");
         }
      }
   }

   public static void main (String[] args) {

      if (args.length == 0) {
         scanfile (STDIN_NAME, new Scanner (in));
      }else {
         for (String filename : args) {
            if (filename.equals (STDIN_NAME)) {
               scanfile (STDIN_NAME, new Scanner (in));
            }else {
               try {
                  Scanner scan = new Scanner (new File (filename));
                  scanfile (filename, scan);
                  scan.close();
               }catch (IOException error) {
                  auxlib.warn (error.getMessage());
               }
            }
         }
      }
   }

}
