/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:04:30 by passunca          #+#    #+#             */
/*   Updated: 2024/02/18 12:04:50 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void		ft_send_str(pid_t pid, char *to_send);
static void		ft_str_to_bits(int pid, char to_send);

int	main(int argc, char **argv)
{
	int		pid;

	if (argc != 3)
		return (ft_printf("%sUsage: ./server [PID] [message]%s\n", RED, NC));
	pid = ft_atoi(argv[1]);
	ft_send_str(pid, argv[2]);
	return (0);
}

void	ft_send_str(pid_t pid, char *to_send)
{
	int		i;

	i = -1;
	while (to_send[++i])
		ft_str_to_bits(pid, (unsigned char)to_send[i]);
}

static void	ft_str_to_bits(int pid, char to_send)
{
	int		bits;

	bits = 0;
	while (bits < 8)
	{
		if ((to_send % 2) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		to_send /= 2;
		++bits;
		usleep(100);
	}
}
