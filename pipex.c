/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:26:52 by ktoivola          #+#    #+#             */
/*   Updated: 2024/02/20 17:53:54 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_execute(t_pipex *pipex_args, int cmd_n, char **env)
{
	char	**cmds;
	char	*exec_path;

	cmds = ft_parse_commands(pipex_args->cmd_args[cmd_n]);
	if (cmds == NULL)
		exit(EXIT_CMD_NOT_FOUND);
	if (access(cmds[0], F_OK & X_OK) == 0)
		exec_path = cmds[0];
	else
		exec_path = ft_get_env_paths(pipex_args, cmds);
	if (exec_path == NULL || execve(exec_path, cmds, env) < 0)
	{
		free(exec_path);
		ft_free_strs(cmds);
		perror("pipex: commad not found");
		exit(EXIT_CMD_NOT_FOUND);
	}
}

static void	child_process1(t_pipex *pipex_args, char **env)
{
	int	fd_in;

	fd_in = open(pipex_args->cmd_args[1], O_RDONLY);
	if (fd_in < 0)
		perror("pipex");
	dup2(fd_in, STDIN_FILENO);
	dup2(pipex_args->pipe[1], STDOUT_FILENO);
	close(pipex_args->pipe[0]);
	ft_execute(pipex_args, 2, env);
}

static void	child_process2(t_pipex *pipex_args, char **env)
{
	int	fd_out;

	fd_out = open(pipex_args->cmd_args[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd_out < 0)
		perror("pipex");
	dup2(fd_out, STDOUT_FILENO);
	dup2(pipex_args->pipe[0], STDIN_FILENO);
	close(pipex_args->pipe[1]);
	ft_execute(pipex_args, 3, env);
}

static void	ft_pipex(t_pipex *pipex_args, char **env)
{
	pid_t	pid[2];
	int		status;

	pid[0] = fork();
	if (pid[0] < 0)
		exit(EXIT_FORK_ERROR);
	if (pid[0] == 0)
		child_process1(pipex_args, env);
	pid[1] = fork();
	if (pid[1] < 0)
		exit(EXIT_FORK_ERROR);
	if (pid[1] == 0)
		child_process2(pipex_args, env);
	close_all_pipes(pipex_args);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex_args;

	if (argc != 5)
		exit(0);
	pipex_args = malloc(sizeof(t_pipex));
	if (pipex_args == NULL)
		exit(EXIT_MALLOC_FAIL);
	ft_init_pipex(pipex_args, argc);
	pipex_args->cmd_args = argv;
	pipex_args->env_paths = envp;
	if (pipe(pipex_args->pipe) == -1)
		exit(EXIT_PIPE_ERROR);
	ft_pipex(pipex_args, envp);
	close_all_pipes(pipex_args);
}
