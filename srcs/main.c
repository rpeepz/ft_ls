/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 21:48:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/30 17:57:23 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		dispatch_ls_mode(t_file *paths, char flags)
{
	if (flags ^ 0x62)
	{
		ft_ls(paths, flags);
		return (0);
	}
	else
		return (dash_onef(paths));
}

int				main(int ac, char **av)
{
	char			flags;
	t_file			*paths;

	flags = 0;
	if (ac > 1)
	{
		if ((flags = get_flags(av, 0, 0, 0)) == '~')
			IF_RETURN(write(1, "usage: ./ft_ls [-Ralrt] [file ...]\n", 35), 0);
		if (!(paths = get_dirs(av, 1, 0)))
			IF_RETURN(write(1, "malloc error, yo\n", 17), 0);
	}
	else
	{
		if (!(paths = t_fileinit(".")))
			t_filedel(paths);
	}
	if (!paths->next)
		paths->index = 0;
	else
		t_file_mergesort(&paths, flags);
	if (dispatch_ls_mode(paths, flags))
		write(1, "malloc error, yo\n", 17);
	t_filedel(paths);
	return (0);
}
