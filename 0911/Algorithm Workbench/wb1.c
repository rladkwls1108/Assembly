#include <stdio.h>
#include <stdint.h>

unsigned int bin16_to_uint(const char* s){
    unsigned int v = 0;
    for(size_t i=0; s[i]; ++i){
        if(s[i]=='0' || s[i]=='1'){
            v = (v<<1) + (s[i]-'0');
        }
    }
    return v;
}

int main(void){
    char s[65];
    scanf("%64s", s);
    printf("%u\n", bin16_to_uint(s));
    return 0;
}
