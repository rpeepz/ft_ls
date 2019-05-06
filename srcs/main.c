/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 21:48:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/05 21:48:41 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		copy_print(char *buf, char *msg, char *attach, int len)
{
	ft_strncpy(buf, msg, (len = LEN(msg)));
	ft_strncpy(buf + len++, attach, 1);
	ft_strncpy(buf + len++, "\n", 1);
	ft_putnstr(buf, len);
	return (1);
}

static t_file	get_dirs(char **av)
{
	t_file	path;

	path.path = 0;
	path.name = 0;
	path.full_path = 0;
	path.next = NULL;
	av++;
	while (**av == '-')
		av++;
	if (**av == '/')
	{
		path.path = *av;
	}
	return (path);
}

static char		get_flags(char **av, char mask, int i, int j)
{
	char	buf[30];

	while ((av[++i]) && av[i][0] == '-' && (j = 1))
	{
		while (IS_FLAG(av[i][j]))
		{
			IF_THEN(av[i][j] == 'R' && (j++), mask |= 1UL << 0);
			IF_THEN(av[i][j] == 'a' && (j++), mask |= 1UL << 1);
			IF_THEN(av[i][j] == 'l' && (j++), mask |= 1UL << 2);
			IF_THEN(av[i][j] == 'r' && (j++), mask |= 1UL << 3);
			IF_THEN(av[i][j] == 't' && (j++), mask |= 1UL << 4);
			IF_RETURN(av[i][j] == '-' && copy_print(buf,
			"ft_ls: illigal option -- ", av[i], 0), mask |= 1UL << 6);
		}
		while (ISNT_FLAG(av[i][j]))
		{
			IF_BREAK(!av[i][j]);
			IF_BREAK(av[i][j] == '-' && !av[i][j + 1]);
			IF_RETURN(av[i][j] == '-' && av[i][j + 1] && copy_print(buf,
			"ft_ls: illigal option -- ", "-", 0), mask |= 1UL << 6);
			IF_RETURN(ISNT_FLAG(av[i][j]) && copy_print(buf,
			"ft_ls: illigal option -- ", av[i], 0), mask |= 1UL << 6);
		}
	}
	return (mask);
}

int				main(int ac, char **av)
{
	char	flags;
	t_file	path;

	if (ac > 1)
	{
		flags = get_flags(av, 0, 0, 0);
		ft_printf("flags found :{%#15.8b}\n", flags);
		if (flags & 1UL << 6)
		{
			ft_putstr("usage: ./ft_ls [-Ralrt] [file ...]\n");
			return (0);
		}
	}
	path = get_dirs(av);
	ft_printf("%s\n", path.path);
	return (0);
}
