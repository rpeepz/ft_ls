/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:05:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/04 15:03:12 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

int					ls_color(t_file *paths, char flags)
{
	if (!(flags & 0x2) && paths->index == 0)
	{
//		if (color_contents(paths, flags))
			return (1);
	}
	else if (N_DIR(paths))
		color_first_files(&paths, flags, get_longest(paths, 1));
	return (0);
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
		color = NOCOL;
		IF_THEN(Y_DIR(paths), color = BGRN);
		IF_THEN(Y_EXE(paths->info.st_mode), color = RED);
		if (flags & 0x1)
			ft_sprintf(&buf[LEN(buf)], "%s%s\n", color, paths->name);
		else if (flags & 0x10)
		{
			;
		}
		else
			ft_sprintf(&buf[LEN(buf)], "%-*s", longest, paths->name);
		paths = paths->next;
	}
	ft_printf("%s%c", buf, flags & 0x1 ? '\0' : '\n');
}
