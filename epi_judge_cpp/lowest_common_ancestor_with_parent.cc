#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  // TODO - you fill in here.
  std::vector<BinaryTreeNode<int>*> path0, path1;
  BinaryTreeNode<int> *p0 = node0.get(), *p1 = node1.get();
  // 查找node0的路径
  while (p0) {
      path0.push_back(p0);
      p0 = p0->parent;
  }
  // 查找node1的路径
  while (p1) {
      path1.push_back(p1);
      p1 = p1->parent;
  }
  // 对齐根结点
  int idx0 = path0.size() - 1, idx1 = path1.size() - 1;
  while(idx0 >= 0 && idx1 >= 0) {
      if (path0[idx0] != path1[idx1]) {
          break;
      }
      --idx0, --idx1;
  }
  return path0[idx0+1];
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
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
