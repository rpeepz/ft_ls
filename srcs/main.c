/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 21:48:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/02 03:13:35 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char		get_flags(int param_count, char **str, char flags)
{
	while (param_count-- > 0 && *str && **str == '-')
	{
		while ((*str)++)
		{
			if (**str == 'R' && (*str)++)
				flags += 2;//set bit for 'R' flag
			if (**str == 'a' && (*str)++)
				flags += 2;//set bit for 'a' flag
			if (**str == 'l' && (*str)++)
				flags += 2;//set bit for 'l' flag
			if (**str == 'r' && (*str)++)
				flags += 2;//set bit got 'r' flag
			if (**str == 't' && (*str)++)
				flags += 2;//set bit for 't' flag
			else if (**str != 'R' || **str != 'a' || **str != 'l' ||
					**str != 'r' || **str != 't' || **str == '\0')
				break ;//if flag is invalid
		}
		str++;
	}
	return (flags);
}

int				main(int ac, char **av)
{
	char	flags;

	flags = get_flags(ac - 1, av + 1, 0);
	ft_printf("%d\n", ac);
	ft_printf("%c\n", flags + '0');
	return (0);
}
