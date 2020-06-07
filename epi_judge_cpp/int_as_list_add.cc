#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> AddTwoNumbers(shared_ptr<ListNode<int>> L1,
                                        shared_ptr<ListNode<int>> L2) {
  // TODO - you fill in here.
  shared_ptr<ListNode<int>> dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
  auto iter = dummy_head;
  int carry = 0;
  // 同时前进两个链表指针
  while (L1 && L2) {
      int val = L1->data + L2->data + carry;
      if (val > 9) {
          val = val - 10;
          carry = 1;
      }
      else {
          carry = 0;
      }
      // 创建新结点
      iter->next = make_shared<ListNode<int>>(ListNode<int>{val, nullptr});
      iter = iter->next;
      L1 = L1->next;
      L2 = L2->next;
  }
  // 处理尾部剩余数值
  auto tail = L1 ? L1 : L2;
  iter->next = tail; // iter指向前结点
  while (carry) {
      if (iter->next == nullptr) {
          iter->next = make_shared<ListNode<int>>(ListNode<int>{carry, nullptr});
          carry = 0;
      }
      else if (iter->next->data >= 9) {
              iter->next->data = 0;
              carry = 1;
              iter = iter->next;
      }
      else {
          iter->next->data += carry;
          carry = 0;
      }
  }
  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "int_as_list_add.cc", "int_as_list_add.tsv",
                         &AddTwoNumbers, DefaultComparator{}, param_names);
}
