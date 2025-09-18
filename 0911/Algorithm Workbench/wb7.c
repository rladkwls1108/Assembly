#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int hv(char c){
    if(c>='0'&&c<='9') return c-'0';
    if(c>='a'&&c<='f') return 10+(c-'a');
    if(c>='A'&&c<='F') return 10+(c-'A');
    return 0;
}
char hd(int v){ return (v<10)? ('0'+v):('A'+v-10); }

char* mul_hex_single(const char* a, char digit){
    int mult=hv(digit);
    int n=strlen(a);
    static char out[2000];
    out[n+1]='\0';
    int k=n, carry=0;
    for(int i=n-1;i>=0;--i){
        int p=hv(a[i])*mult+carry;
        carry=p>>4;
        out[--k]=hd(p&0xF);
    }
    while(carry){ out[--k]=hd(carry&0xF); carry>>=4; }
    return out+k;
}

int main(void){
    char A[1100], d[4];
    scanf("%1099s %3s", A, d);
    printf("%s\n", mul_hex_single(A, d[0]));
    return 0;
}
