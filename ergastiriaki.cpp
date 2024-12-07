

/* Lab exam */


// IF YOU TOUCH ANYTHING OUTSIDE THE LINES MARKED WITH "(snip)"
// THEN YOU'D BETTER KNOW WHAT YOU'RE DOING!  YOUR CODE MAY NOT
// COMPILE.  YOU HAVE BEEN WARNED!

//#ifndef CONTEST
#include <iostream>

using namespace std;

struct list_node {
  int data;
  list_node *next;
};

struct tree_node {
  int data;
  tree_node *left, *right;
};

//#endif

// YOUR SOLUTION GOES HERE -- YOU DON'T NEED TO ERASE THE REST
// -----------------------------------------------------------
// MAKE SURE THAT YOUR SUBMISSION COMPILES, OTHERWISE YOU WILL
// GET ZERO POINTS TODAY AND THAT WILL BE A PITY!
// ------------------------(snip)-----------------------------

int list_length(list_node *l) {
  list_node *h = l;
  int s = 0;
  while (h != nullptr){
    h = h->next;
    s++;
  }
  return s;
}

int list_minimum(list_node *l) {
  list_node *h = l;
  int min = INT_MAX;
  while (h != nullptr){
    if (h->data < min){
      min = h->data;
    }
    h = h->next;
  }
  return min;
}

int list_middle(list_node *n) {
  list_node *h = n;
  int s = 1;
  int j = (list_length(n) / 2) + 1;
  while (h->next != nullptr && s < j){
    s++;
    h = h->next;
  }
  return h->data;
}

void preorder (tree_node *t, int &s) {
  if(t != nullptr){
    s++;
    //cout << t->key << ' ' << t->repetition_count << endl;
    preorder(t->left,s);
    preorder(t->right,s);
  }
}

void preorder_leaves (tree_node *t, int &count) {
  if(t != nullptr){
    if(t->left == nullptr && t->right == nullptr) count += t->data;
    //cout << t->key << ' ' << t->repetition_count << endl;
    preorder_leaves(t->left,count);
    preorder_leaves(t->right,count);
  }
}

void preorder_possible (tree_node *t ,int &num_of_possibilities, int &k, int height_now) {
  if(t != nullptr){
    if (height_now <= k){
      if(t->left == nullptr && t->right == nullptr)num_of_possibilities++;
      height_now++;
      //cout << t->key << ' ' << t->repetition_count << endl;
      preorder_possible(t->left,num_of_possibilities,k,height_now);
      preorder_possible(t->right,num_of_possibilities,k,height_now);
    }
  }
}

int tree_size(tree_node *t) {
  int size = 0;
  preorder(t, size);
  return size;
}

int tree_sum_of_leaves(tree_node *t) {
  int count = 0;
  preorder_leaves(t,count);
  return count;
}

int tree_room_high(tree_node *t, int k) {
  int num_of_possibilities = 0;
  int height_now = 1;
  preorder_possible(t,num_of_possibilities,k,height_now);
  return num_of_possibilities;
}

// ------------------------(snip)-----------------------------
// YOUR SOLUTION ENDS HERE -- YOU DON'T NEED TO ERASE THE REST

//#ifndef CONTEST

list_node * list(int x, list_node *next) {
  list_node *n = new list_node;
  n->data = x;
  n->next = next;
  return n;
}

tree_node * tree(int x, tree_node *left, tree_node *right) {
  tree_node *n = new tree_node;
  n->data = x;
  n->left = left;
  n->right = right;
  return n;
}

int main() {
  list_node *l = list(42, list(17, list(69, list(37, nullptr))));
  cout << "l = 42 -> 17 -> 69 -> 37" << endl;
  cout << "list_length(l) = " << list_length(l) << endl;
  cout << "list_minimum(l) = " << list_minimum(l) << endl;
  cout << "list_middle(l) = " << list_middle(l) << endl << endl;

  tree_node *t = tree(42,
                      tree(17,
                           tree(22, nullptr, tree(6, nullptr, nullptr)),
                           tree(4, nullptr, tree(78, nullptr, nullptr))),
                      tree(37,
                           nullptr,
                           tree(89, nullptr, nullptr)));
  cout << "t =    42" << endl;
  cout << "      /  \\" << endl;
  cout << "    17    37" << endl;
  cout << "   /  \\    \\" << endl;
  cout << " 22    4    89" << endl;
  cout << "   \\    \\" << endl;
  cout << "    6    78" << endl;
  cout << "tree_size(t) = " << tree_size(t) << endl;
  cout << "tree_sum_of_leaves(t) = " << tree_sum_of_leaves(t) << endl;
  cout << "tree_room_high(t, 3) = " << tree_room_high(t, 2) << endl;
}

//#endif
