/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 23:03:12 by proberto          #+#    #+#             */
/*   Updated: 2021/11/30 17:24:09 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Gets the current working directory.
 * 
 * @return char* pointer to the current working directory
 */
char	*get_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	return (tmp);
}

/**
 * @brief Prints the current working directory.
 * 
 * @return void
 */
void	pwd(void)
{
	char	*pwd;
	size_t	len;

	pwd = get_pwd();
	len = ft_strlen(pwd);
	write(1, pwd, len);
	write(1, "\n", 1);
	free(pwd);
}
