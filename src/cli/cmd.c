/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:55:52 by proberto          #+#    #+#             */
/*   Updated: 2021/11/30 14:46:06 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(char *cmd)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (ft_strncmp(cmd, "pwd", len) == 0)
		pwd();
	else if (ft_strncmp(cmd, "cd ", 3) == 0)
		cd(&cmd[3]);
	else if (ft_strncmp(cmd, "echo ", 5) == 0)
		echo(&cmd[5]);
}
