// $Id: commands.java,v 1.7 2014-01-17 17:57:56-08 - - $

//import java.util.HashMap;
import static java.lang.System.*;
class commands {
      static int currLine = 0;
      static int lineLength = 20;
	  static int pageLength = 60;
	  static int pageNumber = 1;
	  static int pageOffset = 10;
	  static int indent = 0;
	  static int topMargin = 6;
	  static String control = "a";
	  static boolean newPage = true;
	  static boolean blankLine = false;
	  static boolean printPage = true;
	  static int endLines = 1;

   private static void command_00 (String[] read, linkedqueue<String> queue) {
      // Executing a comment does nothing.
   }

   private static void command_bp (String[] read, linkedqueue<String> queue) {
      if(newPage == true) {
	     for(int i = 0; i < topMargin; i ++){
	        out.print("\n");
		    if(i >= topMargin/2 || topMargin == 1){
		       for(int j = 0; j < lineLength + pageOffset; j++){
			      out.print(" ");
			   }
		       if(printPage == true) {
			      out.print(pageNumber);
				  printPage = false;
			   }
		    }
	     }
		 if(topMargin > 0) {
		    out.print("\n");
			currLine++;
         }
		 printPage = true;
      }
      newPage = false;
	  command_br(read, queue);
	  blankLine = true;
   }

   private static void command_br (String[] read, linkedqueue<String> queue) {
      for(int j = 0; j < pageOffset + indent; j++){
	     out.print(" ");
	  }
      auxlib.printparagraph(queue, lineLength);
   }

   private static void command_cc (String[] read, linkedqueue<String> queue, String cont) {
      control = cont;
   }

   static void command_in (String[] read, linkedqueue<String> queue, int ind) {
      indent = ind;
   }

   private static void command_ll (String[] read, linkedqueue<String> queue, int length) {
      lineLength = length;
   }

   private static void command_mt (String[] read, linkedqueue<String> queue, int top) {
      topMargin = top;
   }

   private static void command_pl (String[] read, linkedqueue<String> queue) {

   }

   static void command_po (String[] read, linkedqueue<String> queue, int off) {
      pageOffset = off;
   }

   static void command_sp (String[] read, linkedqueue<String> queue, int space) {
      endLines = space;
	  for(int i = 0; i < endLines; i++) {
	     out.print("\n");
      }
   }
   public static void do_command (String[] read, linkedqueue<String> queue, int num, String con) {
      switch (read[0]) {
         case con  + "\\\"": command_00 (read, queue); break;
         case con  + "bp"  : command_bp (read, queue); break;
         case con  + "br"  : command_br (read, queue); break;
         case con  + "cc"  : command_cc (read, queue, con); break;
         case con  + "in"  : command_in (read, queue, num); break;
         case con  + "ll"  : command_ll (read, queue, num); break;
         case con  + "mt"  : command_mt (read, queue, num); break;
         case con  + "pl"  : command_pl (read, queue); break;
         case con  + "po"  : command_po (read, queue, num); break;
         case con + "sp"   : command_sp (read, queue, num); break;
         default     : throw new IllegalArgumentException (read[0]);
      }
   }

}

