/*
#include <stdio.h>
#include <string.h>

int main(){

  int i;
  char s[10][128] = {0};

  for (i=0;i<10;i++){
    scanf("%s",s[i]);
    if(strcmp(s[i],"$END$") == 0)
      break;  
  }

  for(i=0;i<10;i++)
    if(s[i] != 0 && strcmp(s[i],"$END$") != 0)
      printf("%s\n",s[i]);

  return 0;
}
*/

/*
#include <stdio.h>
#include <string.h>

int main(){
  int i;
  char s[128] = {0};
  
  gets(s);

  //printf("%lu",strlen(s));

  int ssize = strlen(s);

  char r[strlen(s)*2];
  
  strcpy(r,s);

  for(i = 0;i<ssize;i++)
  r[ssize+i] = s[ssize-i-1];

  puts(r);

  return 0;
}
*/

/*
#include <stdio.h>
#include <string.h>
int main(){
  int i,j=0;
  char s[128] = {0};
  char c[128] = {0};
  gets(s);
  int ssize = strlen(s);
  for(i=0;i<ssize;i++){
    if(s[i] != ' '){
      c[j] = s[i];
      j++;
    }
  }

  puts(c);
  return 0;
}
*/

/*
#include <stdio.h>
#include <string.h>
#define Size 128
int main() {
    int i, j;
    char s[Size] = { 0 };
    char key[Size] = { 0 };
    char temp[Size] = { 0 };
    int found = 0;
    gets(s);   //real  
    gets(key); //real

    int ksize = strlen(key);

    for (i = 0; i < Size - ksize; i++) {
        for (j = 0; j < ksize; j++) {
            temp[j] = s[i + j];
        }
        if (strcmp(temp, key) == 0) {
            printf("%d ", i);
            found = 1;
        }
    }
    if (found == 0) printf("-1");

    return 0;
}
*/