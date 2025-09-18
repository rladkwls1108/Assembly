#include <stdio.h>
#include <stdlib.h>

char* int_to_hex(unsigned int n){
    if(n==0) return "0";
    static char buf[128];
    int idx=0;
    while(n){
        unsigned d=n&0xF;
        buf[idx++]= d<10? ('0'+d):('A'+d-10);
        n >>=4;
    }
    buf[idx]='\0';
    for(int i=0;i<idx/2;i++){
        char t=buf[i];
        buf[i]=buf[idx-1-i];
        buf[idx-1-i]=t;
    }
    return buf;
}

int main(void){
    unsigned int n;
    scanf("%u", &n);
    printf("%s\n", int_to_hex(n));
    return 0;
}
