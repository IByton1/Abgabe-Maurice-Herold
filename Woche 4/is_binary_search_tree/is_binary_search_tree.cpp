// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>

using namespace std;

struct Binary_Tree_Node {
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

bool is_binary_search_tree(const Binary_Tree_Node *node) {
  return check_bst(node, nullptr, nullptr);
}

bool check_bst(const Binary_Tree_Node *node,
               const Binary_Tree_Node *min_node,
               const Binary_Tree_Node *max_node) {
  if (node == nullptr) {
    return true;
  }

  if (min_node != nullptr && node->data <= min_node->data) {
    return false;
  }

  if (max_node != nullptr && node->data > max_node->data) {
    return false;
  }

  return check_bst(node->left, min_node, node) &&
         check_bst(node->right, node, max_node);
}



int main() {
  // TODO: Thoroughly test function "is_binary_search_tree" 
  // (include also duplicate values in the tests).
  // Test cases for is_binary_search_tree

// Test case 1: nullptr
assert(is_binary_search_tree(nullptr) == true);

// Test case 2: One node
Binary_Tree_Node n2{2, nullptr, nullptr};
assert(is_binary_search_tree(&n2) == true);

// Test case 3: Two nodes, left child
Binary_Tree_Node n3{3, &n2, nullptr};
assert(is_binary_search_tree(&n3) == true);

// Test case 4: Two nodes, right child
Binary_Tree_Node n1{1, nullptr, &n2};
assert(is_binary_search_tree(&n1) == true);

// Test case 5: Three nodes, left child
Binary_Tree_Node n4{4, &n3, nullptr};
assert(is_binary_search_tree(&n4) == true);

// Test case 6: Three nodes, right child
Binary_Tree_Node n0{0, nullptr, &n1};
assert(is_binary_search_tree(&n0) == true);

// Test case 7: Three nodes, invalid BST
Binary_Tree_Node n5{5, &n2, &n3};
assert(is_binary_search_tree(&n5) == false);

// Test case 8: Four nodes, valid BST
Binary_Tree_Node n6{6, &n4, &n5};
assert(is_binary_search_tree(&n6) == true);

// Test case 9: Four nodes, invalid BST
Binary_Tree_Node n7{7, &n5, &n6};
assert(is_binary_search_tree(&n7) == false);

// Test case 10: Five nodes, valid BST
Binary_Tree_Node n8{8, &n6, &n7};
assert(is_binary_search_tree(&n8) == true);

// Test case 11: Five nodes, invalid BST
Binary_Tree_Node n9{9, &n8, &n7};
assert(is_binary_search_tree(&n9) == false);


}
/*************** end assignment ***************/
