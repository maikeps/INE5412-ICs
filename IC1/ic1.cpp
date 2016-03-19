#include <string>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>

using namespace std;
int main ()
{
   // include declarations you need
   int numChilds = 5;
   int count = 0;
   int pid[numChilds];
   /* Repeat 5 times */
   for(int i = 0; i < numChilds; i++){
      cout << "Parent process " << getpid() << ": Creating child" << endl;
      /* Duplicate this process */
      pid[i] = fork(); 
      /* If there was an error on duplication then */
      if(pid[i] < 0){
            cout << "Error on fork()" << endl;
            return -1;  
      }
      /* If child-process is running then */
      if(pid[i] == 0){
         cout << "Child process " << getpid() << ": Running" << endl;
         count++;
         /* Sleep for 1 second */
         sleep(1);
         cout << "Child process " << getpid() << ": Exiting with status " << count << endl;
         exit(count);
      }
   }

   /* if this is the parent-process then */
   // Todos os filhos dão exit logo depois de serem criados, não é necessario colocar um if aqui
   int errno, status, sum = 0;
   /* Parent-process waits for all children to exit, adding each status to the sum variable */
   for(int i = 0; i < numChilds; i++){
      while (-1 == waitpid(pid[i], &status, 0)){
         cout << "Parent process " << getpid() << ": Waiting children to exit" << endl;
      }
      if (WIFEXITED(status)) {
         sum += WEXITSTATUS(status);
      }
   }
   cout << "Parent process " << getpid() << ": Exiting with sum " << sum << endl;
   /*  */
   return count;
}
