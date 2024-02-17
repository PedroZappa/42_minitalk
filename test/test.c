/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:48:38 by passunca          #+#    #+#             */
/*   Updated: 2024/02/17 21:35:27 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>	// signal()
#include <stdio.h>	// printf()
#include <unistd.h>	// sleep()

void	ft_handler(int signum);

int	main(void)
{
	/*	Handle a signal	*/
	// signal(SIGINT, ft_handler);
	// while (1)
	// {
	// 	printf("Yo Whirl!\n");
	// 	sleep(1);
	// }

	/*	Ignore a signal */
	// signal(SIGINT, SIG_IGN);
	// while (1)
	// 	printf("Yo Whirl!\n");
	
	/*	Handle a signal with sigaction() */
	struct sigaction sa;
	sa.sa_handler = ft_handler;
	sa.sa_flags = 0;

	sigaction(SIGINT, &sa, NULL);
	while (1)
	{
		printf("Yo Whirl!\n");
		sleep(1);
	}
	return (0);
}

void	ft_handler(int signum)
{
	printf("\tSignal %d caught\n", signum);
}
