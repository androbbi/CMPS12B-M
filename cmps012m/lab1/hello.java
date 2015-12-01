// Antony Robbins androbbi@ucsc.edu
// $Id: hello.java,v 1.3 2014-01-06 23:51:33-08 androbbi - $
// 
// NAME
//    hello - a verbose version of the classical "Hello World" program.
//
// SYNOPSIS
//    hello
//
// DESCRIPTION
//    Introduces itself and its environment.
//

import java.util.ArrayList;
import java.util.List;
import static java.lang.System.*;
class hello {
   static void printprop (String format, String... properties) {
      List<Object> property_values = new ArrayList<Object>();
      for (String property: properties) {
         property_values.add (getProperty (property));
      }
      out.printf (format, property_values.toArray());
   }
   public static void main (String[] args) {
      double memory = Runtime.getRuntime().freeMemory();
      long now = currentTimeMillis();
      out.printf ("Hello, World!%n");
      printprop ("Class path is%n%s%n", "java.class.path");
      printprop ("Operating system is %s-bit %s-endian %s %s %s%n",
                 "sun.arch.data.model", "sun.cpu.endian",
                 "os.arch", "os.name", "os.version");
      printprop ("Runtime is %s (%s)%n",
                 "java.runtime.name", "java.runtime.version");
      printprop ("Virtual machine is %s (%s)%n",
                 "java.vm.name", "java.vm.version");
      printprop ("Home is %s (%s)%n", "java.home", "java.version");
      out.printf ("There are %.0f bytes = %.4f Mbytes free memory%n",
                  memory, memory / (1<<20));
      out.printf ("Time is now %.3f seconds = %tc%n", now / 1e3, now);
   }
}
