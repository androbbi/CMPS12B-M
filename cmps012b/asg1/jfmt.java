// $Id: jfmt.java,v 1.2 2013-09-24 14:38:16-07 - - $
//
// Antony Robbins androbbi@ucsc.edu
// Brandon Gomez brlgomez@ucsc.edu

import java.io.*;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import static java.lang.System.*;

class jfmt {
   // Static variables keeping the general status of the program.
   public static final String JAR_NAME = get_jarname();
   public static final int EXIT_SUCCESS = 0;
   public static final int EXIT_FAILURE = 1;
   public static int exit_status = EXIT_SUCCESS;

   // A basename is the final component of a pathname.
   // If a java program is run from a jar, the classpath is the
   // pathname of the jar.
   static String get_jarname() {
      String jarpath = getProperty ("java.class.path");
      int lastslash = jarpath.lastIndexOf ('/');
      if (lastslash < 0) return jarpath;
      return jarpath.substring (lastslash + 1);
   }

   // Formats a single file.
   static void format (Scanner infile, int lineLength) {
      // Read each line from the opened file, one after the other.
      // Stop the loop at end of file.
      // Ensures one blank line is printed between paragraphs
      // Create a LinkedList of Strings.
      boolean printblank = true;
      List<String> words = new LinkedList<String>();
      while(infile.hasNextLine()) {
         String line = infile.nextLine();
         line = line.trim();
         // Split the line into words around white space and iterate
         // over the words.
         // Prints paragraph after a new paragraph
         for (String word: line.split ("\\s+")) {
            if (word.length() == 0){
               if(printblank == true){
                  print_paragraph(words, lineLength);
                  out.printf("%n");
               }
               printblank = false;
               continue;
            }
            // Append the word to the end of the linked list.
            if(word != null)
               words.add (word);
               printblank = true;

         } 
         // Use iterator syntax to print out all of the words.
         //for (String word: words) out.printf (" %s", word);
      }
      print_paragraph(words, lineLength);
      out.printf("%n");
   }
   //Prints the paragraph after formatting
   //Accounts the width the user inputted
   static void print_paragraph(List<String> words, int lineLength){
      int count = 0;
      int length = lineLength;
      for(String word: words){
         count += word.length();
         if(count >= length){
            out.printf("%n");
            out.printf(word);
            count = word.length();
         }
         else{
            if(count != word.length()){
               out.printf(" ");
               count++;
            }
         out.printf(word);
         }
      }
      out.printf("%n");
      words.clear();
   }
   // Main function scans arguments and opens/closes files.
   public static void main (String[] args) {
      int lineLength = 65;
      if (args.length == 0) {
         // There are no filenames given on the command line.
         format (new Scanner (in), lineLength);
      }else {
        if(args[0].matches("-\\d+")){
            String arg = args[0];
            try {
               lineLength = Integer.parseInt(arg.substring(1));
            }catch (NumberFormatException error) {
               exit_status = EXIT_FAILURE;
               err.printf ("NumberFormatException: %s%n",
                          error.getMessage());
            }
            
        }
         // Iterate over each filename given on the command line.
         for (int argix = 0; argix < args.length; ++argix) {
            String filename = args[argix];
            if (filename.equals ("-")) {
               // Treat a filename of "-" to mean System.in.
               format (new Scanner (in), lineLength);
            }else {
               // Open the file and read it, or error out.
               try {
                  Scanner infile = new Scanner (new File (filename));
                  out.printf ("%n");
                  format (infile, lineLength);
                  infile.close();
               }catch (IOException error) {
                  exit_status = EXIT_FAILURE;
                  err.printf ("%s: %s%n", JAR_NAME,
                              error.getMessage());
               }
            }
         }
      }
      exit (exit_status);
   }

}
