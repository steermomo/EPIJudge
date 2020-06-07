#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

struct BalancedSatusWithHeight {
    bool balanced;
    int height;
};
BalancedSatusWithHeight CheckBalanced(
        const unique_ptr<BinaryTreeNode<int>> & tree ) {
    if (tree == nullptr) {
        return {true, -1};
    }
    auto left_result = CheckBalanced(tree->left);
    if (!left_result.balanced) {
        return {false, 0};
    }
    auto right_result = CheckBalanced(tree->right);
    if (!right_result.balanced) {
        return {false, 0};
    }
    bool is_balanced = abs(left_result.height - right_result.height) <= 1;
    int height = std::max(left_result.height, right_result.height) + 1;
    return {is_balanced, height};
}
bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  return CheckBalanced(tree).balanced;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
