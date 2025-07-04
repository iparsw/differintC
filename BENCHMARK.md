# BENCHMARK.md

## Benchmark Methodology and Hardware

This document describes the methodology and test environment used for all performance benchmarks in the `differintC`, `differintP`, and related projects.

---

## Hardware & Software

* **Laptop:** Lenovo Legion Y545
* **Operating System:** Windows 10
* **CPU:** Intel Core i7-9750H @ 2.6GHz (6 cores, 12 threads)
* **GPU:** NVIDIA GTX 1660 Ti (used for functions with names ending in `_gpu` only)
* **Python:** 3.x
* **NumPy:** \[version used]
* **CuPy:** \[version used, for GPU benchmarks]
* **differintC / differintP:** \[commit hash or version, if relevant]

---

## Benchmark Methodology

* All timing measurements are performed using Python’s `time.perf_counter()`.
* Each benchmarked function is run multiple times (`c`, chosen as the largest reasonable value under a 5-minute total per test; typically up to 1,000 for fast functions).
* The mean execution time is reported in milliseconds.
* All tests use a fixed set of functions and consistent input arrays for fair comparison.

**Sample benchmark script:**

```python
from time import perf_counter
import numpy as np

def bench1_custom(function, size, c):
    f1 = lambda x: np.sin(x)
    x2 = np.linspace(0, 1, int(size))
    y2 = f1(x2)

    times = []
    for _ in range(c):
        start = perf_counter()
        df = function(0.5, y2, 0, 1, int(size))
        end = perf_counter()
        times.append(end - start)
    avg_ms = np.mean(times) * 1000
    print(f"Size {size} : {avg_ms:.4f} ms")
```

* For `*_gpu` functions, computations are performed on the GPU using CuPy.
* For all other functions, computations are performed on the CPU.

---

## Notes

* The same methodology and hardware are used for all reported benchmarks, unless otherwise specified.
* For full benchmark results and speedup tables, see the project wiki or referenced markdown files.



