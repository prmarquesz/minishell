/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:02:27 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/19 18:49:12 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_pipe(char **matrix)
{
	while (*matrix)
	{
		if (**matrix == '|')
			return (1);
		matrix++;
	}
	return(0);
}

void	free_cmd(t_cmd *cmd)
{
	free(cmd->option);
	free(cmd->name);
	free(cmd);
}

void	run_cmds(char **matrix, char **envp, int input, int output)
{
	t_cmd	*cmd;
	int		fd[2];
	int		pid;

	(void)input;
	cmd = malloc(sizeof(t_cmd));
	matrix = parse_cmd(cmd, matrix, envp);
	if (*matrix && **matrix == '|')
	{
		pipe(fd);
		pid = fork();
		signal(SIGINT, interrupt_process);
		signal(SIGQUIT, quit_process);
		if (pid == 0)
		{
			dup2(input, 0);
			dup2(fd[1], 1);
			if (input != 0)
				close(input);
			close(fd[1]);
			execve(cmd->name, cmd->option, cmd->env);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			matrix++;
			run_cmds(matrix, envp, fd[0], output);
			close(fd[0]);
		}
	}
	else
	{
		pid = fork();
		signal(SIGINT, interrupt_process);
		signal(SIGQUIT, quit_process);
		if (pid == 0)
		{
			dup2(input, 0);
			dup2(output, 1);
			execve(cmd->name, cmd->option, cmd->env);
			if (input != 0)
				close(input);
		}
		else
		{
			wait(NULL);
			if (input != 0)
				close(input);
		}
	}
	free_cmd(cmd);
}