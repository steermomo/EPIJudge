#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  // 定义当前层的结点，用根节点初始化
  std::queue<BinaryTreeNode<int>*> curr_depth_nodes({tree.get()});
  vector<vector<int>> ret;

  while (!curr_depth_nodes.empty()) {
      // 定义下一层
      std::queue<BinaryTreeNode<int>*> next_depth_nodes;
      vector<int> this_level;
      // 遍历当前层
      while (!curr_depth_nodes.empty()) {
          auto curr = curr_depth_nodes.front();
          curr_depth_nodes.pop();
          if (curr) {
              this_level.emplace_back(curr->data);
              // 先左后右 保证按层顺序
              next_depth_nodes.emplace(curr->left.get());
              next_depth_nodes.emplace(curr->right.get());
          }
      }
      if (!this_level.empty()) {
          ret.emplace_back(this_level);
      }
      curr_depth_nodes = next_depth_nodes;
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
