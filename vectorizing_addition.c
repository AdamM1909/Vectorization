#include <stdio.h>
#include <arm_neon.h>


int add(int a, int b) {
  return a + b;
}


int32x4_t add4(int32x4_t a, int32x4_t b) {
  return vaddq_s32(a, b); // NEON equivalent of PADDD
}

int main() {
    // Add one integer at a time.
    int a = 3;
    int b = 4;
    int out;   
    out = add(a, b);
    printf("Result: %d\n", out);


    // Now try adding 4 integrs at a time using NEON intrinsics.
    int32x4_t a4ints = {3, 3, 3, 3};
    int32x4_t b4ints = {4, 4, 4, 8};
    int32x4_t out4 = add4(a4ints, b4ints);
    // Extract and print results.
    int results[4];
    vst1q_s32(results, out4);
    printf("Result: %d %d %d %d\n", results[0], results[1], results[2], results[3]);
    return 0;
}
