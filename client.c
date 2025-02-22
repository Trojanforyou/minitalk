/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:51:53 by msokolov          #+#    #+#             */
/*   Updated: 2025/02/22 17:54:37 by msokolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int g_signal = 0;

static void	handler(int sig)
{
	if (sig == SIGUSR1)
		g_signal = 1;
	else
		write (1, "Recieved\n", 10);
}

void	send_char(int pid, char *str)
{
	int	i;

	while (*str)
	{
		i = 7;
		while (i >= 0)
		{
			if (*str >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			i--;
			while (g_signal == 0)
				usleep(1);
			g_signal = 0;
		}
		str++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	send_char(ft_atoi(argv[1]), argv[2]);
	return (0);
}
