# Matrix Multiplication in TAPA HLS.

To compile and run using TAPA software simulation, simply run with specified arguments:
```bash
tapa g++ -- -I src src/matmul.cpp src/matmul-host.cpp -o matmul
./matmul <kM> <kK> <kN>
```
