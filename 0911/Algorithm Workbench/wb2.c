#include <stdio.h>
#include <ctype.h>

unsigned long hex32_to_ulong(const char* s){
    unsigned long v = 0;
    for(size_t i=0; s[i]; ++i){
        int c = s[i];
        int d = (c>='0'&&c<='9')? c-'0' :
                (c>='a'&&c<='f')? 10 + (c-'a') :
                (c>='A'&&c<='F')? 10 + (c-'A') : -1;
        if(d>=0) v = (v<<4) + d;
    }
    return v;
}

int main(void){
    char s[129];
    scanf("%128s", s);
    printf("%lu\n", hex32_to_ulong(s));
    return 0;
}
