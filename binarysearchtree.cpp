#include <iostream>
using namespace std;

/*
  Binary Search Tree implementation featuring inorder,preorded,postorder printing operations.
*/


struct node
{
  int data;
  node *left, *right;
};
typedef node *bst;

class bstree
{
public:
  bstree();
  int height();
  void insert(int x);
  int search(int x);
  int min();
  int max();
  void inorder();
  void preorder();
  void postorder();

private:
  int counter = 0;
  struct node
  {
    int data;
    node *left, *right;
  };
  node *root;
  int maxDepth(struct node *node)
  {
    if (node == nullptr)
      return 0;
    else
    {
      int lDepth = maxDepth(node->left);
      int rDepth = maxDepth(node->right);
      if (lDepth > rDepth)
        return (lDepth + 1);
      else
        return (rDepth + 1);
    }
  }
  int Search(node *root, int data)
  {
    int depth = 0;
    node *temp = new node;
    temp = root;
    // Run the loop until temp points to a nullptr pointer.
    while (temp != nullptr)
    {
      depth++;
      if (temp->data == data)
      {
        return depth;
      }
      // Shift pointer to left child.
      else if (temp->data > data)
        temp = temp->left;
      // Shift pointer to right child.
      else
        temp = temp->right;
    }
    return 0;
  }
  node *CreateNode(int data)
  {
    node *newnode = new node;
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
  }
  node *InsertIntoTree(node *root, int data)
  {
    // Create node using data from argument list.
    node *temp = CreateNode(data);
    node *t = new node;
    t = root;

    // If root is null, assign it to the node created.
    if (root == nullptr)
      root = temp;
    else
    {
      // Find the position for the new node to be inserted.
      while (t != nullptr)
      {
        if (t->data < data)
        {
          if (t->right == nullptr)
          {
            // If current node is nullptr then insert the node.
            t->right = temp;
            break;
          }
          // Shift pointer to the left.
          t = t->right;
        }

        else if (t->data > data)
        {
          if (t->left == nullptr)
          {
            // If current node is nullptr then insert the node.
            t->left = temp;
            break;
          }
          // Shift pointer to the left.
          t = t->left;
        }
      }
    }
    return root;
  }
  /*int iterativeSearch(struct node *root, int key) {
  // Traverse untill root reaches to dead end
  while (root != nullptr)
  {
      // pass right subtree as new tree
      if (key > root->data){
          root = root->right;
          ++counter;
        }
      // pass left subtree as new tree
      else if (key < root->data){
          root = root->left;
          ++counter;
        }
      else if(key == root->data){
          ++counter;
          return counter;// if the key is found return 1
     }
     else return 0;
  }
  return 0;
}*/
  /*node* find(node* t, int x){
    if (t == nullptr){
      counter = 0;
      return nullptr;
    }
    else if (t->data == x){
      ++counter;
      return t;
    }
    else if (t->data > x){
      ++counter;
      return find(t->left, x);
    }
    else {
      ++counter;
      return find(t->right, x);
    }
  }*/
  /*node* insert(int x, node* t){
    if(t == nullptr){
      t = new node;
      t->data = x;
      t->left = t->right = nullptr;
    }
    else if(x < t->data)
      t->left = insert(x, t->left);
    else if(x > t->data)
      t->right = insert(x, t->right);
    return t;
  }*/
  void inorder(node *t);
  void preorder(node *t);
  void postorder(node *t);
};

bstree::bstree()
{
  root = nullptr;
}

int bstree::height()
{
  return maxDepth(root);
}

void bstree::insert(int x)
{
  root = InsertIntoTree(root, x);
  // root = insert(x, root);
}

int bstree::search(int x)
{
  // iterativeSearch(root,x);
  // find(root,x);
  return Search(root, x);
  // int j = counter;
  // counter = 0;
  // return j;
}

int bstree::min()
{
  node *p = new node;
  p = root;
  if (p == nullptr)
    return 0;
  if (p->left == nullptr && p->right == nullptr)
    return p->data;
  while (p->left != nullptr)
    p = p->left;
  return p->data;
  delete p;
}

int bstree::max()
{
  node *p = new node;
  p = root;
  if (p == nullptr)
    return 0;
  if (p->left == nullptr && p->right == nullptr)
    return p->data;
  while (p->right != nullptr)
    p = p->right;
  return p->data;
  delete p;
}

void bstree::inorder()
{
  inorder(root);
}

void bstree::inorder(node *t)
{
  if (t != nullptr)
  {
    inorder(t->left);
    cout << t->data << ' ';
    inorder(t->right);
  }
}

void bstree::preorder()
{
  preorder(root);
}

void bstree::preorder(node *t)
{
  if (t != nullptr)
  {
    cout << t->data << ' ';
    preorder(t->left);
    preorder(t->right);
  }
}

void bstree::postorder()
{
  postorder(root);
}

void bstree::postorder(node *t)
{
  if (t != nullptr)
  {
    postorder(t->left);
    postorder(t->right);
    cout << t->data << ' ';
  }
}

int num1[400000];
int main()
{
  int N, M;
  int num;
  bstree tree;
  cout << "Type number of nodes to insert: " << endl;
  cin >> N;
  for (int i = 0; i < N; i++)
  {
    cin >> num;
    tree.insert(num);
  }
  cout << tree.height() << endl;
  cout << tree.min() << ' ' << tree.max() << endl;
  cin >> M;
  for (int i = 0; i < M; i++)
  {
    cin >> num;
    num1[i] = num;
  }
  for (int i = 0; i < M; i++)
  {
    cout << tree.search(num1[i]);
    if (i + 1 < M)
      cout << ' ';
  }
  cout << endl;
  tree.inorder();
  cout << "end" << endl;
  tree.preorder();
  cout << "end" << endl;
  tree.postorder();
  cout << "end" << endl;
}
