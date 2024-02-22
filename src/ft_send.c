/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:14:55 by passunca          #+#    #+#             */
/*   Updated: 2024/02/22 15:49:13 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_send_int(pid_t pid, int num)
{
	int		bitshift;
	char	bit;

	bitshift = ((sizeof(int) * 8) - 1);
	while (bitshift >= 0)
	{
		bit = (num >> bitshift) & 1;
		ft_send_bit(pid, bit, 1);
		--bitshift;
	}
}

void	ft_send_char(pid_t pid, char c)
{
	int		bitshift;
	char	bit;

	bitshift = ((sizeof(char) * 8) - 1);
	while (bitshift >= 0)
	{
		bit = (c >> bitshift) & 1;
		ft_send_bit(pid, bit, 1);
		--bitshift;
	}
}

void	ft_send_bit(pid_t pid, char bit, char pause_flag)
{
	(void)pause_flag;
	if (!bit)
	{
		if (kill(pid, SIGUSR1) < 0)
			ft_perror_exit("kill() failed sending SIGUSR1\n");
	}
	else if (bit)
		if (kill(pid, SIGUSR2) < 0)
			ft_perror_exit("kill() failed sending SIGUSR2\n");
	if (pause_flag != 0)
		pause();
}
