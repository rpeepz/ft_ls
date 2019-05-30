/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 01:54:58 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/30 05:12:11 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		copy_print(char *buf, char *msg, char attach, int len)
{
	ft_strncpy(buf, msg, (len = LEN(msg)));
	ft_strncpy(buf + len++, &attach, 1);
	ft_strncpy(buf + len++, "\n", 1);
	ft_putnstr(buf, len);
	return (1);
}

void			mask_flag(char *mask, char option)
{
	if (option == 'R')
		*mask |= 1 << 0;
	else if (option == 'a')
		*mask |= 1 << 1;
	else if (option == 'l')
		*mask |= 1 << 2;
	else if (option == 'r')
		*mask |= 1 << 3;
	else if (option == 't')
		*mask |= 1 << 4;
	else if (option == '1')
		*mask |= 1 << 5;
	else if (option == 'f')
	{
		*mask |= 1 << 6;
		*mask |= 1 << 1;
	}
}

char			get_flags(char **av, char bt, int i, int j)
{
	char	buf[30];

	while ((av[++i]) && av[i][0] == '-' && (j = 1))
	{
		while (IS_FLAG(av[i][j]) || IS_FLAG2(av[i][j]))
		{
			IF_RETURN(av[i][j] == '-' && copy_print(buf,
			"ft_ls: illigal option -- ", av[i][j], 0), '~');
			mask_flag(&bt, av[i][j]);
			j++;
		}
		while (NOT_FLAG(av[i][j]) && NOT_FLAG2(av[i][j]))
		{
			IF_BREAK(!av[i][j]);
			IF_BREAK(av[i][j] == '-' && !av[i][j + 1]);
			IF_RETURN((av[i][j] == '-' && av[i][j + 1] || (NOT_FLAG(av[i][j]) &&
				NOT_FLAG2(av[i][j]))) && copy_print(buf,
				"ft_ls: illigal option -- ", av[i][j], 0), '~');
		}
	}
	return (bt);
}

t_file			*get_dirs(char **av, int i, int j)
{
	t_file	*paths;

	while (av[i])
	{
		if (av[i][j] == '-')
			i++;
		else
			break ;
	}
	if (!av[i])
	{
		if (!(paths = t_fileinit(".")))
			return (t_filedel(paths));
	}
	else
	{
		if (!(paths = t_fileinit(av[i])))
			return (t_filedel(paths));
		while (av[++i])
			if (t_fileadd(&paths, av[i]))
				return (t_filedel(paths));
	}
	return (paths);
}
