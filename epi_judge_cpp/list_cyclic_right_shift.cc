#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

int Length(shared_ptr<ListNode<int>> L) {
    int length = 0;
    while (L) {
        ++length;
        L = L->next;
    }
    return length;
}
shared_ptr<ListNode<int>> CyclicallyRightShiftList(shared_ptr<ListNode<int>> L,
                                                   int k) {
  // TODO - you fill in here.
  int list_len = Length(L);
  if (list_len == 0) {
      return nullptr;
  }
  k = k % list_len; // > len 次的平移等价于在n内平移
  auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
  auto fast = dummy_head, slow = dummy_head; // 均指向前结点
  while (k--) {
      fast = fast->next;
  }
  while (fast->next) {
      fast = fast->next;
      slow = slow->next;
  }
  fast->next = dummy_head->next; // 尾部应该指向原来的头部
  dummy_head->next = slow->next; // 链表头更新为指向后k个元素的首结点
  slow->next = nullptr; // 中间断开
  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(
      args, "list_cyclic_right_shift.cc", "list_cyclic_right_shift.tsv",
      &CyclicallyRightShiftList, DefaultComparator{}, param_names);
}
