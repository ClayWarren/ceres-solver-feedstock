#include <ceres/ceres.h>
#include <cmath>
#include <iostream>
struct Residual {
  template<typename T> bool operator()(const T* x, T* r) const {
    r[0] = T(10) - x[0]; return true;
  }
};
int main() {
  double x = -5;
  ceres::Problem problem;
  problem.AddResidualBlock(new ceres::AutoDiffCostFunction<Residual, 1, 1>(new Residual), nullptr, &x);
  ceres::Solver::Options options;
  options.linear_solver_type = ceres::SPARSE_NORMAL_CHOLESKY;
  options.sparse_linear_algebra_library_type = ceres::SUITE_SPARSE;
  ceres::Solver::Summary summary;
  ceres::Solve(options, &problem, &summary);
  std::cout << summary.BriefReport() << " x=" << x << std::endl;
  return summary.IsSolutionUsable() && std::abs(x - 10) < 1e-6 ? 0 : 1;
}
