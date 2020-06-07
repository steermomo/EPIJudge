#include <vector>
#include <unordered_map>
#include <list>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

class LruCache {
 public:
  LruCache(size_t capacity) {
      this->capacity = capacity;
  }
  int Lookup(int isbn) {
    // TODO - you fill in here.
    auto iter = isbn_price_table_.find(isbn);
    if (iter == isbn_price_table_.end()) {
        return -1;
    }
    int ret_val = iter->second.second;
    MoveFront(isbn, iter);
    return ret_val;
  }
  void Insert(int isbn, int price) {
    // TODO - you fill in here.
    auto iter = isbn_price_table_.find(isbn);
    if (iter == isbn_price_table_.end()) {
        // 未找到
        if (isbn_price_table_.size() == capacity) {
            // 需要替换一个出去
            int subs_isbn = lru_queue_.back();
            isbn_price_table_.erase(subs_isbn);
            lru_queue_.pop_back();

        }
        lru_queue_.emplace_front(isbn);
        isbn_price_table_.insert({isbn, {lru_queue_.begin(), price}});
    } else {
        MoveFront(isbn, iter); //找到项目，更新lru
    }
  }
  bool Erase(int isbn) {
    // TODO - you fill in here.
    auto iter = isbn_price_table_.find(isbn);
    if (iter == isbn_price_table_.end()) {
        return false;
    }
    lru_queue_.erase(iter->second.first);
    isbn_price_table_.erase(iter);
    return true;
  }

private:
    typedef std::unordered_map<int, std::pair<std::list<int>::iterator, int>> Table;
    Table isbn_price_table_;
    std::list<int> lru_queue_;
    size_t capacity;

    void MoveFront(int isbn, const Table::iterator& it) {
        lru_queue_.erase(it->second.first);
        lru_queue_.emplace_front(isbn);
        it->second.first = lru_queue_.begin();
    }
};
struct Op {
  std::string code;
  int arg1;
  int arg2;
};

namespace test_framework {
template <>
struct SerializationTrait<Op> : UserSerTrait<Op, std::string, int, int> {};
}  // namespace test_framework

void LruCacheTester(const std::vector<Op>& commands) {
  if (commands.empty() || commands[0].code != "LruCache") {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++) {
    auto& cmd = commands[i];
    if (cmd.code == "lookup") {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else if (cmd.code == "insert") {
      cache.Insert(cmd.arg1, cmd.arg2);
    } else if (cmd.code == "erase") {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"commands"};
  return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &LruCacheTester,
                         DefaultComparator{}, param_names);
}
