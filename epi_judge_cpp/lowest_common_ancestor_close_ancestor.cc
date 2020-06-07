#include <memory>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  // TODO - you fill in here.
  std::unordered_set<BinaryTreeNode<int>*> node_set;
  BinaryTreeNode<int> *p0 = node0.get(), *p1 = node1.get();
  while (p0 && p1) {
      auto iter = node_set.find(p0);
      if (iter != node_set.end()) {
          return *iter;
      }
      node_set.insert(p0);
      p0 = p0->parent;

      iter = node_set.find(p1);
      if (iter != node_set.end()) {
          return *iter;
      }
      node_set.insert(p1);
      p1 = p1->parent;
  }
  auto *residual = p0 == nullptr ? p1 : p0;
  while (residual != nullptr) {
      auto iter = node_set.find(residual);
      if (iter != node_set.end()) {
          return *iter;
      }
      residual = residual->parent;
  }
  return nullptr;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_close_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
