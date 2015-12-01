//Antony Robbins androbbi@ucsc.edu
//Brandon Gomez brlgomez@ucsc.edu
// $Id: jxref.java,v 1.18 2014-02-18 19:08:42-08 - - $

import java.io.*;
import java.util.Scanner;

import static java.lang.System.*;

class jxref {
   static final String STDIN_NAME = "-";
   static boolean caseD = false;
   static boolean caseF = false;

   static class printer implements visitor <String, queue <Integer>> {
      public void visit (String key, queue <Integer> value) {
         out.printf ("%s", key);
         for (int linenr: value) out.printf (" %d", linenr);
         out.printf ("%n");
      }
   }

   static void xref_file (String filename, Scanner scan) {
      treemap <String, queue <Integer>> map = new
               treemap <String, queue <Integer>>();
      for (int linenr = 1; scan.hasNextLine (); ++linenr) {
         //splits the string if it is not a-z, A-Z, 0-9
         for (String word: scan.nextLine().split ("\\W+")) {
            queue <Integer> q = new queue <Integer>();
            q.insert(linenr);
            //if string matches any
            //number it will ignore and not include or print
            if(caseF == true)
               word = word.toLowerCase();
            if (word.matches ("^\\d*$")) continue;
            map.put(word, q);
            //if(caseD == true)
               map.debug_dump();
         }
         break;
      }
      if(caseD != true){
         visitor <String, queue <Integer>> print_fn = new printer ();
         map.do_visit (print_fn);
      }
   }
   static void visit (String key, queue <Integer> value) {
      out.printf ("%s", key);
      for (int linenr: value) out.printf (" %d", linenr);
      out.printf ("%n");
   }

   public static void main (String[] args) {
      //when there is no file inputed, takes in stdin
      if (args.length == 0) {
         xref_file (STDIN_NAME, new Scanner (in));
      }else {
         if(args[0].startsWith(STDIN_NAME)){
            switch(args[0]){
               case "-d" : caseD = true; break;
               case "-f" : caseF = true; break;
               case "-fd": caseD = true; caseF = true; break;
               case "-df": caseD = true; caseF = true; break;
               default: out.print("No such command"); break;
            }
         }
         for (int argi = 0; argi < args.length; ++argi) {
            //iterates each file into filename if starts with "-"
            String filename = args[argi];
            if (filename.equals (STDIN_NAME)) {
               xref_file (STDIN_NAME, new Scanner (in));
            }else {
               //file is inputed to xref_file without "-"
               try {
                  Scanner scan = new Scanner (new File (filename));
                  xref_file (filename, scan);
                  scan.close ();
               }catch (IOException error) {
                  auxlib.warn (error.getMessage());
                  exit(1);
               }
            }
         }
      }
      auxlib.exit ();
   }
}
