/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:48:38 by passunca          #+#    #+#             */
/*   Updated: 2024/02/17 21:38:54 by passunca         ###   ########.fr       */
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
	int	i;
	sa.sa_handler = ft_handler;
	sa.sa_flags = 0;

	i = 0;
	sigaction(SIGINT, &sa, NULL);
	while (1)
	{
		++i;
		printf("%d Yo Whirl!\n", i);
		sleep(1);
	}
	return (0);
}

void	ft_handler(int signum)
{
	printf("\tSignal %d caught\n", signum);
}
