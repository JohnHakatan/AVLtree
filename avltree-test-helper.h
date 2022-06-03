/*
avl-test-helper.h
Copyright (c) Eromid (Olly) 2017

Friend of AVLTree class which contains functions only used in testing.
*/

#ifndef AVL_TEST_HELPER_H
#define AVL_TEST_HELPER_H

#include <algorithm>
#include <cmath>
#include <assert.h>

using std::max;

#include <iostream>
using std::cout;
using std::endl;

// A class template to test some of the internals of the AVL tree implementation.
// Is declared friend of AVLTree so has access to these.
template<typename K, typename V>
class test_helper
{
private:  
test_helper(){}
  // instantiation not needed (or allowed)
public:


  // Count the total number of nodes in the tree.
  static unsigned int count_nodes(const AVLTree<K, V>& tree)
  {
    if (tree.getRoot())
      return count_descendants(tree.getRoot());
    else
      return 0u;
  }

  // Check the tree is AVL.
  static bool is_avl(const AVLTree<K, V>& tree)
  {
   // try{
     // throw tree.root;
    //}catch(const AVLTree<K, V>& tree1){ return is_avl(tree1);}
 //   return false;
  return is_avl(tree.root);
   
  }

  // Check the tree's balance factors are correct.
  static bool valid_balance_factors(const AVLTree<K, V>& tree)
  {
  /*  try{
throw tree.root;
    }catch(const AVLTree<K, V>& tree1){
    return valid_balance_factors(tree1);
    }
    return false;*/
  //  const AVLTree<K, V>* tptr = (&tree);
    return valid_balance_factors(tree.root, tree);
  }

  // Test the functions in this class.
  static void test_meta_functions()
  {
    {
      // Counting nodes
      AVLTree<K, V> tree;
      assert(count_nodes(tree) == 0);  // Empty tree should have 0 nodes.
      tree.AVLInsert( 1.0);
           

      assert(count_nodes(tree) == 1);  // one node inserted
      tree.AVLInsert( 1.0);
      assert(count_nodes(tree) == 1);  // same node inserted twice
      tree.AVLInsert( 2.0);
      assert(count_nodes(tree) == 2);  // second unique node inserted
      tree.AVLRemoveVal(3);
      assert(count_nodes(tree) == 2);  // non existent node removed
      tree.AVLRemoveVal(1.0);
      assert(count_nodes(tree) == 1);  // one node removed
      tree.AVLRemoveVal(2.0);
      assert(count_nodes(tree) == 0);
    }
    {
      // subtree height
      AVLTree<K, V> tree;
      assert(subtree_height(tree.root) == 0);  // root is null, height is 0.
      tree.AVLInsert( 5.0);
      assert(subtree_height(tree.root) == 1);  // single node height should be 1.
      tree.AVLInsert( 8.0);
      assert(subtree_height(tree.root) == 2);  // height should be 2; root has a single right child
      tree.AVLInsert( 3.0);
      assert(subtree_height(tree.root) == 2);  // height should be 2; root has a left and right child
      tree.AVLInsert( 7.0);
      assert(subtree_height(tree.root) == 3);  // height should be 2; root has a left and right child    
    }
  }

private:
  static bool is_avl(const AVLNode<K, V>*  root_node)
  {
   
    if (!root_node) return true;  // Base case; an empty tree is always AVL.
    bool left_is_avl, right_is_avl;
    unsigned int left_height, right_height;
    left_is_avl = is_avl(root_node->getLeft());
    left_height = subtree_height(root_node->getLeft());
    right_is_avl = is_avl(root_node->getRight());
    right_height = subtree_height(root_node->getRight());
    //if (root_node->parent.lock() == nullptr)
    //{
     // if (DBG) { cout << "left subtree: " << left_height << " | right subtree: " << right_height << endl; }
      //if (DBG) { cout << "left_is_avl: " << left_is_avl << " | right_is_avl: " << right_is_avl << endl; }
   // }
    if(! (left_is_avl && right_is_avl && (abs((int)left_height - (int)right_height) <= 1u)))
    {
       cout<<root_node->getData()<<"hereeeee"<<"left_height:"<<left_height<<"right:"<<right_height<<endl;
      return false;
    }
    return true;
  }


  static bool valid_balance_factors(const  AVLNode<K, V>* node ,const  AVLTree<K, V>& tree)
  {
    if (!node) return true;
  //  if (DBG) { cout << "left_height: " << subtree_height(node->getLeft()) << " | right_height: "
    //    << subtree_height(node->getRight()) << " | balance_factor: " << static_cast<int>(node->balance_factor) << endl; }
    cout<<node->getData()<<endl;
    cout << "left_height: " << subtree_height(node->getLeft()) << " | right_height: "
      << subtree_height(node->getRight()) << " | balance_factor: " << static_cast<int>(node->balanceFactorNode(tree)) << endl;
      if(node->getLeft())cout<<"left "<<node->getLeft()->getHeight()<<endl;
      if(node->getRight())cout<<"right "<<node->getRight()->getHeight()<<endl;
     //if(node->getLeft())cout<<node->getLeft()->getHeight()<<"kkkkklllkkkkk"<<endl;

   return ((subtree_height(node->getLeft()) - subtree_height(node->getRight())) == node->balanceFactorNode(tree))
            && valid_balance_factors(node->getLeft(),tree) && valid_balance_factors(node->getRight(),tree);
  //  return (((node->getLeft())->getHeight() - (node->getRight())->getHeight()) == node->balanceFactorNode(tree))
   //        && valid_balance_factors(node->getLeft(),tree) && valid_balance_factors(node->getRight(),tree);
  }

  static unsigned int count_descendants(const AVLNode<K, V>* node)
  {
    unsigned int left_count = node->getLeft() ? count_descendants(node->getLeft()) : 0;
    unsigned int right_count = node->getRight() ? count_descendants(node->getRight()) : 0;
    return 1u + left_count + right_count;
  }

  static unsigned int subtree_height(const AVLNode<K, V>* node)
  {
    if (!node) return 0u;  // no subtree root -> height = 0.
    unsigned int left_height, right_height;
    left_height = right_height = 0u;
    left_height = subtree_height(node->getLeft());
    right_height = subtree_height(node->getRight());
    return 1 + max(left_height, right_height);
  }
};

#endif
