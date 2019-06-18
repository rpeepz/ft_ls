/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 19:44:51 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/17 21:59:45 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		ls_display(t_file *entry, char flags, int longest, int type)
{
	char		buf[PAGESIZE];
	char		*tmp;
	int			len;

	ft_bzero(buf, 64);
	tmp = buf;
	tmp = G_PATH(tmp, entry->full_path, entry->name);
	IF_THEN(type == 1, ft_printf("\n%s:\n", tmp));
	IF_THEN(type == 2, ft_printf("%s:\n", tmp) && (type = 1));
	IF_THEN(flags & 0x10, norminette(&entry, flags, ""));
	len = ft_sprintf(buf, "\0");
	while (!(flags & 0x10) && entry)
	{
		IF_THEN_CONTINUE(!(flags & 0x4) && entry->name[0] == '.',
			entry = entry->next);
		if (flags & 0x1)
			len += ft_sprintf(&buf[len], "%s\n", entry->name);
		else
			len += ft_sprintf(&buf[len], "%-*s", longest, entry->name);
		IF_THEN(!(entry = entry->next) || len > PAGESIZE - 255,
			ft_printf("%s", buf) && (len = ft_sprintf(buf, "\0")));
	}
}

int				print_contents(t_file *paths, char flags, int type)
{
	DIR				*dir;
	t_file			*entry;

	entry = NULL;
	dir = opendir(paths->name);
	if (!ft_strcmp(strerror(errno), "No such file or directory")
		&& N_DIR(paths))
		IF_RETURN(ft_printf("ls: %s: %s\n", paths->name, strerror(errno)), 0);
	IF_RETURN(!type && !dir && ft_printf("%s\n", paths->name), 0);
	if (!dir)
		ft_printf("ft_ls: %s: %s\n", paths->name, strerror(errno));
	else
	{
		if (get_contents(&entry, paths, &dir, 1))
			if (!(t_filedel(&entry)))
				return (1);
		t_file_mergesort(&entry, flags, 0);
		ls_display(entry, flags, get_longest(entry, flags, 0), type);
	}
	if (!t_filedel(&entry) && paths->next)
		return (print_contents(paths->next, flags, 1));
	t_filedel(&paths);
	return (0);
}

int				print_first_files(t_file **apath, char flgs, int lngst, int len)
{
	t_file	*paths;
	char	buf[PAGESIZE];

	paths = *apath;
	len = ft_sprintf(buf, "\0");
	IF_THEN(flgs & 0x10, norminette2(&paths, ""));
	while (!(flgs & 0x10) && paths && N_DIR(paths))
	{
		opendir(paths->name);
		if (!(ft_strcmp(strerror(errno), "No such file or directory")))
			ft_printf("ls: %s: %s\n", paths->name, strerror(errno));
		else if (flgs & 0x1)
			len += ft_sprintf(&buf[len], "%s\n", paths->name);
		else
			len += ft_sprintf(&buf[len], "%-*s", lngst, paths->name);
		ft_pipewrench("-s-s", paths->name, paths->full_path);
		IF_THEN(!(paths = paths->next) || Y_DIR(paths) || len > PAGESIZE
		- 255, ft_printf("%s", buf) && (len = ft_sprintf(buf, "\0")));
	}
	IF_RETURN(paths, print_contents(paths, flgs, 1));
	return (0);
}
