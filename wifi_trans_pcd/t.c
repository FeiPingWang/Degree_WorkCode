#include <stdio.h>
#include <stdlib.h>
int main ()
{
  FILE * pFile;
  int buffe[1024] = "wfp";
  if((pFile = fopen ("myfile.txt", "w"))==NULL)
  {
      printf("cant open the file");
      exit(0);
  }
  //可以写多个连续的数据(这里一次写4个)
  buffer[4] = '\0';
  fwrite (buffer , sizeof(char), 4, pFile);
  fclose (pFile);
  return 0;
}
