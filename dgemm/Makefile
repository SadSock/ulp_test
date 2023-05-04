all: x86 amd_gpu nvidia_gpu ulp

x86: x86.c
	gcc -O2 -Wall x86.c -lblas -o x86

amd_gpu: amd_gpu.cpp
	hipcc -lrocblas amd_gpu.cpp -o amd_gpu

nvidia_gpu: nvidia_gpu.cu
	nvcc nvidia_gpu.cu -lcublas -o nvidia_gpu -allow-unsupported-compiler

riscv: riscv.c
	gcc -O2 -Wall riscv.c -lblas -o riscv

ulp: ulp.c
	gcc -O2 ulp.c -o ulp -lm

clean:
	rm -f x86 amd_gpu nvidia_gpu ulp
