// $Id: linkedqueue.java,v 1.6 2014-01-21 21:21:57-08 - - $

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

   public boolean empty (){
      return front == null;
   }

   public void insert (item_t any) {
	  if(empty()){
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
	  if(front == rear){
		 front = null;
      }
	  else front = front.link;
	  return tmp.item;
   }
  
   public item_t get() {
      return front.item;
   }

}
