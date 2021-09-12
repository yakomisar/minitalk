/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 13:50:36 by jmacmill          #+#    #+#             */
/*   Updated: 2021/09/09 20:59:53 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	message_handler(int pid, char *c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 128;
	while (c[i] != '\0')
	{
		while (counter >= 1)
		{
			if (c[i] & counter)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(60);
			counter /= 2;
		}
		counter = 128;
		i++;
	}
	i = 8;
	while (i)
	{
		kill(pid, SIGUSR2);
		usleep(60);
		i--;
	}
	exit(0);
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !is_numeric(argv[1]))
	{
		ft_putstr("Please use the following: [PID] [messaage]\n");
		return (1);
	}
	message_handler(ft_atoi(argv[1]), argv[2]);
	return (0);
}
