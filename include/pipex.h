#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>

// parsing
char	*find_path(char *cmd, char **env);

// exec

// utils
void	free_matrice(char **strs);
void	ft_print(char **strs);

#endif