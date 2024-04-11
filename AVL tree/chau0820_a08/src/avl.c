/*
 * your program signature
 */ 
 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "avl.h"

AVLNODE *new_node(RECORD data) {
  AVLNODE *np = (AVLNODE *) malloc(sizeof(AVLNODE));
  if (np) {
    np->data = data;
    np->height = 1;
    np->left = NULL;
    np->right = NULL;
  }
  return np;
}

int max(int a, int b) 
{
  return (a > b)? a : b;
}

int height(AVLNODE *np) {
  int h = 0;
  if (np) h = np->height;
  return h;
}

int balance_factor(AVLNODE* np) {
  int b = 0;
  if (np) b = height(np->left)-height(np->right);
  return b;
}

AVLNODE *rotate_right(AVLNODE *y) {
    
  AVLNODE *temp = y->left;
  y->left = temp->right;
  temp->right = y;

  y->height = max(height(y->left), height(y->right)) + 1;
  temp->height = max(height(temp->left), height(temp->right)) + 1;

  return temp;
}

AVLNODE *rotate_left(AVLNODE *x)
{
  AVLNODE *temp = x->right;
  x->right = temp->left;
  temp->left = x;

  x->height = max(height(x->left), height(x->right)) + 1;
  temp->height = max(height(temp->left), height(temp->right)) + 1;

  return temp;
}

void avl_insert(AVLNODE **rootp, RECORD data)
{ 
  // 1. Perform the normal BST insertion
  if (*rootp == NULL) {
    AVLNODE *np = (AVLNODE *) malloc(sizeof(AVLNODE));
      if (np) {
        np->data = data;
        np->height = 1;
        np->left = NULL;
        np->right = NULL;
      }
      *rootp = np;
  } else {
    AVLNODE *root = *rootp;
    
    if (strcmp(data.name, root->data.name) == 0 )
      return;
    else if (strcmp(data.name, root->data.name) < 0 ) {
      avl_insert(&root->left, data);
    } else {
      avl_insert(&root->right, data);
    }

    // 2. update height of this ancestor node
    root->height = 1 + max(height(root->left), height(root->right));
    
    // 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = balance_factor(root);
   
    // 4. rebalance if not balanced
    if (balance > 1) {
      if (balance_factor(root->left) >= 0) {
        // LL case
        *rootp = rotate_right(root);
      } else {
        // LR case
        root->left = rotate_left(root->left);
        *rootp = rotate_right(root);
      }
    } else if (balance < -1) {
      if (balance_factor(root->right) <= 0) {
        // RR case
        *rootp = rotate_left(root);
      } else {
        // RL case
        root->right = rotate_right(root->right);
        *rootp = rotate_left(root);
      }
    }
  } 
}

AVLNODE *extract_smallest_node(AVLNODE **rootp) {
  AVLNODE *p = *rootp, *parent = NULL;
  if (p) {
    while (p->left) {
      parent = p;
      p = p->left;
    }
    if (parent == NULL)
      *rootp = p->right;
    else
      parent->left = p->right;
    
    p->left = NULL;
    p->right = NULL;
  }
  return p;
}

void avl_delete(AVLNODE **rootp, char *name)
{
  AVLNODE *root = *rootp;
  AVLNODE *np;
  if (root == NULL) return;

  if (strcmp(name, root->data.name) == 0) {
    if (root->left == NULL && root->right == NULL) {
      free(root);
      *rootp = NULL;
    } else if (root->left != NULL && root->right == NULL) {
      np = root->left;
      free(root);
      *rootp = np;
    } else if (root->left == NULL && root->right != NULL) {
      np = root->right;
      free(root);
      *rootp = np;
    } else if (root->left != NULL && root->right != NULL) {
      np = extract_smallest_node(&root->right);
      np->left = root->left;
      np->right = root->right;
      free(root);
      *rootp = np;
    }
  } else {
    if (strcmp(name, root->data.name) < 0) {
      avl_delete(&root->left, name);
    } else {
      avl_delete(&root->right, name);
    }
  }

  // If the tree had only one node then return
  if (*rootp == NULL) return;
  root = *rootp;
    
  // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
  root->height = max(height(root->left), height(root->right)) + 1;

  // STEP 3: GET THE BALANCE FACTOR OF THIS NODE 
  int balance = balance_factor(root);

  // STEP 4: rebalance if not balanced
  if (balance > 1) {
    if (balance_factor(root->left) >= 0) {
      // LL case
      *rootp = rotate_right(root);
    } else {
      // LR case
      root->left = rotate_left(root->left);
      *rootp = rotate_right(root);
    }
  } else if (balance < -1) {
    if (balance_factor(root->right) <= 0) {
      // RR case
      *rootp = rotate_left(root);
    } else {
      // RL case
      root->right = rotate_right(root->right);
      *rootp = rotate_left(root);
    }
  }
}

AVLNODE *avl_search(AVLNODE *root, char *name) {
  AVLNODE *curr = root;

  while(curr) {
    if (strcmp(name, curr->data.name) == 0) {
      return curr;
    } else if (strcmp(name, curr->data.name) < 0) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  return NULL;
}

void clean_avl(AVLNODE **rootp) {
  AVLNODE *root = *rootp;
  if (root) {
    if (root->left)
      clean_avl(&root->left);
    if (root->right)
      clean_avl(&root->right);
    free(root);
  }
  *rootp = NULL;
}