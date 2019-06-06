/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:05:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/06 13:37:29 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

int					ls_color(t_file *paths, char flags)
{
	if (!(flags & 0x2))
	{
		if (!paths->index)
			return (color_contents(paths, flags, 0));
		if (paths->index && N_DIR(paths))
			return (color_first_files(&paths, flags, get_longest(paths, 1)));
		return (color_contents(paths, flags, 2));
	}
	if (flags & 0x2)
		return (recurse_color(paths, flags));
	else if (!paths->index)
		;
	return (0);
}
