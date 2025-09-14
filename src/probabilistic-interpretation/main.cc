#include <matplot/freestanding/plot.h>
#include <matplot/axes_objects/line.h>
#include <matplot/freestanding/axes_lim.h>
#include <matplot/util/common.h>
#include <matplot/core/axes_type.h>
#include <matplot/freestanding/axes_functions.h>
#include <matplot/core/figure_registry.h>
#include <matplot/core/figure_type.h>

#include <memory>
#include <vector>
#include <ranges>
#include <functional>
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <format>

using math_fn = std::function<double(double)>;

math_fn disjunction(math_fn f1, math_fn f2) {
  return [f1, f2](double x) -> double {
    const double y1 = f1(x), y2 = f2(x);
    return y1 + y2 - y1 * y2;
  };
}

math_fn conjunction(math_fn f1, math_fn f2) {
  return [f1, f2](double x) -> double { return f1(x) * f2(x); };
}

double gaussmf(double x, double c, double sig) {
  return std::exp(-((x - c) * (x - c)) / (2 * sig * sig));
}

std::function<double(double)> makeGaussmf(const double c, const double sig) {
  return [c, sig](double x) -> double { return gaussmf(x, c, sig); };
}

int main(const int argc, const char* argv[]) {
  using std::views::transform, std::ranges::to;

  constexpr double c1 = -3, sig1 = 4;
  constexpr double c2 = 3, sig2 = 4;
  const auto f1 = makeGaussmf(c1, sig1);
  const auto f2 = makeGaussmf(c2, sig2);

  const std::vector<double> x_numbers = matplot::linspace(-15, 15);
  const std::vector<double> y_numbers1 = x_numbers | transform(f1) | to<std::vector>();
  const std::vector<double> y_numbers2 = x_numbers | transform(f2) | to<std::vector>();
  const std::vector<double> intersection =
    x_numbers | transform(conjunction(f1, f2)) | to<std::vector>();
  const std::vector<double> unionn = x_numbers | transform(disjunction(f1, f2)) | to<std::vector>();

  matplot::figure()->size(800, 600);

  auto ax1 = matplot::subplot(2, 1, 0);
  matplot::hold(true);
  matplot::plot(x_numbers, y_numbers1, "--")->line_width(2);
  matplot::plot(x_numbers, y_numbers2, "--")->line_width(2);
  matplot::plot(x_numbers, intersection)->line_width(3);
  matplot::title("Intersection(y1 * y2)");
  const std::string label1 = std::format("gaussmf(x, {}, {})", c1, sig1);
  const std::string label2 = std::format("gaussmf(x, {}, {})", c2, sig2);
  matplot::legend(ax1, { label1, label2, "Conjunction" });

  auto ax2 = matplot::subplot(2, 1, 1);
  matplot::hold(true);
  matplot::plot(x_numbers, y_numbers1, "--")->line_width(2);
  matplot::plot(x_numbers, y_numbers2, "--")->line_width(2);
  matplot::plot(x_numbers, unionn)->line_width(3);
  matplot::title("Union(y1 + y2 - y1 * y2)");
  matplot::legend(ax2, { label1, label2, "Union" });

  for (const auto& axis: { ax1, ax2 }) {
    matplot::ylim(axis, { 0, 1.1 });
    matplot::grid(axis, true);
    axis->minor_grid(true);
  }

  matplot::show();
  return 0;
}
