#pragma once

#include <cstdint>
#include <tapa.h>

// MxK times KxM -> MxN
void matmul(tapa::mmap<float> A,
	    tapa::mmap<float> B,
    	    tapa::mmap<float> C,
	    uint64_t kM, uint64_t kK, uint64_t kN);
