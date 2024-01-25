#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>
#include <math.h>

#define PRINT_ARR(arr) \
do { \
    printf(#arr ": "); \
    int n = sizeof(arr) / sizeof(arr[0]); \
    for (int i = 0; i < n; i++) { \
        printf("%.3f ", arr[i]); \
    } \
    printf("\n"); \
} while(0)

void add_arrays_sisd(int n, const float a[static n], const float b[static n], float c[static n]) {
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

void add_arrays_simd(int n, const float a[static n], const float b[static n], float c[static n]) {
    int i;
    for (i = 0; i < n; i += 4) {
        __m128 va = _mm_loadu_ps(&a[i]);
        __m128 vb = _mm_loadu_ps(&b[i]);
        __m128 vc = _mm_add_ps(va, vb);
        _mm_storeu_ps(&c[i], vc);
    }
    for (; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

void fill_random(int n, float a[static n]) {
    for (int i = 0; i < n; i++) {
        a[i] = rand() / (float)RAND_MAX;
    }
}

#define ELEMENTS 800000
#define ITERATIONS 8000

int main(void) {

    srand(time(NULL));

    float* a = malloc(ELEMENTS * sizeof(float));
    float* b = malloc(ELEMENTS * sizeof(float));
    float* c = malloc(ELEMENTS * sizeof(float));

    double total_ms = 0.0;
    double min_ms = INFINITY;
    double max_ms = 0.0;
    for (int i = 1; i <= ITERATIONS; i++) {
        fill_random(ELEMENTS, a);
        fill_random(ELEMENTS, b);
        clock_t t0 = clock();
        // add_arrays_simd(ELEMENTS, a, b, c);
        add_arrays_sisd(ELEMENTS, a, b, c);
        double delta_ms = 1000 * (clock() - t0) / (double)CLOCKS_PER_SEC;
        min_ms = fmin(min_ms, delta_ms);
        max_ms = fmax(max_ms, delta_ms);
        total_ms += delta_ms;
        printf("%d/%d Done. Delta %f ms. Total %f ms\n", i, ITERATIONS, delta_ms, total_ms);
    }
    double avg_ms = total_ms / ITERATIONS;
    printf("Complete. Average %f ms. Min %f ms. Max %f ms. Total %f ms.\n", avg_ms, min_ms, max_ms, total_ms);

    free(a);
    free(b);
    free(c);

    return 0;
}
