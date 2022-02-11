/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 08:06:15 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/11 08:31:22 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sinalize(char *dest)
{
	while (dest)
		dest++;
	*dest = 3;
}

int	check_special_chars(char *str, char c)
{
	if (c != '"' && c != '\'')
		return (0);
	if (*str == '>' || *str == '<')
	{
		if ((str + 1) && *(str + 1) == c)
			return (1);
		if (*(str + 1) && *(str + 2)
			&& *(str + 1) == *str && *(str + 2) == c)
			return (1);
		else
			return (0);
	}
	if (*str == '|')
	{
		if ((str + 1) && *(str + 1) == c)
			return (1);
		else
			return (0);
	}
	return (0);
}

char	*skip_chars(char *src)
{
	static char	quote;

	if (quote != *src)
	{
		quote = *src;
		src++;
	}
	else if (quote == *src)
	{
		quote = 0;
		src++;
	}
	return (src);
}
