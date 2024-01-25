# elliotsr-simd

Summation of two 32-bit float arrays. 800,000 elements. 8,000 iterations. Comparison between SISD and SIMD using Intel x86 AVX intrinsics.

**SISD - Without Compiler Optimizations**:
-   Average: 2.323344 ms
-   Best: 1.874000 ms
-   Worst: 3.391000 ms
-   Total: 18586.751000 ms

**SIMD - Without Compiler Optimizations**:
-   Average: 1.555276 ms
-   Best: 1.243000 ms
-   Worst: 2.469000 ms
-   Total: 12442.206000 ms

**SISD - With Compiler Optimizations**:
-   Average: 0.001137 ms
-   Best: 0.000000 ms
-   Worst: 0.023000 ms
-   Total: 9.095000 ms

**SIMD - With Compiler Optimizations**:
-   Average: 0.001244 ms
-   Best: 0.000000 ms
-   Worst: 0.019000 ms
-   Total: 9.951000 ms