// $Id: testtrees.java,v 1.2 2014-02-13 12:53:40-08 - - $

import static java.lang.System.*;

class testtrees {

   static class printer implements visitor<String> {
      public void visit (String item) {
         out.printf ("%s%n", item);
      }
   }

   static class find_longest implements visitor<String> {
      String longest = "";
      public void visit (String item) {
         if (longest.length() < item.length()) longest = item;
      }
   }

   public static void main (String[] args) {
      String[] arguments = new String [args.length];
      for (int itor = 0; itor < args.length; ++itor) {
         arguments[itor] = "args[" + itor + "]=\"" + args[itor] + "\"";
      }
      tree<String> the_tree = new tree<String> (arguments);
      the_tree.visit (new printer ());
      find_longest longest = new find_longest();
      the_tree.visit (longest);
      out.printf ("The longest string is \"%s\"%n", longest.longest);
   }

}
