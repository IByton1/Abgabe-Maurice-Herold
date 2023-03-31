// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <iostream>
#include <cassert>
#include <limits>
#include <ostream>

using namespace std;

struct Binary_Tree_Node
{
  int data;
  Binary_Tree_Node *left;
  Binary_Tree_Node *right;
};

/************** begin assignment **************/
// Implement a function to check if a binary tree is a binary search tree (BST).
// A binary search tree satisfies the condition:
// left->data <= current->data < right->data.
// More precisely, the condition is that all left nodes must be less than or
// equal to the current node, which must be less than all the right nodes.
//
// Let's state again clearly the properties for a binary search tree:
// - The left subtree of a node contains only nodes with keys lesser than the
//   node's key.
// - The right subtree of a node contains only nodes with keys greater than the
//   node's key.
// - The left and right subtree each must also be a binary search tree.
//
// Be careful with duplicate values:
//    20                  20
//   /    valid BST         \    invalid BST
// 20                       20
//
// Optimal: O(n) time, if binary tree is balanced O(log n) space,
// worst case O(n) space
// --> It's challenging to do it optimal although there is not much code ...
// Try to solve it somehow.
//
// Before you start coding the function "is_binary_search_tree", write test
// cases in the main function to test the "is_binary_search_tree" function.
// Start with simple tests (like nullptr, one node, two nodes, three nodes)
// before writing more complicated tests.
// The style of writing tests before actual coding is called "Test-driven
// development" (TDD). You have indirectly familiarized yourself with it in the
// first exercises of this course, now you can try TDD yourself.
// (If you need an idea how to start writing tests, take a look at the main
// function in "is_symmetric.cpp".)

// write a helper function if you need to
// TODO: write code here

// Helper function to check if a binary tree is a binary search tree (BST)
// Recursively checks if the current node's data falls within the given range
// (inclusive on the left, exclusive on the right) of minimum and maximum values.
// Returns true if the current node is within range and the left and right subtrees
// are also binary search trees.
bool is_binary_search_tree_helper(const Binary_Tree_Node *node, int min_val, int max_val)
{
  if (node == nullptr)
  {
    // If the current node is null, it is a valid binary search tree.
    return true;
  }

  if (node->data <= min_val || node->data > max_val)
  {
    // If the current node's data is not within range, it is not a valid binary search tree.
    return false;
  }

  // Recursively check the left and right subtrees with updated range.
  // The left subtree should have a range of (min_val, node->data - 1),
  // and the right subtree should have a range of (node->data, max_val).
  return is_binary_search_tree_helper(node->left, min_val, node->data - 1) && is_binary_search_tree_helper(node->right, node->data, max_val);
}

// Function to check if a binary tree is a binary search tree (BST).
// Sets the initial range for the root node to be the largest and smallest integers, respectively.
// Calls the helper function to recursively check if the tree is a binary search tree.
bool is_binary_search_tree(const Binary_Tree_Node *node)
{
  int min_val = INT_MIN; // The smallest possible integer
  int max_val = INT_MAX; // The largest possible integer

  return is_binary_search_tree_helper(node, min_val, max_val);
}

int main()
{
  // Test empty tree
  assert(is_binary_search_tree(nullptr) == true);

  // Test single node tree
  Binary_Tree_Node *root = new Binary_Tree_Node{10, nullptr, nullptr};
  assert(is_binary_search_tree(root) == true);

  // Test two node tree
  Binary_Tree_Node *left_child = new Binary_Tree_Node{5, nullptr, nullptr};
  Binary_Tree_Node *right_child = new Binary_Tree_Node{15, nullptr, nullptr};
  root->left = left_child;
  root->right = right_child;
  assert(is_binary_search_tree(root) == true);

  // Test three node tree
  Binary_Tree_Node *left_left_child = new Binary_Tree_Node{3, nullptr, nullptr};
  Binary_Tree_Node *left_right_child = new Binary_Tree_Node{7, nullptr, nullptr};
  left_child->left = left_left_child;
  left_child->right = left_right_child;
  assert(is_binary_search_tree(root) == true);

  // Test four node tree with duplicate values
  Binary_Tree_Node *right_left_child = new Binary_Tree_Node{13, nullptr, nullptr};
  Binary_Tree_Node *right_right_child = new Binary_Tree_Node{20, nullptr, nullptr};
  right_child->left = right_left_child;
  right_child->right = right_right_child;
  Binary_Tree_Node *right_left_child_duplicate = new Binary_Tree_Node{13, nullptr, nullptr};
  right_left_child->right = right_left_child_duplicate;
  assert(is_binary_search_tree(root) == false);

  // Test case with a balanced binary search tree with 7 nodes
  //        10
  //     /      \
  //    5        15
  //   / \      /  \
  //  3   7    13   20
  Binary_Tree_Node *root2 = new Binary_Tree_Node{10, nullptr, nullptr};
  Binary_Tree_Node *left_child2 = new Binary_Tree_Node{5, nullptr, nullptr};
  Binary_Tree_Node *right_child2 = new Binary_Tree_Node{15, nullptr, nullptr};
  Binary_Tree_Node *left_left_child2 = new Binary_Tree_Node{3, nullptr, nullptr};
  Binary_Tree_Node *left_right_child2 = new Binary_Tree_Node{7, nullptr, nullptr};
  Binary_Tree_Node *right_left_child2 = new Binary_Tree_Node{13, nullptr, nullptr};
  Binary_Tree_Node *right_right_child2 = new Binary_Tree_Node{20, nullptr, nullptr};
  root2->left = left_child2;
  root2->right = right_child2;
  left_child2->left = left_left_child2;
  left_child2->right = left_right_child2;
  right_child2->left = right_left_child2;
  right_child2->right = right_right_child2;
  assert(is_binary_search_tree(root2) == true);

  // Test case with an unbalanced binary search tree with 10 nodes
  //        10
  //         \
  //          20
  //           \
  //            30
  //             \
  //              40
  //               \
  //                50
  //                 \
  //                  60
  //                   \
  //                    70
  Binary_Tree_Node *root3 = new Binary_Tree_Node{10, nullptr, nullptr};
  Binary_Tree_Node *right_child3 = new Binary_Tree_Node{20, nullptr, nullptr};
  Binary_Tree_Node *right_right_child3 = new Binary_Tree_Node{30, nullptr, nullptr};
  Binary_Tree_Node *right_right_right_child3 = new Binary_Tree_Node{40, nullptr, nullptr};
  Binary_Tree_Node *right_right_right_right_child3 = new Binary_Tree_Node{50, nullptr, nullptr};
  Binary_Tree_Node *right_right_right_right_right_child3 = new Binary_Tree_Node{60, nullptr, nullptr};
  Binary_Tree_Node *right_right_right_right_right_right_child3 = new Binary_Tree_Node{70, nullptr, nullptr};
  root3->right = right_child3;
  right_child3->right = right_right_child3;
  right_right_child3->right = right_right_right_child3;
  right_right_right_child3->right = right_right_right_right_child3;
  right_right_right_right_child3->right = right_right_right_right_right_child3;
  right_right_right_right_right_child3->right = right_right_right_right_right_right_child3;
  assert(is_binary_search_tree(root3) == true);

  // Test case with an unbalanced binary search tree with 7 nodes, one node violates BST property
  //      5
  //    /   \
  //   3     10
  //  / \   /  \
  // 1   7 11  12

  Binary_Tree_Node *root4 = new Binary_Tree_Node{5, nullptr, nullptr};
  Binary_Tree_Node *left_child4 = new Binary_Tree_Node{3, nullptr, nullptr};
  Binary_Tree_Node *right_child4 = new Binary_Tree_Node{10, nullptr, nullptr};
  Binary_Tree_Node *left_left_child4 = new Binary_Tree_Node{1, nullptr, nullptr};
  Binary_Tree_Node *left_right_child4 = new Binary_Tree_Node{7, nullptr, nullptr};
  Binary_Tree_Node *right_left_child4 = new Binary_Tree_Node{11, nullptr, nullptr};
  Binary_Tree_Node *right_right_child4 = new Binary_Tree_Node{12, nullptr, nullptr};
  root4->left = left_child4;
  root4->right = right_child4;
  left_child4->left = left_left_child4;
  left_child4->right = left_right_child4;
  right_child4->left = right_left_child4;
  right_child4->right = right_right_child4;
  assert(is_binary_search_tree(root4) == false);

  // Test case with a balanced binary search tree with 10 nodes, one node violates BST property
  //        10
  //      /    \
  //     5      15
  //    / \     / \
  //   3   7   13 18
  //              / \
  //             17 20
  //            /
  //           12
  Binary_Tree_Node *root5 = new Binary_Tree_Node{10, nullptr, nullptr};
  Binary_Tree_Node *left_child5 = new Binary_Tree_Node{5, nullptr, nullptr};
  Binary_Tree_Node *right_child5 = new Binary_Tree_Node{15, nullptr, nullptr};
  Binary_Tree_Node *left_left_child5 = new Binary_Tree_Node{3, nullptr, nullptr};
  Binary_Tree_Node *left_right_child5 = new Binary_Tree_Node{7, nullptr, nullptr};
  Binary_Tree_Node *right_left_child5 = new Binary_Tree_Node{13, nullptr, nullptr};
  Binary_Tree_Node *right_right_child5 = new Binary_Tree_Node{18, nullptr, nullptr};
  Binary_Tree_Node *right_right_left_child5 = new Binary_Tree_Node{17, nullptr, nullptr};
  Binary_Tree_Node *right_right_right_child5 = new Binary_Tree_Node{20, nullptr, nullptr};
  Binary_Tree_Node *right_right_left_left_child5 = new Binary_Tree_Node{12, nullptr, nullptr};
  root5->left = left_child5;
  root5->right = right_child5;
  left_child5->left = left_left_child5;
  left_child5->right = left_right_child5;
  right_child5->left = right_left_child5;
  right_child5->right = right_right_child5;
  right_right_child5->left = right_right_left_child5;
  right_right_child5->right = right_right_right_child5;
  right_right_left_child5->left = right_right_left_left_child5;
  assert(is_binary_search_tree(root5) == false);

  cout << "all tests passed" << endl;

  return 0;
}

/*************** end assignment ***************/
