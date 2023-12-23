#include <stdio.h>
#include <arm_neon.h>

int32x4_t add4(const int32x4_t a, int32x4_t b) {
  return vaddq_s32(a, b); // NEON equivalent of _mm_add_epi32
}

void load_add_store_4_accum(const int *arr, int32x4_t *accum, int i){
    int32x4_t a = vld1q_s32(&arr[i]);
    *accum = add4(a, *accum);
}

void vectorized_cum_sum(const int *arr, int *out, const int len){
    int end = len & -4; 
    int32x4_t accum = vdupq_n_s32(0);
    int i = 0;
    for (; i < end; i += 4){load_add_store_4_accum(arr, &accum, i);}
    
    int32x4_t lane_sum = vpaddq_s32(accum, accum);
    lane_sum = vpaddq_s32(lane_sum, lane_sum);

    int result = vgetq_lane_s32(lane_sum, 0);
    for (; i < len; i +=1){result += arr[i];}
    *out = result;
}


int main(){
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int len = sizeof(a) / sizeof(a[0]);
    int *cumsumptr; 

    vectorized_cum_sum(a, cumsumptr, len);
    printf("Cumsum: %d ", *cumsumptr);
    return 0;
}