#include <matmul.h>

void matmul(tapa::mmap<const float> A,
	    tapa::mmap<const float> B,
    	    tapa::mmap<float> C,
	    uint64_t kM, uint64_t kK, uint64_t kN) {
    
    //NOTE: row major storage is A[i][j] = A[i*kK + j]

    for (int i = 0; i < kM; ++i) {
        for (int j = 0; j < kN; ++j) {
            float sum = 0;
            for (int k = 0; k < kK; ++k) {
                sum += A[kK*i + k] * B[kN*k + j];
            }
            C[kN*i + j] = sum;
        }
    }
}	
