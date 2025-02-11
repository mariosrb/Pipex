#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>


#include "./libft/libft.h"

int main (int ac, char **av)
{
	int pipefd[2];
	// pipefd[0]: lecture
	// pipefd[1]: ecriture

	if (pipe(pipefd) == -1)
	{
		perror("Erreur creation du pipe !");
		return (1);
	}

	int pid = fork();
	if (pid == -1)
	{
		perror ("Erreur fork!");
		return (1);
	}

	if (pid == 0)
	{
		// process enfant
		char *receive = malloc(100);
		int	file = open("file.txt", O_WRONLY | O_CREAT, 0777);
		if (file == -1)
		{
			perror("Erreur ouverture file.txt");
			return (1);
		}
		dup2(file, 1);
		close(pipefd[1]);
		read(pipefd[0], &receive, sizeof(receive));
		printf("Le message que l'enfant a recu :\n%s\n", receive);
		close(pipefd[0]);
		close(file);
	}
	else
	{
		// process parent
		char *envoyer = "Hello world";
		close(pipefd[0]);
		write(pipefd[1], &envoyer, ft_strlen(envoyer) + 1);
		close(pipefd[1]);
		wait(NULL);
	}
	return (0);
}
