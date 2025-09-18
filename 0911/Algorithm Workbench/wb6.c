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

char* add_hex(const char* a, const char* b){
    int n=strlen(a), m=strlen(b);
    int L=(n>m?n:m)+1;
    static char out[2000];
    out[L]='\0';
    int i=n-1,j=m-1,k=L,carry=0;
    while(i>=0||j>=0||carry){
        int da=(i>=0)?hv(a[i]):0;
        int db=(j>=0)?hv(b[j]):0;
        int s=da+db+carry;
        carry=s>>4;
        out[--k]=hd(s&0xF);
        --i;--j;
    }
    return out+k;
}

int main(void){
    char A[1100], B[1100];
    scanf("%1099s %1099s", A, B);
    printf("%s\n", add_hex(A,B));
    return 0;
}
