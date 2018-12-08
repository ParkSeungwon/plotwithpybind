#include<pybind11/pybind11.h>
#include<pybind11/embed.h>
#include<pybind11/numpy.h>
using namespace std;
using namespace pybind11::literals;
namespace py = pybind11;

int main()
{
	py::scoped_interpreter guard{};
	py::exec("print 'hello'");

	py::object linspace = py::module::import("numpy").attr("linspace");
	py::array a = linspace(1, 100, 300);
	py::array b = a * a;

	py::object plt = py::module::import("matplotlib.pyplot");
	py::object plot = plt.attr("plot");
	py::object show = plt.attr("show");
	plot(a, b, "color"_a = "green");
	show();
}

