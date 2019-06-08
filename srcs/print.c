/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 19:44:51 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/07 18:26:29 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		ls_display(t_file *entry, char flags, int longest, int type)
{
	char		buf[PAGESIZE];
	char		*tmp;

	ft_bzero(buf, 64);
	tmp = buf;
	tmp = G_PATH(tmp, entry->full_path, entry->name);
	IF_THEN(type == 1, ft_printf("\n%s:\n", tmp));
	IF_THEN(type == 2, ft_printf("%s:\n", tmp) && (type = 1));
	buf[0] = '\0';
	while (entry)
	{
		IF_THEN_CONTINUE(!(flags & 0x4) && entry->name[0] == '.',
			entry = entry->next);
		if (flags & 0x1)
			ft_sprintf(&buf[LEN(buf)], "%s\n", entry->name);
		else if (flags & 0x10)
			;
		else
			ft_sprintf(&buf[LEN(buf)], "%-*s", longest, entry->name);
		entry = entry->next;
	}
	ft_printf("%s%c", buf, flags & 0x1 ? '\0' : '\n');
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
	if (paths->next && !t_filedel(&entry))
		return (print_contents(paths->next, flags, 1));
	t_filedel(&entry);
	return (0);
}

int				print_first_files(t_file **apath, char flags, int longest)
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
	if (paths)
		return (print_contents(paths, flags, 1));
	return (0);
}
