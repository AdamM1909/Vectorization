#include <stdio.h>
#include <arm_neon.h>

int32x4_t add4(const int32x4_t a, const int32x4_t b) {
  return vaddq_s32(a, b); // NEON equivalent of _mm_add_epi32
}

void add_arrays(const int *arr1, const int *arr2, int *out, const int len){
    for (int i = 0; i < len; i++){
        out[i] = arr1[i] + arr2[i];
    }
}


int main(){
    int a1[5] = {1, 2, 3, 4, 5};
    int a2[5] = {10, 10, 10, 10, 10};
    
    int len = sizeof(a1) / sizeof(a1[0]);
    int out[len];

    add_arrays(a1, a2, out, len);

    for (int i = 0; i < len; ++i) {
        printf("%d ", out[i]);
    }
    return 0;
}