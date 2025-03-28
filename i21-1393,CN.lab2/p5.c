// Muhammad Abdullah Nawaz

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_LINE_LENGTH 1024

int main() 
{
 char line[MAX_LINE_LENGTH];
    FILE *file;
    unsigned long long u1, st1, m1, d1, t1, q1, s1,u2, st2, m2, d2, t2, q2, s2,total_diff,idle_diff;
    double cpu_performance = 0.0 ;       

    while (1) {
      file = fopen("p6.txt", "r");
   if (file == NULL) {
     perror(" error opening file from system ");
       return 1;
        }

   char* input1 = fgets(line, sizeof(line), file);
      fclose(file);
      
      sscanf(line, input1,
               &u2, &m2, &st2, &d2, &t2, &q2, &q2);

        sleep(1);

     file = fopen("p6.txt", "r");
   if (file == NULL) {
     perror(" error opening file from system  ");
       return 1;
        }

   char* input2 = fgets(line, sizeof(line), file);
      fclose(file);
      
      sscanf(line, input2,
               &u2, &m2, &st2, &d2, &t2, &q2, &q2);

    total_diff = (u2 + m2 + st2 + d2 + t2 + q2 + s2) -
                                        (u1 + m1 + st1 + d1 + t1 + q1 + s1);
    idle_diff = d2 - d1 + t2 - t1;

        cpu_performance = ((total_diff - idle_diff) * 100.0) / total_diff;
        


// Print on terminal
        printf("average CPU utilization is : %.2f%%\n", cpu_performance);
    }

    return 0;
}

