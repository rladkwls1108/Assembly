#include <stdio.h>
#include <stdlib.h>

char* int_to_binary(unsigned int n){
    if(n==0) return "0";
    static char buf[128];
    int idx=0;
    while(n){ buf[idx++] = (n&1)?'1':'0'; n >>=1; }
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
    printf("%s\n", int_to_binary(n));
    return 0;
}
