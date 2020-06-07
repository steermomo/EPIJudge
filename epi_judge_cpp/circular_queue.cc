#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
class Queue {
 public:
  Queue(size_t capacity) {
      data = new std::vector<int>(capacity);
      head = 0, tail = 0;
      cap = capacity;
  }
  void _Resize() {
      int new_cap = data->size() * 2 + 1;
      auto new_field = new std::vector<int>(new_cap);
      int n_idx = 0;
      while(head != tail) {
          (*new_field)[n_idx++] = (*data)[head];
          head = (head + 1) % cap;
      }
      head = 0;
      tail = n_idx;
      delete data;
      data = new_field;
      cap = new_cap;
  }
  void Enqueue(int x) {
    // TODO - you fill in here.
    if ((tail + 1) % cap == head) {
        _Resize();
    }
    (*data)[tail] = x;
    tail = (tail + 1) % cap;
    return;
  }
  int Dequeue() {
    // TODO - you fill in here.
    int c_val = (*data)[head];
    head = (head + 1) % cap;
    return c_val;
  }
  int Size() const {
    // TODO - you fill in here.
    return (tail + cap - head) % cap;
    return 0;
  }

private:
    std::vector<int>* data;
    int head, tail;
    int cap;
};
struct QueueOp {
  enum class Operation { kConstruct, kDequeue, kEnqueue, kSize } op;
  int argument;

  QueueOp(const std::string& op_string, int arg) : argument(arg) {
    if (op_string == "Queue") {
      op = Operation::kConstruct;
    } else if (op_string == "dequeue") {
      op = Operation::kDequeue;
    } else if (op_string == "enqueue") {
      op = Operation::kEnqueue;
    } else if (op_string == "size") {
      op = Operation::kSize;
    } else {
      throw std::runtime_error("Unsupported queue operation: " + op_string);
    }
  }

  void execute(Queue& q) const {
    switch (op) {
      case Operation::kConstruct:
        // Hack to bypass deleted assign operator
        q.~Queue();
        new (&q) Queue(argument);
        break;
      case Operation::kDequeue: {
        int result = q.Dequeue();
        if (result != argument) {
          throw TestFailure("Dequeue: expected " + std::to_string(argument) +
                            ", got " + std::to_string(result));
        }
      } break;
      case Operation::kEnqueue:
        q.Enqueue(argument);
        break;
      case Operation::kSize: {
        int s = q.Size();
        if (s != argument) {
          throw TestFailure("Size: expected " + std::to_string(argument) +
                            ", got " + std::to_string(s));
        }
      } break;
    }
  }
};

namespace test_framework {
template <>
struct SerializationTrait<QueueOp> : UserSerTrait<QueueOp, std::string, int> {};
}  // namespace test_framework

void QueueTester(const std::vector<QueueOp>& ops) {
  Queue q(0);
  for (auto& op : ops) {
    op.execute(q);
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "circular_queue.cc", "circular_queue.tsv",
                         &QueueTester, DefaultComparator{}, param_names);
}
