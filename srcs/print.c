/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 19:44:51 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/02 22:28:27 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			ls_display(t_file **apath, char flags, int longest)
{
	t_file		*entry;
	char		buf[PAGESIZE];

	entry = *apath;
	buf[0] = '\0';
	while (entry)
	{
		if (flags & 0x1)
			ft_sprintf(&buf[LEN(buf)], "%s\n", entry->name);
		else if (flags & 0x10)
		{
			;
		}
		else
			ft_sprintf(&buf[LEN(buf)], "%-*s", longest, entry->name);
		entry = entry->next;
	}
	ft_printf("%s\n", buf);
}

int				print_contents(t_file *paths, char flags)
{
	DIR				*dir;
	t_file			*entry;
	char			buf[PAGESIZE];

	entry = NULL;
	dir = opendir(paths->name);
	if (!dir)
	{
		ft_sprintf(buf, "ft_ls: %s: %s\n", paths->name, strerror(errno));
		ft_printf("%s", buf);
		return (0);
	}
	else
	{
		if (get_contents(&entry, &dir))
		{
			t_filedel(entry);
			return (1);
		}
		t_file_mergesort(&entry, flags, 0);
		ls_display(&entry, flags, get_longest(entry, 0));
	}
	t_filedel(entry);
	return (0);
}

void			print_first_files(t_file **apath, char flags, int longest)
{
	t_file	*paths;
	char	buf[PAGESIZE];

	paths = *apath;
	buf[0] = '\0';
	while (N_DIR(paths))
	{
		if (flags & 0x1)
			ft_sprintf(&buf[LEN(buf)], "%s\n", paths->name);
		else if (flags & 0x10)
		{
			;
		}
		else
			ft_sprintf(&buf[LEN(buf)], "%-*s", longest, paths->name);
		paths = paths->next;
	}
	ft_printf("%s\n", buf);
}
