#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main (int ac, char **av)
{
	int arr[] = {1, 2, 3, 4 , 1, 2, 4, 2, 23, 6};
	int arrSize = sizeof(arr) / sizeof(int);
	int pipefd[2]; // tableau pour stocker nos fd
	int pipefd2[2];
	int result;
	int start, end;



	// creation du pipe
	if (pipe(pipefd) == -1 || pipe(pipefd2) == -1)
		return 1;

	int id1 = fork();
	if (id1 == -1)
		return 2;
	
	if (id1 == 0)
	{
		start = 0;
		end = arrSize / 2;
	}
	else
	{
		start = arrSize / 2;
		end = arrSize;
	}
	int sum, i;
	sum = 0;
	i = start;
	while (i < end)
	{
		sum += arr[i];
		i++;
	}

	printf("somme partiel calcule : %d\n", sum);

	if (id1 == 0)
	{
		close(pipefd[0]);
		write(pipefd[1], &sum, sizeof(sum));
		close(pipefd[1]);
	}
	else 
	{
		int sumChild;
		close(pipefd[1]);
		read(pipefd[0], &sumChild, sizeof(sumChild));
		close(pipefd[0]);
		
		int totalsum;
		totalsum = sum + sumChild;
		printf("%d\n", totalsum);
		wait(NULL);
	}
	// pipefd[1] : cote ecriture (on poste la lettre)
	// pipefd[0] : cote lecture (on recoit la lettre)

	return (0);
}