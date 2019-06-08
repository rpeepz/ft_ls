/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 01:54:58 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/08 15:33:28 by rpapagna         ###   ########.fr       */
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
	else if (option == 'G')
		*mask |= 0x80;
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
		if (!(paths = t_fileinit(".", "", 0)))
			return (t_filedel(&paths));
	}
	else
	{
		if (!(paths = t_fileinit(av[i], "", 0)))
			return (t_filedel(&paths));
		while (av[++i])
			if (t_fileadd(&paths, av[i], "", 0))
				return (t_filedel(&paths));
	}
	return (paths);
}

int				get_longest(t_file *paths, char flags, int type)
{
	int		pad_width;
	int		tmp_len;

	pad_width = 0;
	IF_RETURN(flags & 0x1, 0);
	while (type == 3 && paths && (tmp_len = LEN(paths->full_path)))
	{
		IF_THEN(pad_width < tmp_len, pad_width = tmp_len);
		paths = paths->next;
	}
	while (type == 2 && paths)
	{
		IF_THEN(pad_width++, paths = paths->next);
	}
	while (type == 1 && paths && N_DIR(paths) && (tmp_len = LEN(paths->name)))
	{
		IF_THEN(pad_width < tmp_len, pad_width = tmp_len);
		paths = paths->next;
	}
	while (type == 0 && paths && (tmp_len = LEN(paths->name)))
	{
		IF_THEN(pad_width < tmp_len, pad_width = tmp_len);
		paths = paths->next;
	}
	return (pad_width + 1);
}

int				get_contents(t_file **apath, t_file *parent, DIR **dir, int typ)
{
	t_file			*entry;
	char			*fullpath;
	char			*tmp;
	struct dirent	*contents;

	tmp = parent->name;
	entry = *apath;
	while ((contents = readdir((*dir))))
	{
		IF_THEN(typ == 3, tmp = parent->full_path);
		fullpath = str_3join(tmp, "/", contents->d_name);
		if (!entry)
		{
			IF_RETURN(!(entry = t_fileinit(contents->d_name, fullpath, 1)), 1);
		}
		else
		{
			IF_RETURN(t_fileadd(&entry, contents->d_name, fullpath, 1), 1);
		}
		IF_THEN(fullpath, free(fullpath));
	}
	closedir(*dir);
	*apath = entry;
	return (0);
}
