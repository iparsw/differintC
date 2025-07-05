- **Only Windows Support for now!**
- There is also a more complete version implemented in Pure python [diffeintP](https://github.com/iparsw/differintP)


# differintC

`differintC` is a high-performance C++ library with Python bindings for computing fractional differintegrals (derivatives and integrals of arbitrary real order) using numerical methods.

This package implements optimized versions of the Riemann–Liouville and Grünwald–Letnikov (GL) fractional differintegral operators, inspired by the original [DifferInt project](https://github.com/differint/differint).

> ⚙️ Built with modern C++17 and exposed to Python via `pybind11`, this library is significantly faster than pure-Python equivalents, especially for large arrays and high-precision needs.

---

## 📦 Installation

```bash
pip install differintC
````


---

## 🚀 Usage

```python
from differintC import RLpoint, RL, GLpoint, GL

# Example 1: Riemann–Liouville at a single point
result = RLpoint(0.5, lambda x: x**2)
print("RLpoint(0.5, x^2) =", result)

# Example 2: RL on a whole domain
import numpy as np
x = np.linspace(0, 1, 100)
f = x**2
out = RL(0.5, f)

# Example 3: Grünwald–Letnikov pointwise
gl_res = GLpoint(0.5, lambda x: np.sqrt(x))

# Example 4: Full array version (fastest)
gl_array = GL(0.5, lambda x: np.sqrt(x))
```

All functions support either a NumPy array or a Python callable as the `f_name` argument.

---

## 📚 Implemented Functions

| Function  | Description                                 |
| --------- | ------------------------------------------- |
| `RLpoint` | Riemann–Liouville differintegral at a point |
| `RL`      | RL differintegral over a uniform domain     |
| `GLpoint` | Grünwald–Letnikov at a point (optimized)    |
| `GL`      | Vectorized GL differintegral with FFT       |

---

## ⚖️ License and Credits

This package was inspired by and based on the original [`DifferInt`](https://placeholder-link-to-original-differint-project) project. We thank the authors for their foundational work in fractional calculus.

Licensed under MIT.

---

## 🛠 Development Notes

See the [todo list 1](https://github.com/your-username/differintC-project/issues/1) for the development roadmap and planned features. Contributions are welcome.
