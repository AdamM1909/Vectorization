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

int check_round_down() {
    int len = 20;  // Example length
    int end = len & -4;

    printf("Original Length: %d\n", len);
    printf("Adjusted Length: %d\n", end);

    return 0;
}

void load_add_store_4(const int *arr1, const int *arr2, int *out, int i){
    int32x4_t a = vld1q_s32(&arr1[i]);
    int32x4_t b = vld1q_s32(&arr2[i]);
    vst1q_s32(&out[i], add4(a, b));

}

void vectorized_add_arrays(const int *arr1, const int *arr2, int *out, const int len){
    int end = len & -4; // Fast round down to closest multiple of 4
    int i = 0;
    for (; i < end; i += 4){load_add_store_4(arr1, arr2, out, i);}
    // Add the last 4 seperately to minimise operations.
    int last4idx = len - 4;
    load_add_store_4(arr1, arr2, out, last4idx);
}



int main(){
    int a1[5] = {1, 2, 3, 4, 5};
    int a2[5] = {10, 10, 10, 10, 10};
    
    int len = sizeof(a1) / sizeof(a1[0]);
    int out1[len];
    int out2[len];

    add_arrays(a1, a2, out1, len);
    vectorized_add_arrays(a1, a2, out2, len);

    printf("Normal version:\n");
    for (int i = 0; i < len; ++i) {
        printf("%d ", out1[i]);
    }

    printf("\nVectorized version:\n");
    for (int i = 0; i < len; ++i) {
        printf("%d ", out2[i]);
    }

    return 0;
}
