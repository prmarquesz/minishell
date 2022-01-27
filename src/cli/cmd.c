/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:55:52 by proberto          #+#    #+#             */
/*   Updated: 2022/01/27 10:22:32 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	launch_builtins(char *cmd, char **arg, t_var *env_list, int fd)
{
	if (ft_strncmp(cmd, "pwd", comp_size(cmd, "pwd")) == 0)
		pwd(fd);
	else if (ft_strncmp(cmd, "env", comp_size(cmd, "env")) == 0)
		env(env_list, fd);
	else if (ft_strncmp(cmd, "echo", comp_size(cmd, "echo")) == 0)
		echo(arg, fd);
	else if (ft_strncmp(cmd, "cd", comp_size(cmd, "cd")) == 0)
		cd(arg[1], env_list);
	else if (ft_strncmp(cmd, "export", comp_size(cmd, "export")) == 0)
		export(env_list, &arg[1]);
	else if (ft_strncmp(cmd, "unset", comp_size(cmd, "unset")) == 0)
		env_list = unset(env_list, &arg[1]);
	else if (ft_strncmp(cmd, "exit", comp_size(cmd, "exit")) == 0)
		ft_exit();
	else
		return (FALSE);
	return (TRUE);
}

void	launch_execve(char *path, char **arg, char **envp, int fd[2])
{
	pid_t	pid;

	if (access(path, F_OK) == 0)
	{
		pid = fork();
		signal(SIGINT, interrupt_process);
		signal(SIGQUIT, quit_process);
		if (pid == 0)
		{
			dup2(fd[0], 0);
			dup2(fd[1], 1);
			if (execve(path, arg, envp) == -1)
			{
				perror("minishell");
				exit(EXIT_FAILURE);
			}
			if (fd[0] != 0)
				close(fd[0]);
			if (fd[1] != 1)
				close(fd[1]);
			fd[0] = 0;
		}
		else if (pid == -1)
			ft_putendl_fd("\nFailed forking child..", 2);
		else
		{
			wait(NULL);
			if (fd[0] != 0)
				close(fd[0]);
			if (fd[1] != 1)
				close(fd[1]);
			fd[0] = 0;
		}
	}
	else
		ft_putendl_fd("minishell: command not found: ", 2);
}

void	eval(char *command_line, t_var *env_list, char **envp)
{
	char	**run;
//	char	**path;
//	char	*valid_path;
//	int		i;

	//check redirect in/out
	run = string_parse(command_line, env_list);
	run_cmds(run, envp, STDIN_FILENO, STDOUT_FILENO, env_list);

//	path = parse_paths(envp);
//	if (*run == NULL || *path == NULL)
//		return ;
//	valid_path = check_path(path, run[0]);
//	if (valid_path == NULL)
//		valid_path = ft_strdup(run[0]);
//	if (launch_builtins(run[0], run, env_list, 1) == TRUE)
//		i = 0;
//	else
//		launch_execve(valid_path, run, envp);
//	i = 0;
//	while (run[i])
//		free(run[i++]);
//	i = 0;
//	while (path[i])
//		free(path[i++]);
	free_matrix(run);
//	free(path);
//	free(valid_path);
}
