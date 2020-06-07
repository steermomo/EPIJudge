#include <memory>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;
using test_framework::BinaryTreeSerializationTrait;
template <typename T>
struct BinaryTreeNode {
  T data;
  unique_ptr<BinaryTreeNode<T>> left, right;
  BinaryTreeNode<T>* next = nullptr;  // Populates this field.

  explicit BinaryTreeNode(T data) : data(data){};
};

void ConstructRightSiblingBak(BinaryTreeNode<int>* tree) {
  // TODO - you fill in here.
  if (!tree) {
      return;
  }
  std::vector<BinaryTreeNode<int>*> curr_level, next_level;
  curr_level.push_back(tree);
  while (!curr_level.empty()) {
      for (int i = 0; i < curr_level.size() - 1; ++i) {
          curr_level[i]->next = curr_level[i+1];
      }
      for (auto each: curr_level) {
          if (each->left.get() != nullptr) {
              next_level.push_back(each->left.get());
              next_level.push_back(each->right.get());
          }
      }
      curr_level = next_level;
      next_level.clear();
  }
  return;
}

void SetRightSibling(BinaryTreeNode<int>* iter) {
    // 传入的是最左侧的结点
    while (iter) {
        iter->left->next = iter->right.get();
        if (iter->next) {
            iter->right->next = iter->next->left.get();
        }
        iter = iter->next;
    }
}

void ConstructRightSibling(BinaryTreeNode<int>* tree) {
    // TODO - you fill in here.
    auto left_start = tree; // 沿着左侧向下
    while (left_start && left_start->left.get()) {
        SetRightSibling(left_start);
        left_start = left_start->left.get();
    }
    return;
}

namespace test_framework {
template <>
struct SerializationTrait<unique_ptr<BinaryTreeNode<int>>>
    : BinaryTreeSerializationTrait<unique_ptr<BinaryTreeNode<int>>, false> {};
}  // namespace test_framework

std::vector<std::vector<int>> ConstructRightSiblingWrapper(
    TimedExecutor& executor, unique_ptr<BinaryTreeNode<int>>& tree) {
  executor.Run([&] { ConstructRightSibling(tree.get()); });

  std::vector<std::vector<int>> result;
  auto level_start = tree.get();
  while (level_start) {
    result.emplace_back();
    auto level_iter = level_start;
    while (level_iter) {
      result.back().push_back(level_iter->data);
      level_iter = level_iter->next;
    }
    level_start = level_start->left.get();
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree"};
  return GenericTestMain(
      args, "tree_right_sibling.cc", "tree_right_sibling.tsv",
      &ConstructRightSiblingWrapper, DefaultComparator{}, param_names);
}
