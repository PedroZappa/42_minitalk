/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:14:55 by passunca          #+#    #+#             */
/*   Updated: 2024/02/22 13:16:43 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	if (pause_flag)
		pause();
}
