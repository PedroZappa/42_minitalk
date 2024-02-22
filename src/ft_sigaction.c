/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigaction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:12:53 by passunca          #+#    #+#             */
/*   Updated: 2024/02/22 21:05:16 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_set_sigaction(struct sigaction *sa)
{
	if (sigaction(SIGUSR1, sa, NULL) < 0)
		ft_perror_exit("sigaction() failed to handle SIGUSR1");
	if (sigaction(SIGUSR2, sa, NULL) < 0)
		ft_perror_exit("sigaction() failed to handle SIGUSR2");
}
