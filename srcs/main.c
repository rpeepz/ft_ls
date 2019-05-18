/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 21:48:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/18 03:48:31 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				main(int ac, char **av)
{
	char	flags;
	t_file	*paths;

	if (ac > 1)
	{
		flags = get_flags(av, 0, 0, 0);
		if (flags & 1UL << 6)
			IF_RETURN(write(1, "usage: ./ft_ls [-Ralrt] [file ...]\n", 35), 0);
		if (!(paths = get_dirs(av, flags, 1, 0)))
			IF_RETURN(write(1, "malloc error ,yo\n", 17), 0);
	}
	else
	{
		flags = 0;
		if (!(paths = t_fileinit()))
			t_filedel(paths);
	}
	system("leaks ft_ls");
	ft_printf("flags found :{%#15.8b}\n", flags);
	return (0);
}
