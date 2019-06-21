/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:21:47 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/20 07:23:03 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

static void		ls_color_display(t_file *entry, char flgs, int lnth, int type)
{
	char		buf[PAGESIZE];
	char		*tmp;
	int			len;

	ft_bzero(buf, 4096);
	tmp = buf;
	tmp = G_PATH(tmp, entry->full_path, entry->name);
	IF_THEN(type == 1, ft_printf("\n%.*s:\n", LEN(tmp), tmp));
	IF_THEN(type == 2, ft_printf("%s:\n", tmp) && (type = 1));
	IF_THEN(flgs & 0x10, norminette(&entry, flgs, ""));
	len = ft_sprintf(buf, "\0");
	while (!(flgs & 0x10) && entry && (tmp = define_color(entry)))
	{
		IF_THEN_CONTINUE(!(flgs & 0x4) && entry->name[0] == '.',
			entry = entry->next);
		if (flgs & 0x1)
			len += ft_sprintf(&buf[len], "%s%s%s\n", tmp, entry->name, NOCOL);
		else
			len += ft_sprintf(&buf[len], "%s%-*s%s", tmp, lnth, entry->name,
				NOCOL);
		IF_THEN(!(entry = entry->next) || len > PAGESIZE - 255,
			ft_printf("%s", buf) && (len = ft_sprintf(buf, "\0")));
	}
	IF_THEN(LEN(buf), ft_putstr(buf));
}

int				color_contents(t_file *paths, char flags, int type)
{
	DIR				*dir;
	t_file			*entry;

	entry = NULL;
	dir = opendir(paths->name);
	if (!dir)
	{
		if (!ft_strcmp(strerror(errno), "Permission denied"))
			ft_printf("%s:\n", paths->name);
		IF_RETURN(ft_printf("ls: %s: %s\n", paths->name, strerror(errno)), 0);
	}
	else
	{
		if (get_contents(&entry, paths, &dir, type))
			if (!(t_filedel(&entry)))
				return (1);
		t_file_mergesort(&entry, flags, 0);
		ls_color_display(entry, flags, get_longest(entry, flags, 0),
			paths->index ? type : 0);
	}
	if (!t_filedel(&entry) && paths->next)
		return (color_contents(paths->next, flags, 1));
	t_filedel(&paths);
	return (0);
}

int				color_first_files(t_file **apath, char flags, int lngst, int ln)
{
	t_file	*pth;
	char	*color;
	char	buf[PAGESIZE];

	pth = *apath;
	ft_bzero(buf, 4096);
	IF_THEN(flags & 0x10, norminette2(&pth, "", ln, flags));
	while (!(flags & 0x10) && pth && N_DIR(pth) && (color = define_color(pth)))
	{
		opendir(pth->name);
		if (!(ft_strcmp(strerror(errno), "No such file or directory")))
			ft_printf("ls: %s: %s\n", pth->name, strerror(errno));
		else if (flags & 0x1)
			ft_sprintf(&buf[LEN(buf)], "%s%s%s\n", color, pth->name, NOCOL);
		else
			ft_sprintf(&buf[LEN(buf)], "%s%-*s%s", color, lngst, pth->name,
				NOCOL);
		ft_pipewrench("-s-s", pth->name, pth->full_path);
		IF_THEN(!(pth = pth->next) || Y_DIR(pth) || ln > PAGESIZE
		- 255, ft_printf("%s", buf) && (ln = ft_sprintf(buf, "\0")));
	}
	IF_RETURN(pth, color_contents(pth, flags, pth->index ? 1 : 0));
	return (0);
}
