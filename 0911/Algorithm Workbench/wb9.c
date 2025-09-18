#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* sub_unsigned_bin(const char* big, const char* small){
    int n=strlen(big), m=strlen(small);
    static char out[2000];
    out[n]='\0';
    int i=n-1,j=m-1,k=n-1,borrow=0;
    while(i>=0){
        int A=big[i]-'0'-borrow;
        int B=(j>=0)?small[j]-'0':0;
        if(A<B){ A+=2; borrow=1;} else borrow=0;
        out[k]= (A-B)+'0';
        --i;--j;--k;
    }
    int start=0; while(out[start]=='0' && out[start+1]) start++;
    return out+start;
}

int main(void){
    char A[1024], B[1024];
    scanf("%1023s %1023s", A, B);
    if(strlen(A)<strlen(B) || (strlen(A)==strlen(B) && strcmp(A,B)<0)){
        char tmp[1024]; strcpy(tmp,A); strcpy(A,B); strcpy(B,tmp);
    }
    printf("%s\n", sub_unsigned_bin(A,B));
    return 0;
}
