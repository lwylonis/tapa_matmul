#include <tapa.h>
#include <matmul.h>

void matmul(tapa::mmap<float> A,
	    tapa::mmap<float> B,
    	    tapa::mmap<float> C) {
    
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
