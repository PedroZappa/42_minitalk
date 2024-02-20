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

static void		ft_str_to_bits(int pid, char *bits);

int	main(int argc, char **argv)
{
	int		pid;

	if (argc != 3)
		return (ft_printf("%sUsage: ./server [PID] [message]%s\n", RED, NC));
	pid = ft_atoi(argv[1]);
	ft_str_to_bits(pid, argv[2]);
	return (0);
}

static void	ft_str_to_bits(int pid, char *bits)
{
	int		i;
	int		base;
	char	letter;

	i = 0;
	while (bits[i])
	{
		while (base > 0)
		{
			if (letter >= base)
			{
				kill(pid, SIGUSR1);
				letter -= base;
			}
			else
				kill(pid, SIGUSR2);
			base /= 2;
			usleep(100);
		}
		++i;
	}
}
