all: x86 amd_gpu nvidia_gpu ulp

x86: x86.c
	gcc -O2 -Wall x86.c -lblas -o x86

x86_openblas: x86.c
	gcc -O2 -Wall x86.c -lopenblas64 -o x86

amd_gpu: amd_gpu.cpp
	hipcc -lrocblas amd_gpu.cpp -o amd_gpu

nvidia_gpu: nvidia_gpu.cu
	nvcc nvidia_gpu.cu -lcublas -o nvidia_gpu -allow-unsupported-compiler

aarch64: aarch64.c
	gcc -O2 -Wall aarch64.c -lblas -o aarch64

ulp: ulp.c
	gcc -O2 ulp.c -o ulp -lm

clean:
	rm -f x86 amd_gpu nvidia_gpu ulp
