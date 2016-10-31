#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define random()  (float)rand()/(float)(RAND_MAX)

//mimics the wheights the function will receive
void fill (float *wheight1)
{
  for (size_t i = 0; i < 4; i++)
    {
      *(wheight1+i) = random();
    }
}

//saves the wheights in a .txt file
void save (float *wheight1)
{
  FILE *fd = fopen("test.txt", "w+");
if (fd == NULL)
  {
    perror("Error opning file :");
exit(1);
  }
const char *text = "Wheights saved :";
fprintf(fd, "%s\n", text);
 for (size_t i = 0; i < 4; i++)
   fprintf(fd,"%.2f\n",*(wheight1+i));
fclose(fd);
}

int main (void)
{
  float *w1;
  w1 = malloc(sizeof(float)*4);
  fill(w1);
  save(w1);
  free(w1);
}
