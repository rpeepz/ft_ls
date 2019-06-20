/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:05:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/20 02:59:38 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

static void		recur_callor(t_file **apath, char flags, char *buf)
{
	t_file *cur;

	cur = *apath;
	if (buf)
		ft_printf("%s", buf);
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
	int		len;
	char	buf[PAGESIZE];
	char	*tmp;
	t_file	*cur;

	ft_bzero(buf, 255);
	cur = *entry;
	tmp = buf;
	IF_THEN(type == 1, ft_printf("\n%s:\n",
		tmp = G_PATH(tmp, cur->full_path, cur->name)));
	len = ft_sprintf(buf, "\0");
	IF_THEN(flags & 0x10, norminette(&cur, flags, ""));
	while (!(flags & 0x10) && cur && (tmp = define_color(cur)))
	{
		IF_THEN_CONTINUE(!(flags & 0x4) && cur->name[0] == '.',
			cur = cur->next);
		if (flags & 0x1)
			len += ft_sprintf(&buf[len], "%s%s%s\n", tmp, cur->name, NOCOL);
		else
			len += ft_sprintf(&buf[len], "%s-*s%s", tmp, longest, cur->name,
				NOCOL);
		IF_THEN(!(cur = cur->next) || len > PAGESIZE - 255, ft_printf("%s",
			buf) && (len = ft_sprintf(buf, "\0")));
	}
	recur_callor(entry, flags, tmp = buf);
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
	char	*color;
	int		len;

	paths = *apath;
	ft_bzero(buf, 4096);
	IF_THEN(!(len = 0) && flags & 0x10, norminette2(&paths, "", len, flags));
	while (!(flags & 0x10) && paths && N_DIR(paths) &&
		(color = define_color(paths)))
	{
		opendir(paths->name);
		if (!(ft_strcmp(strerror(errno), "No such file or directory")))
			ft_printf("ls: %s: %s\n", paths->name, strerror(errno));
		else if (flags & 0x1)
			ft_sprintf(&buf[LEN(buf)], "%s%s%s\n", color, paths->name, NOCOL);
		else
			ft_sprintf(&buf[LEN(buf)], "%s%-*s%s", color, longest, paths->name,
				NOCOL);
		IF_THEN(!(paths = paths->next) || Y_DIR(paths) || len > PAGESIZE
		- 255, ft_printf("%s", buf) && (len = ft_sprintf(buf, "\0")));
	}
	while (paths && color_re_recurse(paths, flags, 1))
		paths = paths->next;
	return (0);
}

int				ls_color(t_file *paths, char flags)
{
	if (!(flags & 0x2))
	{
		if (!paths->index && !(flags & 0x10))
			return (color_contents(paths, flags, 0));
		if ((paths->index && N_DIR(paths)))
		{
			return (color_first_files(&paths, flags,
			get_longest(paths, flags, 1), 0));
		}
		if (!paths->index && N_DIR(paths) && flags & 0x10)
			return (color_first_files(&paths, flags, 0, 0));
		return (color_contents(paths, flags, 2));
	}
	if (flags & 0x2 && !paths->index && N_DIR(paths))
		return (color_contents(paths, flags, 0));
	else
	{
		color_recurse(&paths, flags, get_longest(paths, flags, 1));
	}
	IF_THEN(!(flags & 0x1) && !(flags & 0x10), ft_putchar('\n'));
	return (0);
}
