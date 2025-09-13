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
#include <string>

double gaussmf(const double x, const double c, const double sig) {
  return std::exp(-((x - c) * (x - c)) / (2 * sig * sig));
}

double gauss2mf(double x, double c1, double sig1, double c2, double sig2) {
  const double f1 = x <= c1 ? gaussmf(x, c1, sig1) : 1.0;
  const double f2 = x <= c2 ? 1.0 : gaussmf(x, c2, sig2);
  return f1 * f2;
}

std::function<double(double)> makeGauss2mf(double c1, double sig1, double c2, double sig2) {
  return [c1, sig1, c2, sig2](double x) -> double { return gauss2mf(x, c1, sig1, c2, sig2); };
}

int main(const int argc, const char* argv[]) {
  const std::vector<double> x_numbers = matplot::linspace(-15, 15);
  const std::vector<double> y_numbers1 =
    x_numbers | std::views::transform(makeGauss2mf(-4, 3, 2, 1.5)) | std::ranges::to<std::vector>();
  const std::vector<double> y_numbers2 =
    x_numbers | std::views::transform(makeGauss2mf(-7, 0.5, 5, 3)) | std::ranges::to<std::vector>();

  matplot::hold(true);
  matplot::plot(x_numbers, y_numbers1)->line_width(2);
  matplot::plot(x_numbers, y_numbers2)->line_width(2);
  matplot::ylim({ 0, 1.2 });
  matplot::grid(true);
  matplot::gca()->minor_grid(true);
  matplot::title("Gaussian 2 membership function");
  matplot::legend(matplot::gca(), { "gauss2mf(x, -4, 3, 2, 1.5)", "gauss2mf(x, -7, 0.5, 5, 3)" });
  matplot::show();
  return 0;
}
