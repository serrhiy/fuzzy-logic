#include <matplot/axes_objects/line.h>
#include <matplot/core/axes_type.h>
#include <matplot/freestanding/axes_functions.h>
#include <matplot/freestanding/axes_lim.h>
#include <matplot/freestanding/plot.h>
#include <matplot/util/common.h>

#include <algorithm>
#include <cmath>
#include <format>
#include <functional>
#include <initializer_list>
#include <memory>
#include <ranges>
#include <vector>

using math_fn = std::function<double(double)>;

math_fn setComplement(math_fn f) {
  return [f](double x) -> double { return 1 - f(x); };
}

double sigmf(double x, double a, double c) {
  return 1.0 / (1 + std::exp(-a * (x - c)));
}

double dsigmf(double x, double a1, double c1, double a2, double c2) {
  return sigmf(x, a1, c1) - sigmf(x, a2, c2);
}

std::function<double(double)> makeDsigmf(double a1, double c1, double a2,
                                         double c2) {
  return [a1, c1, a2, c2](double x) -> double {
    return dsigmf(x, a1, c1, a2, c2);
  };
}

int main(const int argc, const char* argv[]) {
  using std::views::transform, std::ranges::to;

  constexpr double a1 = 0.8, c1 = -5.5, a2 = 0.7, c2 = 8;
  const auto f = makeDsigmf(a1, c1, a2, c2);

  const std::vector<double> x_numbers = matplot::linspace(-10, 10);
  const std::vector<double> y_numbers =
      x_numbers | transform(f) | to<std::vector>();
  const std::vector<double> complement =
      x_numbers | transform(setComplement(f)) | to<std::vector>();

  matplot::hold(true);
  matplot::plot(x_numbers, y_numbers)->line_width(2);
  matplot::plot(x_numbers, complement, "--")->line_width(2);
  matplot::ylim({0, 1.1});
  matplot::grid(true);
  matplot::gca()->minor_grid(true);
  matplot::title("Set complement");
  const std::string label1 =
      std::format("dsigmf(x, {}, {}, {}, {})", a1, c1, a2, c2);
  matplot::legend(matplot::gca(), {label1, "Complement"});
  matplot::show();

  return 0;
}
