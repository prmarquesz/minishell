/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:59:47 by proberto          #+#    #+#             */
/*   Updated: 2022/02/17 18:48:10 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Count number of arguments and set error if is greater than 1
 * 
 * @param matrix matrix of inputs
 * @return int number of arguments
 */
int	number_of_args(char **matrix)
{
	int	size;

	size = 0;
	while (*matrix)
	{
		matrix++;
		size++;
	}
	if (size > 2)
		g_error_status = 1;
	return (size);
}

/**
 * @brief Checks if the argument is a digit
 * 
 * @param status argument in a string
 * @return int 1 if is valid or 0 if isn't
 */
int	valid_exit(char *status)
{
	if (!status)
		return (1);
	while (*status)
	{
		if (!ft_isdigit(*status))
			return (0);
		status++;
	}
	return (1);
}

/**
 * @brief Simulates the shell's built-in exit, which exits the shell.
 * 
 * @return void 
 */
void	ft_exit(char **exit_status, t_var *env_list, char **matrix, t_cmd *cmd)
{
	int	ex;
	int	args;

	args = number_of_args(exit_status);
	if (!valid_exit(exit_status[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(*exit_status, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		g_error_status = 2;
	}
	else if (args > 2)
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	else
	{
		if (args == 1)
			ex = g_error_status;
		else
			ex = ft_atoi(exit_status[1]);
		free_cmd(cmd);
		free_matrix(matrix);
		free_var_list(env_list);
		exit(ex);
	}
}
