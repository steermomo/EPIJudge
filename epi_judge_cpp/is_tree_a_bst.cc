#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

bool IsBinaryTreeBSTHelper(const unique_ptr<BinaryTreeNode<int>>& p, int max_val, int min_val) {
    if (p == nullptr) {
        return true;
    }
    if (p->data > max_val || p->data < min_val) {
        return false;
    }
    return IsBinaryTreeBSTHelper(p->left, p->data, min_val) && IsBinaryTreeBSTHelper(p->right, max_val, p->data);
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  int max_val = std::numeric_limits<int>::max(), min_val = std::numeric_limits<int>::min();
  return IsBinaryTreeBSTHelper(tree, max_val, min_val);
//  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
