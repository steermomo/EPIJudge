#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> MergeTwoSortList(shared_ptr<ListNode<int>> L0, shared_ptr<ListNode<int>> L1) {
    auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});

    auto ptr = dummy_head;
    while (L0 && L1) {
        if (L0->data < L1->data) {
            ptr->next = L0;
            L0 = L0->next;
        } else {
            ptr->next = L1;
            L1 = L1->next;
        }
        ptr = ptr->next;
    }
    if (L0 == nullptr) {
        ptr->next = L1;
    } else {
        ptr->next = L0;
    }
    return dummy_head->next;
}

shared_ptr<ListNode<int>> StableSortList(shared_ptr<ListNode<int>> L) {
  // TODO - you fill in here.
  if (L == nullptr || L->next == nullptr) {
      return L;
  }
  // 用快慢指针找到链表中点
  shared_ptr<ListNode<int>> pre_slow = nullptr, slow = L, fast = L;
  while (fast && fast->next) {
      pre_slow = slow;
      fast = fast->next->next;
      slow = slow->next;
  }
  // 断开链表
  pre_slow->next = nullptr;
  // 递归归并排序
  return MergeTwoSortList(StableSortList(L), StableSortList(slow));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "sort_list.cc", "sort_list.tsv", &StableSortList,
                         DefaultComparator{}, param_names);
}
