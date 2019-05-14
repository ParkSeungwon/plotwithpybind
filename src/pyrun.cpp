#include<valarray>
#include<pybind11/pybind11.h>
#include<pybind11/embed.h>
#include<pybind11/numpy.h>
using namespace std;
using namespace pybind11::literals;
namespace py = pybind11;

template<class T> py::array_t<T> to_numpy(valarray<T> &&v)
{
	return py::array_t<T>(py::buffer_info(
				&v[0], sizeof(T), py::format_descriptor<T>::format(), 1,//dim
				{v.size()}, {sizeof(T)}//stride
			));
}

valarray<float> linspace(float start, float stop, int size)
{
    valarray<float> v(size);
    for(int i=0; i<size; i++) v[i] = start + i * (stop-start)/size;
    return v;
}

std::valarray<float> arange(float start, float step, float stop)
{
    int size = (stop - start) / step;
    valarray<float> v(size);
    for(int i=0; i<size; i++) v[i] = start + step * i;
    return v;
}

int main()
{
	py::scoped_interpreter guard{};
	py::exec("print 'hello'");

//	py::object linspac = py::module::import("numpy").attr("linspace");
//	py::array a = linspac(1, 100, 300);
//	py::array b = a * a;
	auto x = arange(0, 0.1, 15);
	valarray<float> y = 2 * sin(x) + tan(x);
	auto nx = to_numpy(move(x));
	auto ny = to_numpy(move(y));
	py::object plt = py::module::import("matplotlib.pyplot");
	py::object plot = plt.attr("plot");
	py::object show = plt.attr("show");
	py::object scatter = plt.attr("scatter");
//	plot(a, b, "color"_a = "green");
	plot(nx, ny, "color"_a = "green");
	scatter(nx, ny);
	show();
}

