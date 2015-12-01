// $Id: jroff.java,v 1.31 2014-02-04 00:21:16-08 - - $

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class jroff{
   static final String STDIN_NAME = "-";

   static void scanfile (String filename, Scanner infile){
      linkedqueue <String> words = new linkedqueue <String> ();
      while(infile.hasNextLine()) {
	     int num = 0;
		 String incon = commands.control;
         String line = infile.nextLine();
         String[] read = line.split ("\\s+");
		 if (read.length > 0 && read[0].startsWith(incon)) {
		    if((read[1]).matches(".*\\d.*")) {
			   num = Integer.parseInt(read[1]);
			   for(int i = 2; i < read.length; i++) {
			      String word = read[i];
				  words.insert(word);
               }
            }
			else {
			   for(int i = 1; i < read.length; i++) {
			      String word = read[i];
				  words.insert(word);
			   }
		    }	  
            try {
               commands.do_command (read, words, num, incon);
            }catch (IllegalArgumentException error) {
               auxlib.warn (filename, read[0],
                            "invalid command");
            }
         }else {
            for (String word: read){
               words.insert(word);
            }
            //auxlib.printparagraph(words);
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
