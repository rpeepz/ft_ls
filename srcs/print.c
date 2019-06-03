/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 19:44:51 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/02 20:11:17 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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
