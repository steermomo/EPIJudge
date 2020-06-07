#include <set>
#include <stdexcept>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

int Length(shared_ptr<ListNode<int>> L) {
    int  length = 0;
    while (L) {
        ++length;
        L = L->next;
    }
    return length;
}
void AdvanceByK(shared_ptr<ListNode<int>> *L, int k) {
    while (k--) {
        (*L) = (*L)->next;
    }
}
shared_ptr<ListNode<int>> OverlappingNoCycleLists(
        shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
    // TODO - you fill in here.
    int l0_len = Length(l0), l1_len = Length(l1);  // 计算长度
    AdvanceByK(l0_len > l1_len ? &l0 : &l1, abs(l0_len - l1_len)); // 将较长的链表头前进，直至两个链表长度相等
    while (l0 && l0 != l1) {
        l0 = l0->next;
        l1 = l1->next;
    }
    return l0;
}

shared_ptr<ListNode<int>> HasCycle(const shared_ptr<ListNode<int>>& head) {
    // TODO - you fill in here.
    shared_ptr<ListNode<int>> slow = head, fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) { // find cycle
            // 计算圈长
            int cycle_len = 0;
            do {
                ++cycle_len;
                fast = fast->next;
            }while (slow != fast);
            // cycle 指针先前进cycle len
            auto cycle_advance_iter = head;
            while (cycle_len--) {
                cycle_advance_iter = cycle_advance_iter->next;
            }
            // 两指针同时前进
            auto iter = head;
            while (iter != cycle_advance_iter) {
                iter = iter->next;
                cycle_advance_iter = cycle_advance_iter->next;
            }
            return iter;
        }
    }
    return nullptr;
}

int Distance(shared_ptr<ListNode<int>> a, shared_ptr<ListNode<int>> b) {
    int dis = 0;
    while (a != b) {
        a = a->next;
        ++dis;
    }
    return dis;
}
shared_ptr<ListNode<int>> OverlappingLists(shared_ptr<ListNode<int>> l0,
                                           shared_ptr<ListNode<int>> l1) {
  // TODO - you fill in here.
  auto root0 = HasCycle(l0), root1 = HasCycle(l1);
  if (!root0 && !root1) {
      // 两个都无环
      return OverlappingNoCycleLists(l0, l1);
  }
  else if ((!root0 && root1) || (root0 && !root1)) {
      // 只有一个有环，肯定不会相交
      return nullptr;
  }

  auto temp = root0;
  do {
      temp = temp->next;
  } while (temp != root0 && temp != root1);

  if (temp != root1) {
      // 两个都有环，且环不相交
      return nullptr;
  }

  // 类似无环判断时判断两链表相交，需要先计算出距离
  int stem0_length = Distance(l0, root0), stem1_length = Distance(l1, root1);  // 计算两个链表到各自环的距离
  AdvanceByK(stem0_length > stem1_length ? &l0 : &l1, abs(stem0_length - stem1_length));

  while (l0 != l1 && l0 != root0 && l1 != root1) {
      l0 = l0->next;
      l1 = l1->next;
  }

  if (l0 == l1) {
      // l1 == l2 说明在入环之前两个指针相遇，相交点在环外
      return l1;
  }
  else {
      // 另外两种情况下，返回任意一个入环点均可
      return root0;
  }
  
  return nullptr;
}
void OverlappingListsWrapper(TimedExecutor& executor,
                             shared_ptr<ListNode<int>> l0,
                             shared_ptr<ListNode<int>> l1,
                             shared_ptr<ListNode<int>> common, int cycle0,
                             int cycle1) {
  if (common) {
    if (!l0) {
      l0 = common;
    } else {
      auto it = l0;
      while (it->next) {
        it = it->next;
      }
      it->next = common;
    }

    if (!l1) {
      l1 = common;
    } else {
      auto it = l1;
      while (it->next) {
        it = it->next;
      }
      it->next = common;
    }
  }

  if (cycle0 != -1 && l0) {
    auto last = l0;
    while (last->next) {
      last = last->next;
    }
    auto it = l0;
    while (cycle0-- > 0) {
      if (!it) {
        throw std::runtime_error("Invalid input data");
      }
      it = it->next;
    }
    last->next = it;
  }

  if (cycle1 != -1 && l1) {
    auto last = l1;
    while (last->next) {
      last = last->next;
    }
    auto it = l1;
    while (cycle1-- > 0) {
      if (!it) {
        throw std::runtime_error("Invalid input data");
      }
      it = it->next;
    }
    last->next = it;
  }

  std::set<shared_ptr<ListNode<int>>> common_nodes;
  auto it = common;
  while (it && common_nodes.count(it) == 0) {
    common_nodes.insert(it);
    it = it->next;
  }

  auto result = executor.Run([&] { return OverlappingLists(l0, l1); });

  if (!((common_nodes.empty() && result == nullptr) ||
        common_nodes.count(result) > 0)) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0",     "l1",
                                       "common",   "cycle0", "cycle1"};
  return GenericTestMain(args, "do_lists_overlap.cc", "do_lists_overlap.tsv",
                         &OverlappingListsWrapper, DefaultComparator{},
                         param_names);
}
