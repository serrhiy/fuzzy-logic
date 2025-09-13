#include <matplot/freestanding/plot.h>
#include <matplot/axes_objects/line.h>
#include <matplot/freestanding/axes_lim.h>
#include <matplot/util/common.h>
#include <matplot/core/axes_type.h>
#include <matplot/freestanding/axes_functions.h>

#include <memory>
#include <vector>
#include <ranges>
#include <functional>
#include <algorithm>
#include <cmath>

double gbellmf(const double x, const double a, const double b, const double c) {
  return 1.0 / (1 + std::pow(std::fabs((x - c) / a), 2 * b));
}

std::function<double(double)> makeGbellmf(const double a, const double b, const double c) {
  return [a, b, c](double x) -> double { return gbellmf(x, a, b, c); };
}

int main(const int argc, const char* argv[]) {
  const std::vector<double> x_numbers = matplot::linspace(-5, 5);
  const std::vector<double> y_numbers1 =
    x_numbers | std::views::transform(makeGbellmf(2, 3.8, 0)) | std::ranges::to<std::vector>();
  const std::vector<double> y_numbers2 =
    x_numbers | std::views::transform(makeGbellmf(1, -2, 0)) | std::ranges::to<std::vector>();

  matplot::hold(true);
  matplot::plot(x_numbers, y_numbers1)->line_width(2);
  matplot::plot(x_numbers, y_numbers2)->line_width(2);
  matplot::ylim({ 0, 1.5 });
  matplot::grid(true);
  matplot::gca()->minor_grid(true);
  matplot::title("Generalized bell shape membership function");
  matplot::show();
  return 0;
}
