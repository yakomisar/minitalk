/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 13:50:36 by jmacmill          #+#    #+#             */
/*   Updated: 2021/09/05 19:24:54 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n > 2147483647 || n < -2147483648)
		return ;
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		n = n * -1;
		ft_putchar_fd('-', fd);
	}
	if (n < 10)
	{
		ft_putchar_fd(n + '0', fd);
		return ;
	}
	ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
	return ;
}

void	my_handler(int sig)
{
	static int	received = 0;

	write(1, "i", 1);
	if (sig == SIGUSR1)
		++received;
	else
	{
		ft_putnbr_fd(received, 1);
		write(1, "\n", 1);
		exit(0);
	}
}

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

static void	message_handler(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(40);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(40);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	act;

	if (argc != 3 || !is_numeric(argv[1]))
	{
		ft_putstr("Please use the following format: [PID] [messaage]\n");
		return (1);
	}
	act.sa_handler = my_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	message_handler(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
