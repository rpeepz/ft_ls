/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:21:47 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/06 16:20:46 by rpapagna         ###   ########.fr       */
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
	ft_bzero(buf, 64);
	tmp = buf;
	tmp = G_PATH(tmp, entry->full_path, entry->name);
	IF_THEN(tm == 1, ft_printf("\n%.*s:\n", LEN(tmp), tmp));
	IF_THEN(tm == 2, ft_printf("%.*s:\n", LEN(tmp), tmp) && (tm = 1));
	buf[0] = '\0';
	while (entry && (color = define_color(entry)))
	{
		IF_THEN_CONTINUE(!(flags & 0x4) && entry->name[0] == '.',
			entry = entry->next);
		if (flags & 0x1)
			ft_sprintf(&buf[LEN(buf)], "%s%s%s\n", NOCOL, color, entry->name);
		else if (flags & 0x10)
			;
		else
			ft_sprintf(&buf[LEN(buf)], "%s%s%-*s", NOCOL, color, length, entry->name);
		entry = entry->next;
	}
	ft_printf("%s%c%s", buf, flags & 0x1 ? '\0' : '\n', NOCOL);
}

int				color_contents(t_file *paths, char flags, int type)
{
	DIR				*dir;
	t_file			*entry;

	entry = NULL;
	dir = opendir(paths->name);
	if (!ft_strcmp(strerror(errno), "No such file or directory") && N_DIR(paths))
		IF_RETURN(ft_printf("ls: %s: %s\n", paths->name, strerror(errno)), 0);
	IF_RETURN(!type && !dir && ft_printf("%s\n", paths->name), 0);
	if (!dir)
		ft_printf("ls: %s: %s\n", paths->name, strerror(errno));
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
	while (paths && N_DIR(paths) && (color = define_color(paths)))
	{
		opendir(paths->name);
		if (!(ft_strcmp(strerror(errno), "No such file or directory")))
			IF_THEN_CONTINUE(ft_printf("ls: %s: %s\n", paths->name, strerror(errno)),
			paths = paths->next);
		if (flags & 0x1)
			ft_sprintf(&buf[LEN(buf)], "%s%s\n", color, paths->name);
		else if (flags & 0x10)
			;
		else
			ft_sprintf(&buf[LEN(buf)], "%s%-*s", color, longest, paths->name);
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
