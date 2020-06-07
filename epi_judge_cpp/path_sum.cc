#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
bool HasPathSumHelper(const unique_ptr<BinaryTreeNode<int>>& tree,
                        int current_sum, int target) {
    if (!tree) {
        return false;
    }
    current_sum += tree->data;
    if (!tree->left && !tree->right) {
        if (current_sum == target) {
            return true;
        } else {
            return false;
        }
    }
    return HasPathSumHelper(tree->left, current_sum, target) || HasPathSumHelper(tree->right, current_sum, target);
}
bool HasPathSum(const unique_ptr<BinaryTreeNode<int>>& tree,
                int remaining_weight) {
  // TODO - you fill in here.
  return HasPathSumHelper(tree, 0, remaining_weight);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "remaining_weight"};
  return GenericTestMain(args, "path_sum.cc", "path_sum.tsv", &HasPathSum,
                         DefaultComparator{}, param_names);
}
