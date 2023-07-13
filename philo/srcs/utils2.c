/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:45:47 by nvaubien          #+#    #+#             */
/*   Updated: 2023/07/13 22:42:02 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_valid_input(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	if (ft_strlen(str) >= 10 && ft_strncmp(str, INT_MAX, len) != 0)
		return (1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n - 1) && (*s1 == *s2) && (*s1))
	{
		i++;
		s1++;
		s2++;
	}
	if (n == 0)
		return (0);
	return ((unsigned char )*s1 - (unsigned char)*s2);
}

size_t	ft_strlen(const char *string)
{
	int	index;

	index = 0;
	while (string[index] != '\0')
		index++;
	return (index);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
