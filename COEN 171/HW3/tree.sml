(* a tree is either empty or is a node consisting of
   an integer, a left subtree, and a right subtree *)
   
datatype tree = empty | node of (int * tree * tree);


(* member goes here *)
fun member empty x = false
	|member (node(v,left,right)) x = 
		if x < v then node(v, member left x, right)
		else if x > v then node(v, left, member right x)
		else true;

(* insert goes here *)
fun insert empty x = node(x, empty, empty)
	|insert (node(v,left,right)) x = 
		if x < v then node(v, insert left x, right) 
		else node(v, left, insert right x);

(* build = fn : int list -> tree
   Returns a tree that is result of inserting all integers in the given list *)

val build = foldl (fn (v,t) => insert t v) empty;


(* inorder = fn : tree -> int list
   Returns a list that is contains all integers in the tree in order *)

fun inorder empty = []
  | inorder (node(d, l, r)) = inorder l @ d :: inorder r;
