/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:08:15 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/19 18:47:20 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input_redirects(char **matrix)
{
	char	*name;
	int		mode;

	mode = check_redirects(matrix, '<');
	if (!mode)
		return (0);
	name = file_name(matrix, '<');
	if (name == NULL)
		return (-1);
	return (open(name, O_RDONLY));
}
