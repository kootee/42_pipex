/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:31:38 by ktoivola          #+#    #+#             */
/*   Updated: 2024/01/15 13:36:02 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_strs(char **strs_to_free)
{
	int	i;

	i = 0;
	while (strs_to_free[i])
	{
		free(strs_to_free[i]);
		i++;
	}
	free(strs_to_free);
}

void	ft_init_pipex(t_pipex *pipex_args, int argc)
{
	pipex_args->pipe[0] = 0;
	pipex_args->pipe[1] = 0;
	pipex_args->fd_IO[0] = 0;
	pipex_args->fd_IO[1] = 0;
	pipex_args->here_doc = 0;
	pipex_args->is_invalid_infile = 0;
	pipex_args->env_paths = NULL;
	pipex_args->cmd_args = NULL;
	pipex_args->cmd_count = argc - 3;
}

char	*ft_getenv(char **envp, char *str)
{
	while (*envp)
	{
		if (ft_strnstr(*envp, str, 4))
			return(*envp + 5);
		envp++;
	}
	return (NULL);
}

char *ft_get_env_paths(t_pipex *pipex_args, char **cmds)
{
	char	**all_env;
	char	*exec_path;
	char	*temp_path;
	int		i;
	
	i = 0;
	all_env = ft_split(ft_getenv(pipex_args->env_paths, "PATH"), ':');
	if (all_env == NULL)
		exit(EXIT_FAILURE);
	while (all_env[i])
	{
		temp_path = ft_strjoin(all_env[i], "/");
		exec_path = ft_strjoin(temp_path, cmds[0]);
		free(temp_path);
		if (access(exec_path, F_OK & X_OK) == 0)
		{
			ft_free_strs(all_env);
			return (exec_path);
		}
		free(exec_path);
		i++;
	}
	ft_free_strs(all_env);
	return (NULL);
}

void	ft_check_args(t_pipex *pipex_args, char **argv)
{
	pipex_args->fd_IO[0] = open(argv[1], O_RDONLY);
	if (pipex_args->fd_IO[0] < 0)
	{
		perror("Error on opening infile");
		exit(EXIT_FAILURE);
	}
	pipex_args->fd_IO[1] = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex_args->fd_IO[1] < 0)
	{
		perror("Error on opening outfile");
		exit(EXIT_FAILURE);
	}
}
/* IS THIS necessary */
void	ft_close_all(t_pipex *pipex_args)
{
	close(pipex_args->pipe[0]);
	close(pipex_args->pipe[1]);
	close(pipex_args->fd_IO[0]);
	close(pipex_args->fd_IO[1]);
}