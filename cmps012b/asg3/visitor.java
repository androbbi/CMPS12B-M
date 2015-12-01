//Antony Robbins androbbi@ucsc.edu
//Brandon Gomez brlgomez@ucsc.edu
// $Id: visitor.java,v 1.1 2014-01-16 17:44:47-08 - - $

interface visitor <key_t, value_t> {
   public void visit (key_t key, value_t value);
}
