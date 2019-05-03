/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 21:48:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/03 12:33:20 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		copy_print(char *msg, char *attach, char *buf, int len)
{
	ft_strncpy(buf, msg, (len = LEN(msg)));
	ft_strncpy(buf + len++, attach, 1);
	ft_strncpy(buf + len++, "\n", 1);
	ft_putnstr(buf, len);
	return (1);
}

static char		get_flags(int index, int param_count, char **str, char mask)
{
	char	buf[40];

	while ((str++) && index++ < param_count && **str == '-' && ((*str)++))
	{
		if (IS_FLAG(**str))
			while (IS_FLAG(**str))
			{
				IF_THEN((**str == 'R' && (*str)++), mask |= 1UL << 0);
				IF_THEN((**str == 'a' && (*str)++), mask |= 1UL << 1);
				IF_THEN((**str == 'l' && (*str)++), mask |= 1UL << 2);
				IF_THEN((**str == 'r' && (*str)++), mask |= 1UL << 3);
				IF_THEN((**str == 't' && (*str)++), mask |= 1UL << 4);
			}
		else if (ISNT_FLAG(**str))
		{
			IF_RETURN(!**str, mask);
			IF_BREAK(**str == '-' && !(*(*str + 1)));
			if (**str == '-' && *(*str + 1))
				ft_putstr("2ft_ls: illigal option -- -\n");
			else if (ISNT_FLAG(**str))
				copy_print("1ft_ls: illigal option -- ", *str, buf, 0);
			return (1UL << 7);
		}
	}
	return (mask);
}

int				main(int ac, char **av)
{
	t_file	path;

	path.flags = get_flags(0, ac - 1, av, 0);
	ft_printf("ac: %15.4f\n", (float)ac);
	ft_printf("fl: %#15.6b\n", path.flags);
	if (path.flags & 1UL << 7)
		ft_putstr("usage: ./ft_ls [-Ralrt] [file ...]\n");
	return (0);
}
