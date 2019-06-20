/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 19:22:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/20 02:58:40 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		recur_call(t_file **apath, char flags, char *buf)
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
			re_recurse(cur, flags, 3);
		cur = cur->next;
	}
	t_filedel(apath);
}

void			re_re_recurse(t_file **entry, char flgs, int lngst, int typ)
{
	char	buf[PAGESIZE];
	char	*tmp;
	int		len;
	t_file	*cur;

	ft_bzero(buf, 255);
	cur = *entry;
	tmp = buf;
	IF_THEN(typ == 1, ft_printf("\n%s:\n",
		tmp = G_PATH(tmp, cur->full_path, cur->name)));
	len = ft_sprintf(buf, "\0");
	IF_THEN(flgs & 0x10, norminette(&cur, flgs, ""));
	while (!(flgs & 0x10) && cur)
	{
		IF_THEN_CONTINUE(!(flgs & 0x4) && cur->name[0] == '.',
			cur = cur->next);
		if (flgs & 0x1)
			len += ft_sprintf(&buf[len], "%s\n", cur->name);
		else
			len += ft_sprintf(&buf[len], "%-*s", lngst, cur->name);
		IF_THEN(!(cur = cur->next) || len > PAGESIZE - 255,
			ft_printf("%s", buf) && (len = ft_sprintf(buf, "\0")));
	}
	recur_call(entry, flgs, tmp = buf);
}

int				re_recurse(t_file *paths, char flags, int type)
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
		re_re_recurse(&entry, flags,
			get_longest(entry, flags, 3), paths->index ? type : 2);
	}
	return (1);
}

int				recurse(t_file **apath, char flags, int longest)
{
	t_file	*paths;
	char	buf[PAGESIZE];
	int		len;

	paths = *apath;
	ft_bzero(buf, 4096);
	len = 0;
	IF_THEN(flags & 0x10, norminette2(&paths, "", len, flags));
	while (!(flags & 0x10) && paths && N_DIR(paths))
	{
		opendir(paths->name);
		if (!(ft_strcmp(strerror(errno), "No such file or directory")))
			ft_printf("ls: %s: %s\n", paths->name, strerror(errno));
		else if (flags & 0x1)
			len += ft_sprintf(&buf[len], "%s\n", paths->name);
		else
			len += ft_sprintf(&buf[len], "%-*s", longest, paths->name);
		ft_pipewrench("-s-s", paths->name, paths->full_path);
		IF_THEN(!(paths = paths->next) || Y_DIR(paths) || len > PAGESIZE
		- 255, ft_printf("%s", buf) && (len = ft_sprintf(buf, "\0")));
	}
	while (paths && re_recurse(paths, flags, 1))
		paths = paths->next;
	return (0);
}

int				ft_ls(t_file *paths, char flags)
{
	if (flags & 0x80)
		return (ls_color(paths, flags));
	if (!(flags & 0x2))
	{
		if (!paths->index && !(flags & 0x10))
			return (print_contents(paths, flags, 0));
		if ((paths->index && N_DIR(paths)))
		{
			return (print_first_files(&paths, flags,
			get_longest(paths, flags, 1), 0));
		}
		if (!paths->index && N_DIR(paths) && flags & 0x10)
			return (print_first_files(&paths, flags, 0, 0));
		return (print_contents(paths, flags, 2));
	}
	if (flags & 0x2 && !paths->index && N_DIR(paths))
		return (print_contents(paths, flags, 0));
	else
	{
		recurse(&paths, flags, get_longest(paths, flags, 1));
	}
	IF_THEN(!(flags & 0x1) && !(flags & 0x10), ft_putchar('\n'));
	return (0);
}
