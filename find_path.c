#include "include/pipex.h"


void	ft_print(char **strs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (strs[i] != NULL)
	{
		while (strs[i][j])
		{
			write (1, &strs[i][j], 1);
			j++;
		}
		write (1, "\n", 1);
		i++;
		j = 0;
	}
	if (strs[i] == NULL)
		write (1, "null", 4);
}

static char	*create_cmd_path(char *path, char *cmd)
{
	char	*final;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	final = ft_strjoin(tmp, cmd);
	free(tmp);
	return (final);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*final_path;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		final_path = create_cmd_path(paths[i], cmd);
		if (access(final_path, F_OK) == 0)
		{
			free_matrice(paths);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	free_matrice(paths);
	return (NULL);
}

int main(int ac, char **av, char **env)
{
	char *cs;
	cs = find_path("ls", env);
	printf("%s\n", cs);
	free(cs);
	return (0);
}

int main (int argc, char **argv, char **env)
{
	int		i;
	int		y;
	char	**all_path;
	char	**commande;

	// isoler la commande 
	commande = ft_split(argv[1], ' ');
	if (!commande)
		return (1);

	// trouver le chemin et le fusionner avec la commande 
	i = 0;
	y = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	all_path = ft_split(env[i], ':');
	if (!all_path)
		return (1);
	while (all_path[y])
	{
		char *tmp1 = all_path[y];
		all_path[y] = ft_strjoin(all_path[y], "/");
		free(tmp1);

		char *tmp2 = all_path[y];
		all_path[y] = ft_strjoin(all_path[y], commande[0]);
		free(tmp2);
		y++;
	}

	y = 0;
	while (access(all_path[y], F_OK) != 0)
		y++;
	if (!all_path[y])
	{
		perror("Commande non trouvee\n");
		exit(EXIT_FAILURE);
	}
	printf("\nle chemin est : %s\n", all_path[y]);
	free_matrice(commande);
	free_matrice(all_path);
	return (0);
}