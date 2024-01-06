/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:31:38 by ktoivola          #+#    #+#             */
/*   Updated: 2024/01/06 16:33:44 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *ft_get_path(char **env)
{
	while (*env)
	{
		if (ft_strnstr(*env, "PATH", 5))
			return (*env + 5);
		env++;
	}
	return (NULL);
}

void	ft_init_pipex(t_pipex *pipex_args, int argc)
{
	if (pipex_args == NULL)
		return ;
	pipex_args->pipe[0] = 0;
	pipex_args->pipe[1] = 1;
	pipex_args->here_doc = 0;
	pipex_args->is_invalid_infile = 0;
	pipex_args->env_path = NULL;
	pipex_args->cmd_args = NULL;
	pipex_args->cmd_count = argc - 3;
	return ;
}

void	ft_check_args(t_pipex *pipex_args, char **argv, char **envp)
{
	int	i;
	
	i = 0;
	pipex_args->pipe[0] = open(argv[1], O_RDONLY);
	if (pipex_args->pipe[0] < 0)
	{
		perror("Error on open");
		exit(EXIT_FILE_OPEN_ERROR);
	}
	pipex_args->pipe[1] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC | 0644);
	if (pipex_args->pipe[1] < 0)
	{
		perror("Error on open");
		exit(EXIT_FILE_OPEN_ERROR);
	}
	pipex_args->cmd_args = argv;
	pipex_args->env_path = envp;
}
void	ft_clear_all(t_pipex *pipex_args)
{
	close(pipex_args->pipe[0]);
	close(pipex_args->pipe[1]);
}