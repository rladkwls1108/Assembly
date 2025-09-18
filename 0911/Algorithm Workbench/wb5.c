#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* add_base_b(const char* a, const char* b, int base){
    int n=strlen(a), m=strlen(b);
    int L=(n>m?n:m)+1;
    static char out[2000];
    out[L]='\0';
    int i=n-1,j=m-1,k=L,carry=0;
    while(i>=0||j>=0||carry){
        int da=(i>=0)?a[i]-'0':0;
        int db=(j>=0)?b[j]-'0':0;
        int s=da+db+carry;
        carry=s/base;
        out[--k]=(s%base)+'0';
        --i;--j;
    }
    return out+k;
}

int main(void){
    char A[1100], B[1100]; int base;
    scanf("%d %1099s %1099s",&base,A,B);
    printf("%s\n", add_base_b(A,B,base));
    return 0;
}
