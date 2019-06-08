/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:05:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/08 11:15:53 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

static void		recur_callor(t_file **apath, char flags)
{
	t_file *cur;

	cur = *apath;
	while (cur)
	{
		IF_THEN_CONTINUE(!(flags & 0x4) && cur->name[0] == '.',
			cur = cur->next);
		if (Y_DIR(cur) && !PARENT_DIR(cur->name) && !CURRENT_DIR(cur->name))
			color_re_recurse(cur, flags, 3);
		cur = cur->next;
	}
	t_filedel(apath);
}

void			color_re_re_recurse(t_file **entry, char flags,
		int longest, int type)
{
	char	buf[PAGESIZE];
	char	*tmp;
	t_file	*cur;

	ft_bzero(buf, 255);
	cur = *entry;
	tmp = buf;
	tmp = G_PATH(tmp, cur->full_path, LEN(cur->name) < 2 ? "-" : cur->name);
	IF_THEN(type == 1, ft_printf("\n%s:\n", tmp));
	ft_bzero(buf, 255);
	while (cur && (tmp = define_color(cur)))
	{
		IF_THEN_CONTINUE(!(flags & 0x4) && cur->name[0] == '.',
			cur = cur->next);
		if (flags & 0x1)
			ft_sprintf(&buf[LEN(buf)], "%s%s\n", tmp, cur->name);
		else if (flags & 0x10)
			;
		else
			ft_sprintf(&buf[LEN(buf)], "%s-*s", tmp, longest, cur->name);
		cur = cur->next;
	}
	ft_printf("%s%c%s", buf, flags & 0x1 ? '\0' : '\n', NOCOL);
	recur_callor(entry, flags);
}

int				color_re_recurse(t_file *paths, char flags, int type)
{
	DIR		*dir;
	t_file	*entry;

	entry = NULL;
	if (type == 3)
		dir = opendir(paths->full_path);
	else
		dir = opendir(paths->name);
	if (!ft_strcmp(strerror(errno), "No such file or directory") &&
		N_DIR(paths))
	{
		IF_RETURN(ft_printf("ls: %s: %s\n", paths->name, strerror(errno)), 1);
	}
	else
	{
		if (get_contents(&entry, paths, &dir, type))
			if (!(t_filedel(&entry)))
				IF_RETURN(write(1, MALLOC_ERR, 17), 1);
		t_file_mergesort(&entry, flags, 0);
		if (type == 3)
			type = 1;
		color_re_re_recurse(&entry, flags,
			get_longest(entry, flags, 3), paths->index ? type : 2);
	}
	return (1);
}

int				color_recurse(t_file **apath, char flags, int longest)
{
	t_file	*paths;
	char	buf[PAGESIZE];

	paths = *apath;
	buf[0] = '\0';
	while (paths && N_DIR(paths))
	{
		opendir(paths->name);
		if (!(ft_strcmp(strerror(errno), "No such file or directory")))
			ft_printf("ls: %s: %s\n", paths->name, strerror(errno));
		else if (flags & 0x1)
			ft_sprintf(&buf[LEN(buf)], "%s\n", paths->name);
		else if (flags & 0x10)
			;
		else
			ft_sprintf(&buf[LEN(buf)], "%-*s", longest, paths->name);
		IF_THEN(paths->name, free(paths->name));
		IF_THEN(paths->full_path, free(paths->full_path));
		paths = paths->next;
	}
	ft_printf("%s%c", buf, flags & 0x1 ? '\0' : '\n');
	while (paths && color_re_recurse(paths, flags, 1))
		paths = paths->next;
	return (0);
}

int				ls_color(t_file *paths, char flags)
{
	if (!(flags & 0x2))
	{
		if (!paths->index)
			return (color_contents(paths, flags, 0));
		if (paths->index && N_DIR(paths))
		{
			return (color_first_files(&paths, flags,
			get_longest(paths, flags, 1)));
		}
		return (color_contents(paths, flags, 2));
	}
	if (flags & 0x2 && !paths->index && N_DIR(paths))
		return (color_contents(paths, flags, 0));
	else
	{
		color_recurse(&paths, flags, get_longest(paths, flags, 1));
	}
	return (0);
}
