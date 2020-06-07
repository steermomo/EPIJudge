#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

// Assumes L has at least k nodes, deletes the k-th last node in L.
shared_ptr<ListNode<int>> RemoveKthLast(const shared_ptr<ListNode<int>>& L,
                                        int k) {
  // TODO - you fill in here.
  // 头结点为了方便处理删除
  auto dummy_head = make_shared<ListNode<int>>(0, L);
  // 双指针
  auto fast = L, slow = dummy_head;
  // 将fast与slow的间距设为k+1 (slow指向前结点，所以多了1)
  while (k--) {
      fast = fast->next;
  }
  while (fast) {
      fast = fast->next;
      slow = slow->next;
  }
  slow->next = slow->next->next;
  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(args, "delete_kth_last_from_list.cc",
                         "delete_kth_last_from_list.tsv", &RemoveKthLast,
                         DefaultComparator{}, param_names);
}
