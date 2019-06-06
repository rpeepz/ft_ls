/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:21:47 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/05 23:32:32 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

static char		*define_color(t_file *paths)
{
	IF_RETURN(Y_DIR(paths), BGRN);
	IF_RETURN(Y_USX(paths), RED);
	return (NOCOL);
}

static void		ls_color_display(t_file **apath, char flags, int length, int tm)
{
	t_file		*entry;
	char		*color;
	char		buf[PAGESIZE];
	char		*tmp;

	entry = *apath;
	tmp = buf;
	tmp = ft_strncpy(buf, entry->full_path, LEN(entry->full_path));
	IF_THEN(tm == 1, ft_printf("\n%.*s:\n", LEN(tmp) - 2, tmp));
	buf[0] = '\0';
	while (entry && (color = define_color(entry)))
	{
		IF_THEN_CONTINUE((!(flags & 0x4) && entry->name[0] == '.'),
			entry = entry->next);
		if (flags & 0x1)
			ft_sprintf(&buf[LEN(buf)], "%s%s\n", color, entry->name);
		else if (flags & 0x10)
		{
			;
		}
		else
			ft_sprintf(&buf[LEN(buf)], "%s%-*s", color, length, entry->name);
		entry = entry->next;
	}
	ft_printf("%s%c%s", buf, flags & 0x1 ? '\0' : '\n', NOCOL);
}

int				color_contents(t_file *paths, char flags, int type)
{
	DIR				*dir;
	t_file			*entry;
	char			buf[PAGESIZE];

	entry = NULL;
	dir = opendir(paths->name);
	if (!dir)
	{
		ft_sprintf(buf, "ft_ls: %s: %s\n", paths->name, strerror(errno));
		IF_RETURN(ft_printf("%s", buf), 0);
	}
	else
	{
		if (get_contents(&entry, paths, &dir))
			if (!(t_filedel(&entry)))
				return (1);
		t_file_mergesort(&entry, flags, 0);
		ls_color_display(&entry, flags, get_longest(entry, 0), type);
	}
	if (paths->next && !t_filedel(&entry))
		return (color_contents(paths->next, flags, 1));
	t_filedel(&paths);
	return (0);
}

int				color_first_files(t_file **apath, char flags, int longest)
{
	t_file	*paths;
	char	*color;
	char	buf[PAGESIZE];

	paths = *apath;
	buf[0] = '\0';
	while (paths && N_DIR(paths))
	{
		color = define_color(paths);
		if (flags & 0x1)
			ft_sprintf(&buf[LEN(buf)], "%s%s\n", color, paths->name);
		else if (flags & 0x10)
		{
			;
		}
		else
			ft_sprintf(&buf[LEN(buf)], "%s%-*s", color, longest, paths->name);
		free(paths->name);
		IF_THEN(paths->full_path, free(paths->full_path));
		paths = paths->next;
	}
	ft_printf("%s%c%s", buf, flags & 0x1 ? '\0' : '\n', NOCOL);
	if (paths)
		return (color_contents(paths, flags, 1));
	return (0);
}

int				recurse_color(t_file *paths, char flags)
{
	return (write(1, "recur\n", 6));
}