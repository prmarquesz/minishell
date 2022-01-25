/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:08:15 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/25 15:59:02 by guferrei         ###   ########.fr       */
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
	if (mode == 2)
	{
		heredocs_prompt(matrix, name);
		return (open("/tmp/heredoc", O_RDONLY));
	}
	else
		return (open(name, O_RDONLY));
}
