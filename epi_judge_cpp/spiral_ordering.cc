#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
  // TODO - you fill in here.
  const vector<vector<int>> kShift = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  int dir = 0, x = 0, y = 0;
  int nextX = 0, nextY = 0;
  vector<vector<int>> visited(square_matrix);
  vector<int> ret;
  for (int i = 0; i < square_matrix.size() * square_matrix.size(); ++i) {
      ret.push_back(square_matrix[x][y]);
      visited[x][y] = 0;
      nextX = x + kShift[dir][0];
      nextY = y + kShift[dir][1];
      if (nextX < 0 || nextX >= square_matrix.size() || nextY < 0 || nextY >= square_matrix.size() || visited[nextX][nextY] == 0) {
          dir = (dir + 1) % 4;
          nextX = x + kShift[dir][0];
          nextY = y + kShift[dir][1];
      }
      x = nextX;
      y = nextY;
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
