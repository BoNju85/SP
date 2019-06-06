#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <stdint.h>
using namespace std;

int line1, line2;
const int N = 1<<20;
uint64_t New[1024], Old[1024];
int array[1000][1000] = {{0}};

int max(int a, int b){
    return (a>b)? a:b;
}

void LCS(int x, int y){
    for(int i=1; i<=x; i++){
        for(int j=1; j<=y; j++){
           array[i][j] = max( max(array[i-1][j-1]+(New[i-1]==Old[j-1]), array[i-1][j]) , array[i][j-1] );
        }
    }
}

int main(){
    int n;
    char order[6];
    char data[20];
    char *buffer = new char[N];
    FILE *fp1, *fp2;
    string path1, path2;
    string s;
    while(scanf("%s", order) == 1){
        if(order[0] == 'u'){
            path1 = "client/";
            path2 = "server/";
            scanf("%s", data);
            path1 += data;
            path2 += data;
            fp1 = fopen(path1.c_str(), "r");
            fp2 = fopen(path2.c_str(), "r");
            line1 = 0, line2 = 0;
            if(fp1 == NULL){
                while(n = fread(buffer, 1, N, fp2)){                    
                    for(int i=0; i<n; i++)
                        if(*(buffer+i) == '\n')
                            line2++;
                }
                printf("0 %d\n", line2);
                fflush(stdout);
                s = "rm ", s += path2;
                system(s.c_str());
            }else{
                uint64_t ret = 0;
                while(n = fread(buffer, 1, N, fp1)){
                    for(int j=0; j<n; j++){
                        ret = ret*131 + *(buffer+j);
                        if(*(buffer+j) == '\n'){
                            New[line1] = ret;
                            ret = 0;
                            line1++;
                        }
                    }
                }
                fclose(fp1);
                if(fp2 != NULL){
                    ret = 0;
                    while(n = fread(buffer, 1, N, fp2)){
                        for(int i=0; i<n; i++){
                            ret = ret*131 + *(buffer+i);
                            if(*(buffer+i) == '\n'){
                                Old[line2] = ret;
                                ret = 0;
                                line2++;
                            }
                        }
                    }
                    fclose(fp2);
                }
                LCS(line1, line2);
                int lcs = array[line1][line2];
                printf("%d %d\n", line1 - lcs, line2 - lcs);
                fflush(stdout);
                s = "cp ", s += path1 + " server/";
                system(s.c_str());
            }
        }
        else
            return 0;
    }
}
