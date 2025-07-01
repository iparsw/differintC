#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <vector>
#include <stdexcept>

namespace py = pybind11;

namespace differint {
    std::vector<double> RL(double, const std::vector<double>&, double, double, size_t);
    double RLpoint(double, const std::vector<double>&, double, double, size_t);
    std::vector<double> GL(double, const std::vector<double>&, double, double, size_t);
    double GLpoint(double, const std::vector<double>&, double, double, size_t);
}
using namespace differint;



// Helper to sample a Python callable into a std::vector<double>
template <typename Func>
std::vector<double> call_and_sample(Func&& f, double a, double b, size_t n) {
    std::vector<double> vals(n);
    double step = (b - a) / (n - 1);
    for (size_t i = 0; i < n; ++i)
        vals[i] = f(a + step * i);
    return vals;
}

// Overload 1: Input is a NumPy array or list (accept py::array_t<double>)
std::vector<double> prepare_fvals(py::array_t<double> arr, size_t expected_size) {
    if (arr.size() != expected_size)
        throw std::runtime_error("Input array length must equal num_points");
    // Copy data from NumPy array (you could do zero-copy with caution, but copying is safer here)
    std::vector<double> v(arr.size());
    std::memcpy(v.data(), arr.data(), sizeof(double) * arr.size());
    return v;
}

// Overload 2: Input is a Python callable (py::function)
std::vector<double> prepare_fvals(py::function func, double a, double b, size_t n) {
    return call_and_sample([&func](double x) {
        return func(x).cast<double>();
    }, a, b, n);
}





PYBIND11_MODULE(_differintC, m) {
    m.doc() = "Fast fractional calculus operators in C++ with Python bindings";

    // RL (whole array)
    m.def("RL", [](double alpha, py::object f, double domain_start, double domain_end, size_t num_points) {
        // Dispatch based on type
        if (py::isinstance<py::array>(f)) {
            return RL(alpha, prepare_fvals(f.cast<py::array_t<double>>(), num_points), domain_start, domain_end, num_points);
        } else if (py::isinstance<py::function>(f)) {
            return RL(alpha, prepare_fvals(f.cast<py::function>(), domain_start, domain_end, num_points), domain_start, domain_end, num_points);
        } else if (py::isinstance<py::list>(f)) {
            // treat list as array
            return RL(alpha, prepare_fvals(f.cast<py::array_t<double>>(), num_points), domain_start, domain_end, num_points);
        } else {
            throw std::runtime_error("Unsupported input type for function f");
        }
    }, py::arg("alpha"), py::arg("f"), py::arg("domain_start") = 0.0, py::arg("domain_end") = 1.0, py::arg("num_points") = 100);

    // RLpoint (single point)
    m.def("RLpoint", [](double alpha, py::object f, double domain_start, double domain_end, size_t num_points) {
        if (py::isinstance<py::array>(f)) {
            return RLpoint(alpha, prepare_fvals(f.cast<py::array_t<double>>(), num_points), domain_start, domain_end, num_points);
        } else if (py::isinstance<py::function>(f)) {
            return RLpoint(alpha, prepare_fvals(f.cast<py::function>(), domain_start, domain_end, num_points), domain_start, domain_end, num_points);
        } else if (py::isinstance<py::list>(f)) {
            return RLpoint(alpha, prepare_fvals(f.cast<py::array_t<double>>(), num_points), domain_start, domain_end, num_points);
        } else {
            throw std::runtime_error("Unsupported input type for function f");
        }
    }, py::arg("alpha"), py::arg("f"), py::arg("domain_start") = 0.0, py::arg("domain_end") = 1.0, py::arg("num_points") = 100);



    m.def("GL", [](double alpha, py::object f, double domain_start, double domain_end, size_t num_points) {
        // Dispatch based on type
        if (py::isinstance<py::array>(f)) {
            return GL(alpha, prepare_fvals(f.cast<py::array_t<double>>(), num_points), domain_start, domain_end, num_points);
        } else if (py::isinstance<py::function>(f)) {
            return GL(alpha, prepare_fvals(f.cast<py::function>(), domain_start, domain_end, num_points), domain_start, domain_end, num_points);
        } else if (py::isinstance<py::list>(f)) {
            // treat list as array
            return GL(alpha, prepare_fvals(f.cast<py::array_t<double>>(), num_points), domain_start, domain_end, num_points);
        } else {
            throw std::runtime_error("Unsupported input type for function f");
        }
    }, py::arg("alpha"), py::arg("f"), py::arg("domain_start") = 0.0, py::arg("domain_end") = 1.0, py::arg("num_points") = 100);

    // GLpoint (single point)
    m.def("GLpoint", [](double alpha, py::object f, double domain_start, double domain_end, size_t num_points) {
        if (py::isinstance<py::array>(f)) {
            return GLpoint(alpha, prepare_fvals(f.cast<py::array_t<double>>(), num_points), domain_start, domain_end, num_points);
        } else if (py::isinstance<py::function>(f)) {
            return GLpoint(alpha, prepare_fvals(f.cast<py::function>(), domain_start, domain_end, num_points), domain_start, domain_end, num_points);
        } else if (py::isinstance<py::list>(f)) {
            return GLpoint(alpha, prepare_fvals(f.cast<py::array_t<double>>(), num_points), domain_start, domain_end, num_points);
        } else {
            throw std::runtime_error("Unsupported input type for function f");
        }
    }, py::arg("alpha"), py::arg("f"), py::arg("domain_start") = 0.0, py::arg("domain_end") = 1.0, py::arg("num_points") = 100);

}
