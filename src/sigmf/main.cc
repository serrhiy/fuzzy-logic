#include <matplot/axes_objects/line.h>
#include <matplot/core/axes_type.h>
#include <matplot/core/figure_registry.h>
#include <matplot/core/figure_type.h>
#include <matplot/freestanding/axes_functions.h>
#include <matplot/freestanding/axes_lim.h>
#include <matplot/freestanding/plot.h>
#include <matplot/util/common.h>

#include <algorithm>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <memory>
#include <ranges>
#include <vector>

double sigmf(double x, double a, double c) {
  return 1.0 / (1 + std::exp(-a * (x - c)));
}

double dsigmf(double x, double a1, double c1, double a2, double c2) {
  return sigmf(x, a1, c1) - sigmf(x, a2, c2);
}

double psigmf(double x, double a1, double c1, double a2, double c2) {
  return sigmf(x, a1, c1) * sigmf(x, a2, c2);
}

std::function<double(double)> makeSigmf(double a, double c) {
  return [a, c](double x) -> double { return sigmf(x, a, c); };
}

std::function<double(double)> makeDsigmf(double a1, double c1, double a2,
                                         double c2) {
  return [a1, c1, a2, c2](double x) -> double {
    return dsigmf(x, a1, c1, a2, c2);
  };
}

std::function<double(double)> makePsigmf(double a1, double c1, double a2,
                                         double c2) {
  return [a1, c1, a2, c2](double x) -> double {
    return psigmf(x, a1, c1, a2, c2);
  };
}

int main(const int argc, const char* argv[]) {
  using std::views::transform, std::ranges::to;

  const std::vector<double> x_numbers = matplot::linspace(-15, 15);
  const std::vector<double> y_numbers1 =
      x_numbers | transform(makeSigmf(-1, 3)) | to<std::vector>();
  const std::vector<double> y_numbers2 =
      x_numbers | transform(makeDsigmf(10, -8, 10, 8)) | to<std::vector>();
  const std::vector<double> y_numbers3 =
      x_numbers | transform(makePsigmf(2.5, -8.5, -11, 7)) | to<std::vector>();

  matplot::figure()->size(800, 600);

  auto ax1 = matplot::subplot(2, 2, 0);
  matplot::plot(x_numbers, y_numbers1)->line_width(2);
  matplot::title("Sigmoid function");

  auto ax2 = matplot::subplot(2, 2, 1);
  matplot::plot(x_numbers, y_numbers2)->line_width(2);
  matplot::title("Difference of sigmoid functions");

  auto ax3 = matplot::subplot(2, 2, {2, 3});
  matplot::plot(x_numbers, y_numbers3)->line_width(2);
  matplot::title("Product of sigmoid functions");

  for (const auto& axis : {ax1, ax2, ax3}) {
    matplot::ylim(axis, {0, 1.5});
    matplot::grid(axis, true);
    axis->minor_grid(true);
  }

  matplot::show();
  return 0;
}
