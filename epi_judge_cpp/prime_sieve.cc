#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n) {
  // TODO - you fill in here.
  std::deque<bool> sieve(n+1, true);
  sieve[0] = false;
  for (int i = 2; i < n/2+1; ++i) {
      for (int j = 2; i*j <= n; ++j) {
          sieve[i*j] = false;
      }
  }
  vector<int> ret;
  for (int i = 2; i <= n; ++i) {
      if (sieve[i]) {
          ret.push_back(i);
      }
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
