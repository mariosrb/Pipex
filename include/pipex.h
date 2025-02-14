#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>

typedef struct s_pipex
{
    int     infile;      // Fichier d'entrée (comme dans "< infile")
    int     outfile;     // Fichier de sortie (comme dans "> outfile") 
    char    *cmd1_path;  // Chemin complet de la première commande
    char    *cmd2_path;  // Chemin complet de la deuxième commande
    char    **cmd1_args; // Arguments de la première commande
    char    **cmd2_args; // Arguments de la deuxième commande
    char    **env;       // Variables d'environnement
    int     pipe_fd[2];  // Les deux bouts du pipe
}   t_pipex;

// parsing
char	*find_path(char *cmd, char **env);

// check
int		check_args(int ac);
int		check_files(char *infile, char *outfile, t_pipex *pipex);

// exec


// utils
void	free_matrice(char **strs);
void	free_pipex(t_pipex *pipex);
void	ft_print(char **strs);

#endif