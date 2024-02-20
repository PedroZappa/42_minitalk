/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:05:05 by passunca          #+#    #+#             */
/*   Updated: 2024/02/18 12:05:10 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_btoa(int sig);


/*	Prints the server PID 
 *	*/
int main(void)
{
	struct sigaction sa;
	pid_t	pid;

	pid = getpid();
	sa.sa_handler = ft_btoa;
	sa.sa_flags = 0;
	ft_printf("Server PID: %s%d%s\n", YEL, pid, NC);
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		sleep(1);
	}
	return (0);
}

void	ft_btoa(int sig)
{

}
