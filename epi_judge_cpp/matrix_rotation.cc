#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
void RotateMatrix(vector<vector<int>>* square_matrix_ptr) {
  // TODO - you fill in here.
  vector<vector<int>> &square_matrix = *square_matrix_ptr;
  const int mat_size = square_matrix.size() - 1;
  for (int i = 0; i < square_matrix.size() / 2; ++i) {
      for (int j = i; j < mat_size - i; ++j) {
          int temp1 = square_matrix[i][j]; // top element
          int temp2 = square_matrix[j][mat_size-i]; // right element
          int temp3 = square_matrix[mat_size-i][mat_size-j]; // bottom element
          int temp4 = square_matrix[mat_size-j][i]; // left element

          square_matrix[i][j] = temp4; // left2top
          square_matrix[j][mat_size-i] = temp1; //top2right
          square_matrix[mat_size-i][mat_size-j] = temp2; // right2bottom
          square_matrix[mat_size-j][i] = temp3; //bottom2left
      }
  }
  return;
}
vector<vector<int>> RotateMatrixWrapper(vector<vector<int>> square_matrix) {
  RotateMatrix(&square_matrix);
  return square_matrix;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "matrix_rotation.cc", "matrix_rotation.tsv",
                         &RotateMatrixWrapper, DefaultComparator{},
                         param_names);
}
