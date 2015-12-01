// $Id: commands.java,v 1.17 2014-02-04 15:27:16-08 - - $
// Antony Robbins androbbi@ucsc.edu
// Brandon Gomez brlgomez@ucsc.edu

import static java.lang.System.*;

class commands {
   static int lineLength = 65;
   static int topMargin = 6;
   static int currPage = 1;
   static int pageOffSet = 10;
   static int indent = 0;
   static int pageLength = 60;
   static int spaces = 1;
   static boolean printNum = true;
   
   private static void command_00 (String[] words) {
      // Executing a comment does nothing.
   }

   private static void command_bp (String[] words,
               linkedqueue<String> queue) {
      for(int i = 0; i < topMargin; i++){
         out.print("\n");
         if((i >= topMargin/2-1) && printNum == true){
            for(int j = 0; j < lineLength + pageOffSet; j++){
               out.print(" ");
            }
            out.print(currPage);
            printNum = false;
         }
      }
      printNum = true;
      currPage++;
      out.print("\n");
      command_br(words, queue);
   }

   private static void command_br (String[] words,
               linkedqueue<String> queue) {
      auxlib.printparagraph(queue, lineLength - pageOffSet - indent);
      command_sp(words, spaces);
   }

   private static void command_cc (String[] words) {

   }

   private static void command_in (String[] words, int ind) {
      indent = ind;
   }

   private static void command_ll (String[] words, int length) {
      lineLength = length;
   }

   private static void command_mt (String[] words, int top) {
      topMargin = top;
   }

   private static void command_pl (String[] words, int pLength) {
      pageLength = pLength;
   }

   static String command_po (String[] words, int pageOff) {
      pageOffSet = pageOff;
      String off = "";
      for(int i = 0; i < pageOffSet + indent; i++){
          off+=" ";
      }
      return off;
   }

   private static void command_sp (String[] words, int space) {
      for(int i = 0; i < spaces; i++){
         out.print("\n");
      }
      spaces = space;
   }

   public static void do_command (String[] words,
            linkedqueue<String> queue, int num) {
      switch (words[0]) {
      case ".\\\"": command_00 (words); break;
      case ".bp"  : command_bp (words, queue); break;
      case ".br"  : command_br (words, queue); break;
      case ".cc"  : command_cc (words); break;
      case ".in"  : command_in (words, num); break;
      case ".ll"  : command_ll (words, num); break;
      case ".mt"  : command_mt (words, num); break;
      case ".pl"  : command_pl (words, num); break;
      case ".po"  : command_po (words, num); break;
      case ".sp"  : command_sp (words, num); break;
      default     : throw new IllegalArgumentException (words[0]);
      }
   }

}
