// $Id: linkedqueue.java,v 1.1 2011-01-20 21:05:43-08 - - $
// Antony Robbins androbbi@ucsc.edu
// Brandon Gomez brlgomez@ucsc.edu

import java.util.NoSuchElementException;

class linkedqueue <item_t> {

   private class node{
      item_t item;
      node link;
   }

   //
   // INVARIANT:  front == null && rear == null
   //          || front != null && rear != null
   // In the latter case, following links from the node pointed 
   // at by front will lead to the node pointed at by rear.
   //
   private node front = null;
   private node rear = null;
   private linkedqueue<String> link;

   
   public void print_node (node curr){
      System.out.print(curr.item);
   }

   public void print () {
      for (node curr = front; curr != null; curr = curr.link){
         print_node(curr);
      }
   }
   
   public boolean empty (){
      return front == null;
   }

   public void insert (item_t any) {
      if(empty ()){
         front = new node();
         rear = new node();
         front.item = any;
         rear = front;
         rear.link = null;
      }
      else{
         node tmp = new node();
         tmp.item = any;
         tmp.link = null;
         rear.link = tmp;
         rear = tmp;
      }      
   }

   public item_t remove (){
      if (empty ()) throw new NoSuchElementException ();
      node tmp = new node();
      tmp = front;
      if(front == front.link){
         front = null;
      }
      else front = front.link;
      return tmp.item; 
   }

   public item_t get(){
      return front.item;
   }

   public static int length(linkedqueue<String> queue) {
      int count = 0;
      for(linkedqueue<String> curr = queue;
            curr != null; curr = curr.link){
         count++;
      }
      return count;
   }
}
