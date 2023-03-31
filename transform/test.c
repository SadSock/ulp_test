#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main(int argc, char* argv[]){

        uint64_t ret_u64;
        double ret_f64;
        

        scanf("%llx", (uint64_t *)&ret_f64);
        ret_u64 = ret_f64;
        printf("%llx\n", ret_u64);
        
        ret_f64   = ldexp(1.0, 64);
        ret_u64 = ret_f64;
        printf("%llx\n", ret_u64);

        ret_u64 = ldexp(1.0, 64);
        printf("%llx\n", ret_u64);
        return 0;
}
