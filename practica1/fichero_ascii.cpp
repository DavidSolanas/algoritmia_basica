#include <cstdio>

using namespace std;

int main(){
    char s[224];
    int j=0;
    for (int i=32; i<255; i++){
        if (i==127){
            s[j]=32;
        }
        else{
            s[j]=i;
        }
        j++;
    }
    s[223]=0;
    FILE *f = fopen("ascii.txt", "wt");
    fputs(s, f);
    fclose(f);
}