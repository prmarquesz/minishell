/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:55:52 by proberto          #+#    #+#             */
/*   Updated: 2022/02/01 09:04:05 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_matrix(char **matrix)
{
	while(*matrix)
		printf("cl: %s\n", *matrix++);
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
		ft_exit(arg, env_list);
	else
		return (FALSE);
	return (TRUE);
}

void	launch_execve(t_cmd *cmd, int input, int output)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, interrupt_process);
	signal(SIGQUIT, quit_process);
	if (pid == 0)
	{
		dup2(input, 0);
		dup2(output, 1);
		if (execve(cmd->name, cmd->option, cmd->env) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		if (input != STDIN_FILENO)
			close(input);
		if (output != STDOUT_FILENO)
			close(output);
	}
	else if (pid == -1)
		ft_putendl_fd("\nFailed forking child..", 2);
	wait(NULL);
	reset_io(&input, &output);
}

static void	free_cmd(t_cmd *cmd)
{
	free(cmd->option);
	free(cmd->name);
	free(cmd);
}

void run_command_line(char **cl, t_env_var *env, int input, int output)
{
	t_cmd	*cmd;
	int		fd[2];

	(void)input;
	(void)output;
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return ;
	cl = parse_cmd(cmd, cl, env->envp, env->list);
	if (!cl)
	{
		//EXIT STATUS 2
		return ;
	}
	set_io(cl, fd, &input);
	if (input == -1)
	{
		//EXIT STATUS 1, FILE NOT FOUND
		return ;
	}
	if (!cmd->option[0])
	{
		//Se for só redirect, sem commando, exit status = 0
		return ;
	}
	// printf("input: %d\nfd[0]: %d\nfd[1]: %d\n", input, fd[0], fd[1]);
	if (launch_builtins(cmd->option[0], cmd->option, env->list, fd[1]))
		reset_io(&input, &fd[1]);
	else
	{
		if (access(cmd->name, F_OK) == 0)
			launch_execve(cmd, input, fd[1]);
		else
		{
			//Apenas printando o erro corretamente, ocupa muitas linhas então vai precisar de refactor
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putstr_fd(cmd->option[0], 2);
			write(2, "\n", 1);
		}
	}
	free_cmd(cmd);
	while (*cl && **cl++ != '|')
		;
	if (*cl && **cl != '|')
		run_command_line(cl, env, fd[0], fd[1]);
}

void	eval(char *command_line, t_var *env_list, char **envp)
{
	char		**run;
	t_env_var	env;
//	char	**path;
//	char	*valid_path;
//	int		i;

	//check redirect in/out
	env.envp = envp;
	env.list = env_list;
	run = string_parse(command_line, env_list, envp);
	if (!*run)
		return ;
	// run_cmds(run, envp, STDIN_FILENO, STDOUT_FILENO, env.list);
	run_command_line(run, &env, STDIN_FILENO, STDOUT_FILENO);

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
