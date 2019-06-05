/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:05:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/04 18:39:07 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

int					ls_color(t_file *paths, char flags)
{
	if (!(flags & 0x2) && paths->index == 0)
	{
		if (color_contents(paths, flags))
			return (1);
	}
	else if (N_DIR(paths))
		color_first_files(&paths, flags, get_longest(paths, 1));
	return (0);
}
