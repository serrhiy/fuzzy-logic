#include <matplot/axes_objects/line.h>
#include <matplot/core/axes_type.h>
#include <matplot/freestanding/axes_functions.h>
#include <matplot/freestanding/axes_lim.h>
#include <matplot/freestanding/plot.h>
#include <matplot/util/common.h>

#include <algorithm>
#include <cmath>
#include <functional>
#include <memory>
#include <ranges>
#include <vector>

double gbellmf(double x, double a, double b, double c) {
  return 1.0 / (1 + std::pow(std::fabs((x - c) / a), 2 * b));
}

std::function<double(double)> makeGbellmf(double a, double b, double c) {
  return [a, b, c](double x) -> double { return gbellmf(x, a, b, c); };
}

int main(const int argc, const char* argv[]) {
  using std::views::transform, std::ranges::to;

  const std::vector<double> x_numbers = matplot::linspace(-5, 5);
  const std::vector<double> y_numbers1 =
      x_numbers | transform(makeGbellmf(2, 3.8, 0)) | to<std::vector>();
  const std::vector<double> y_numbers2 =
      x_numbers | transform(makeGbellmf(1, -2, 0)) | to<std::vector>();

  matplot::hold(true);
  matplot::plot(x_numbers, y_numbers1)->line_width(2);
  matplot::plot(x_numbers, y_numbers2)->line_width(2);
  matplot::ylim({0, 1.5});
  matplot::grid(true);
  matplot::gca()->minor_grid(true);
  matplot::title("Generalized bell shape membership function");
  matplot::show();
  return 0;
}
