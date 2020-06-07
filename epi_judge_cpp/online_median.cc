#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin,
                            const vector<int>::const_iterator &sequence_end) {
    // TODO - you fill in here.
    // 最小堆存储较大的那半部份数  最大堆存储较小的那部份
    std::priority_queue<int, vector<int>, std::greater<>> min_heap;
    std::priority_queue<int, vector<int>, std::less<>> max_heap;
    vector<double> ret;
    while (sequence_begin != sequence_end) {
        min_heap.emplace(*sequence_begin++);
        max_heap.emplace(min_heap.top());
        min_heap.pop();
        // 偶数个元素情况下， 两个堆大小将会相等， 否则最小堆将会多一个元素
        if (max_heap.size() > min_heap.size()) {
            min_heap.emplace(max_heap.top());
            max_heap.pop();
        }
        ret.emplace_back(max_heap.size() == min_heap.size() ?
                         0.5 * max_heap.top() + 0.5 * min_heap.top() :
                         min_heap.top());
    }
    return ret;
}

vector<double> OnlineMedianWrapper(const vector<int> &sequence) {
    return OnlineMedian(cbegin(sequence), cend(sequence));
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"sequence"};
    return GenericTestMain(args, "online_median.cc", "online_median.tsv",
                           &OnlineMedianWrapper, DefaultComparator{},
                           param_names);
}
