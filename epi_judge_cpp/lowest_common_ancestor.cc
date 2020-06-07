#include <memory>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;
struct Status {
    int num_target_nodes;
    BinaryTreeNode<int>* ancestor;
};
Status LCAHelper(const unique_ptr<BinaryTreeNode<int>>& tree,
                 const unique_ptr<BinaryTreeNode<int>>& node0,
                 const unique_ptr<BinaryTreeNode<int>>& node1) {
    if (tree == nullptr) {
        return {0, nullptr};
    }
    // 查找左子树
    auto left_result = LCAHelper(tree->left, node0, node1);
    if (left_result.num_target_nodes == 2){
        return left_result;
    }
    // 查找右子树
    auto right_result = LCAHelper(tree->right, node0, node1);
    if (right_result.num_target_nodes == 2) {
        return right_result;
    }
    // 如果当前结点或左右子树的目标和为2 则当前为目标结点
    int num_target_nodes = left_result.num_target_nodes +
            right_result.num_target_nodes +
            (tree == node0) + (tree == node1);
    return {num_target_nodes, num_target_nodes == 2 ? tree.get() : nullptr};
}
BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& tree,
                         const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  // TODO - you fill in here.
  return LCAHelper(tree, node0, node1).ancestor;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(tree, node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
