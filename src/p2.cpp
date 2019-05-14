
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
				&v[0], sizeof(T), py::format_descriptor<T>::format(), 1,
				vector<size_t>{v.size()}, vector<size_t>{sizeof(T)}
			));
}

//valarray<float> linspace(float start, float stop, int size)
//{
//    valarray<float> v(size);
//    for(int i=0; i<size; i++) v[i] = start + i * (stop-start)/size;
//    return v;
//}
//
//std::valarray<float> arange(float start, float step, float stop)
//{
//    int size = (stop - start) / step;
//    valarray<float> v(size);
//    for(int i=0; i<size; i++) v[i] = start + step * i;
//    return v;
//}

int main()
{
	py::scoped_interpreter guard{};
	py::exec("print 'hello'");

	py::object arange = py::module::import("numpy").attr("arange");
	py::object sin = py::module::import("numpy").attr("sin");
	py::array a = arange(0, 15, 0.1);
	py::array b =  sin(a) + a*a*a;
//	auto x = arange(0, 0.1, 15);

//	valarray<float> y = sin(x);
//	auto nx = to_numpy(move(x));
//	auto ny = to_numpy(move(y));
	py::object plt = py::module::import("matplotlib.pyplot");
	py::object plot = plt.attr("plot");
	py::object show = plt.attr("show");
	plot(a, b, "color"_a = "green");
//	plot(nx, ny);
	show();
}

