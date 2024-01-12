/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:31:38 by ktoivola          #+#    #+#             */
/*   Updated: 2024/01/12 10:56:50 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_on_error(char **cmds)
{
	while (*cmds)
	{
		free(*cmds);
		cmds++;
	}
	free(cmds);
}

void	ft_init_pipex(t_pipex *pipex_args, int argc)
{
	if (pipex_args == NULL)
		return ;
	pipex_args->pipe[0] = 0;
	pipex_args->pipe[1] = 1;
	pipex_args->here_doc = 0;
	pipex_args->is_invalid_infile = 0;
	pipex_args->env_paths = NULL;
	pipex_args->cmd_args = NULL;
	pipex_args->cmd_count = argc - 3;
	pipex_args->fd_IO[0] = 0;
	pipex_args->fd_IO[1] = 0;
	return ;
}

char *ft_get_env_paths(t_pipex *pipex_args, int cmd_n)
{
	char	**all_env;
	char	*exec_path;
	
	while (*pipex_args->env_paths)
	{
		if (ft_strnstr(*pipex_args->env_paths, "PATH", 5))
		{			
			all_env = ft_split((*pipex_args->env_paths + 5), ':'); //malloc protect
			while (*all_env)
			{
				exec_path = ft_strjoin(*all_env, "/");
				exec_path = ft_strjoin(exec_path, pipex_args->cmd_args[cmd_n]);
				if (access(exec_path, F_OK & X_OK) < 0)
					all_env++;
				else
				{
					//free all_env
					return (exec_path);
				}
			}
		}		
		pipex_args->env_paths++;
	}
	return (NULL);
}

void	ft_check_args(t_pipex *pipex_args, char **argv, char **envp)
{
	int	i;
	
	i = 0;
	pipex_args->fd_IO[0] = open(argv[1], O_RDONLY);
	if (pipex_args->fd_IO[0] < 0)
	{
		perror("Error on opening infile");
		exit(EXIT_FILE_OPEN_ERROR);
	}
	pipex_args->fd_IO[1] = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex_args->fd_IO[1] < 0)
	{
		perror("Error on opening outfile");
		exit(EXIT_FILE_OPEN_ERROR);
	}
	pipex_args->cmd_args = argv;
	pipex_args->env_paths = envp;
}

void	ft_close_all(t_pipex *pipex_args)
{
	close(pipex_args->pipe[0]);
	close(pipex_args->pipe[1]);
	close(pipex_args->fd_IO[0]);
	close(pipex_args->fd_IO[1]);
}