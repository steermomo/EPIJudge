#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool CheckSymmetrice(const unique_ptr<BinaryTreeNode<int>> &left, const unique_ptr<BinaryTreeNode<int>> &right) {
    if (!left && !right) {
        return true;
    }
    if (!left || !right) {
        return false;
    }
    if (left->data != right->data) {
        return false;
    }
    return CheckSymmetrice(left->left, right->right) && CheckSymmetrice(left->right, right->left);
}
bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  if (!tree) {
      return true;
  }
  return CheckSymmetrice(tree->left, tree->right);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
