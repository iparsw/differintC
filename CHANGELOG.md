## 0.0.1: (6/30/2025) First working Version
### ~~0.0.2:~~ problematic
### ~~0.0.2.1:~~ problematic
### ~~0.0.2.2:~~ problematic
## 0.0.2.3: Optimized GL implementation with FFT acceleration

bench_1 Result:

| time | GL          |  RL         | GLpoint     | RLpoint    |
| ---- | ----------- | ----------- | ----------- | ---------- |
| 1+e2 | *           | 0.0482 ms   | *           | 0.0099 ms  |
| 1+e3 | 0.9822 ms   | 5.6009 ms   | 0.0083 ms   | 0.0899 ms  |
| 1+e4 | 5.2982 ms   | 605.5952 ms | 0.0721 ms   | 1.0599 ms  |
| 1+e5 | 104.1740 ms | *           | 1.5568 ms   | 9.6303 ms  |
| 1+e6 | 667.7444 ms | *           | 10.0608 ms  | 93.9401 ms |


## 0.0.2.4: Optimized GLpoint implementation

- GLpoint
  - On-the-fly Coefficient Calculation
  - Efficient Memory Access
  - Precomputed Constants
- GLcoeffs optimization


bench_1 Result and comparison to original differint package (1.0.0):

| time |  0.0.2.3    |  0.0.2.4    | differint   |
| ---- | ----------- | ----------- | ----------- |
| 1+e2 | *           | *           | *           |
| 1+e3 | 0.0083 ms   | 0.0099 ms   | 0.4213 ms   |
| 1+e4 | 0.0721 ms   | 0.0243 ms   | 3.8376 ms   |
| 1+e5 | 1.5568 ms   | 0.1885 ms   | 36.3030 ms  |
| 1+e6 | 10.0608 ms  | 3.9995 ms   | 385.9205 ms |
| 1+e7 | *           | 41.2 ms     | *           |
