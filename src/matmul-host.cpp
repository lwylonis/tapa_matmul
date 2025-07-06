#include <iostream>
#include <vector>

#include <gflags/gflags.h> // for declaring command line flags

#include <src/matmul.h>

using std::clog;
using std::endl;
using std::vector;

DEFINE_string(bitstream, "", "path to bitstream file, run csim if empty";

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, /*remove_flags=*/true);

    // kM, kK, kN are first three arguments
    const uint64_t kM = argc > 3 ? atoll(argv[1]) : 1024;
    const uint64_t kK = argc > 3 ? atoll(argv[2]) : 1024;
    const uint64_t kN = argc > 3 ? atoll(argv[3]) : 1024;

    vector<float> a(kM*kK);
    vector<float> b(kK*kN);
    vector<float> c(kM*kN);
	
    // builds A as all ones, B as all twos, and C as zeros
    for (uint64_t i = 0; i < kM*kK; ++i) {
	A[i] = static_cast<float>(1);	
    }    
    for (uint64_t i = 0; i < kK*kN; ++i) {
	B[i] = static_cast<float>(1) * 2;	
    }    
    for (uint64_t i = 0; i < kM*kN; ++i) {
	C[i] = 0.f	
    }

    // runs kernel on arguments
    int64_t kernel_time_ns = tapa::invoke(
	matmul, FLAGS_bitstream, 
	tapa::read_only_mmap<const float>(A),     
	tapa::read_only_mmap<const float>(B),     
	tapa::read_only_mmap<const float>(C), kM, kK, kN);
    clog << "kernel time: " << kernel_time_ns * 1e-9 << " s" << endl;

    // checking for errors...
    uint64_t num_errors = 0;
    const uint64_t threshold = 10;  // only report up to these errors
    for (uint64_t i = 0; i < kM*kN; ++i) {
        auto expected = 2 * kK;
        auto actual = static_cast<uint64_t>(C[i]);
        if (actual != expected) {
            if (num_errors < threshold) {
                clog << "expected: " << expected << ", actual: " << actual << endl;
	    }
	    else if (num_errors == threshold) {
                clog << "...";
	    }
            ++num_errors;
        }
    }
    if (num_errors == 0) {
        clog << "PASS!" << endl;
    }
    else {
        if (num_errors > threshold) {
            clog << " (+" << (num_errors - threshold) << " more errors)" << endl;
        }
        clog << "FAIL!" << endl;
    }
    return num_errors > 0 ? 1 : 0;    
}
