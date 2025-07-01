## 0.0.1: (6/30/2025) First working Version
### ~~0.0.2:~~ problematic
### ~~0.0.2.1:~~ problematic
### ~~0.0.2.2:~~ problematic
## 0.0.2.3: Optimized GL implementation with FFT acceleration

bench_1 Result:

| time |  RL         | GL          |
| ---- | ----------- | ----------- |
| 1+e2 | 0.0482 ms   | *           |
| 1+e3 | 5.6009 ms   | 0.9822 ms   |
| 1+e4 | 605.5952 ms | 5.2982 ms   |
| 1+e5 | *           | 104.1740 ms |
| 1+e6 | *           | 667.7444 ms |