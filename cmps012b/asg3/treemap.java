//Antony Robbins androbbi@ucsc.edu
//Brandon Gomez brlgomez@ucsc.edu
// $Id: treemap.java,v 1.1 2014-01-16 17:44:47-08 - - $

import static java.lang.System.*;

class treemap <key_t extends Comparable <key_t>, value_t> {
   
   private class node {
      key_t key;
      value_t value;
      node left;
      node right;
   }
   private node root;

   private void debug_dump_rec (node tree, int depth) {
      String indent = "";
      for (int i = 0; i < depth; i++){
         indent += " ";
      }
      node right = null;
      node left = null;
      right = tree.right;
      left = tree.left;
      if(root != null){
         if(right != null)
            debug_dump_rec(right, depth+=1);
         out.println(indent + depth + " " +
               tree.key + " " + tree.value);
         if(left != null)
            debug_dump_rec(left, depth+=1);
      }
   }

   private void do_visit_rec (visitor <key_t,
         value_t> visit_fn, node tree) {
      if(tree == null){
         return;
      }
      tree = root;
      do_visit_rec(visit_fn, tree.right);
      visit_fn.visit(tree.key, tree.value);
      do_visit_rec(visit_fn, tree.left);
   }

   public value_t get (key_t key) {
      node curr = root;
      while(curr != null){
         int cmp = key.compareTo(curr.key);
         if(cmp == 0){
            return curr.value;
         }
         if(cmp < 0){
            curr = curr.right;
            continue;
         }
         else{
            curr = curr.left;
            continue;
         }
      }
      return null;
   }

   public value_t put (key_t key, value_t value) {
      if(root == null){
         node newnode = new node();
         root = newnode;
         root.key = key;
         root.value = value;
         return null;
      }
      else{
         node curr = new node();
         node prev = new node();
         curr = root;
         while(curr != null){
            int cmp = key.compareTo(curr.key);
            if (cmp == 0){
               curr.key = key;
               curr.value = value;
               //root = curr;
               return prev.value;
            }
            if(cmp < 0){
               prev = curr;
               curr = curr.right;
               continue;
            }
            else{
               prev = curr;
               curr = curr.left;
               continue;
            }
         }
         prev.key = key;
         prev.value = value;
         root = prev;
         return null;
      }
   }

   public void debug_dump () {
      debug_dump_rec (root, 0);
   }

   public void do_visit (visitor <key_t, value_t> visit_fn) {
      do_visit_rec (visit_fn, root);
   }

}
