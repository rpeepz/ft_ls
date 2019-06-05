/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:21:47 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/04 18:35:42 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

static char		*define_color(t_file *paths)
{
	IF_RETURN(Y_DIR(paths), BGRN);
	IF_RETURN(paths->info.st_mode & S_IXUSR, RED);
	return (NOCOL);
}

void			ls_color_display(t_file **apath, char flags, int longest)
{
	t_file		*entry;
	char		*color;
	char		buf[PAGESIZE];

	entry = *apath;
	buf[0] = '\0';
	while (entry && (color = define_color(entry)))
	{
		if (!(flags & 0x4) && entry->name[0] == '.')
		{
			entry = entry->next;
			continue ;
		}
		if (flags & 0x1)
			ft_sprintf(&buf[LEN(buf)], "%s%s\n", color, entry->name);
		else if (flags & 0x10)
		{
			;
		}
		else
			ft_sprintf(&buf[LEN(buf)], "%s%-*s", color, longest, entry->name);
		entry = entry->next;
	}
	ft_printf("%s%c", buf, flags & 0x1 ? '\0' : '\n');
}

int				color_contents(t_file *paths, char flags)
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
		if (get_contents(&entry, &dir))
		{
			IF_RETURN(!t_filedel(&entry), 1);
		}
		t_file_mergesort(&entry, flags, 0);
		ls_color_display(&entry, flags, get_longest(entry, 0));
	}
	IF_RETURN(!t_filedel(&entry) || 1, 0);
}

void			color_first_files(t_file **apath, char flags, int longest)
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
		paths = paths->next;
	}
	ft_printf("%s%c", buf, flags & 0x1 ? '\0' : '\n');
}
