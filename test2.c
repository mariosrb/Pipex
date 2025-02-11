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
	int result;
	int start, end;

	if (pipe(pipefd) == -1)
		return 1;
	
	int id = fork();
	if (id == -1)
		return 1;
	
	if (id == 0)
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
		sum += arr[i++];
	printf("la somme %d\n", sum);

	if (id == 0)
	{
		close (pipefd[0]);
		write (pipefd[1], &sum, sizeof(sum));
		close (pipefd[1]);
	}
	else
	{
		int sumChild;
		close (pipefd[1]);
		read (pipefd[0], &sumChild, sizeof(sumChild));
		close (pipefd[0]);

		int total = sumChild + sum;
		printf("total : %d\n", total);
		wait(NULL);
	}
}

	if (ac < 2)
	{
		perror("Nombres darguments invalide !");
		return 0;
	}

	char	*path = "/bin/ls";
	char	**args = malloc(sizeof(char *) * ac);
	if (!args)
		return (1);
	int		i = 1;

	while (av[i])
	{
		args[i - 1] = av[i];
		i++;
	}
	args[i - 1] = NULL;
	char	*env[] = {NULL};
	i = 0;

	if (execve(path, args, env) == -1)
	{
		perror("execve failed");
		return 1;
	}
	printf("si execve reussi pas print ici \n");
	free (args);
	return (0);