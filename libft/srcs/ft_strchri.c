/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:00:05 by rpapagna          #+#    #+#             */
/*   Updated: 2019/02/26 20:26:18 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_strchri(const char *s, int c)
{
	int		i;

	i = -1;
	while (++i < (int)ft_strlen(s) + 1)
		if (s[i] == (char)c)
			return (i);
	return (0);
}
