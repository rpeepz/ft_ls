/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 01:54:58 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/02 20:07:07 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		mask_flag(char *mask, char option)
{
	if (option == '1')
		*mask |= 0x1;
	else if (option == 'R')
		*mask |= 0x2;
	else if (option == 'a')
		*mask |= 0x4;
	else if (option == 'f')
		*mask |= 0xC;
	else if (option == 'l')
		*mask |= 0x10;
	else if (option == 'r')
		*mask |= 0x20;
	else if (option == 't')
		*mask |= 0x40;
}

char			get_flags(char **av, char bt, int i, int j)
{
	char	buf[PAGESIZE];

	while ((av[++i]) && av[i][0] == '-' && (j = 1))
	{
		while (IS_FLAG(av[i][j]) || IS_FLAG2(av[i][j]))
		{
			IF_RETURN(av[i][j] == '-' &&
			ft_sprintf(buf, "%s%c\n", "ft_ls: illigal option -- ", av[i][j]) &&
			write(1, buf, 27), '~');
			mask_flag(&bt, av[i][j]);
			j++;
		}
		while (NOT_FLAG(av[i][j]) && NOT_FLAG2(av[i][j]))
		{
			IF_BREAK(!av[i][j]);
			IF_BREAK(av[i][j] == '-' && !av[i][j + 1]);
			IF_RETURN((av[i][j] == '-' && av[i][j + 1] ||
			(NOT_FLAG(av[i][j]) && NOT_FLAG2(av[i][j]))) &&
			ft_sprintf(buf, "%s%c\n", "ft_ls: illigal option -- ", av[i][j]) &&
			write(1, buf, 27), '~');
		}
	}
	return (bt);
}

t_file			*get_dirs(char **av, int i, int j)
{
	t_file	*paths;

	while (av[i])
	{
		if (av[i][j] == '-' && av[i][j + 1])
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

int				get_longest(t_file *paths)
{
	int		pad_width;
	int		tmp_len;

	pad_width = 0;
	while (N_DIR(paths) && (tmp_len = LEN(paths->name)))
	{
		if (pad_width < tmp_len)
			pad_width = tmp_len;
		paths = paths->next;
	}
	return (pad_width + 1);
}
