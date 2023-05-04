all: x86 amd_gpu nvidia_gpu ulp

x86: x86.c
	gcc -O2 -Wall x86.c -lblas -o x86

x86_openblas: x86.c
	gcc -O2 -Wall x86.c -lopenblas64 -o x86

mac_x86_openblas:x86.c
	gcc -O2 -Wall x86.c -I/usr/local/opt/openblas/include -L/usr/local/opt/openblas/lib -lopenblas -o x86

amd_gpu: amd_gpu.cpp
	hipcc -lrocblas amd_gpu.cpp -o amd_gpu

nvidia_gpu: nvidia_gpu.cu
	nvcc nvidia_gpu.cu -lcublas -o nvidia_gpu -allow-unsupported-compiler

aarch64: aarch64.c
	gcc -O2 -Wall aarch64.c -lblas -o aarch64

aarch64_openblas: aarch64.c
	gcc -O2 -Wall aarch64.c -lopenblas -o aarch64_openblas
	
ulp: ulp.c
	gcc -O2 ulp.c -o ulp -lm

clean:
	rm -f x86 amd_gpu nvidia_gpu ulp
