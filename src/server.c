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

static void	ft_btoc(int sig, siginfo_t *info, void *context);
static void	ft_print_byte(int *byte);

/*	Prints the server PID;
 *	Handles SIGUSR1 and SIGUSR2 changing the default behaviour of their signal
 *	handlers to receive and message bit by bit and print it to stdout;
 *		SIGUSR1: when received sends
 *		This is achieved by using the sigaction() function;
 *	*/
int	main(void)
{
	struct sigaction	sa;
	// sigset_t			block_mask;
	pid_t				pid;

	pid = getpid();
	sigemptyset(&sa.sa_mask);
	// sigemptyset(&block_mask);
 //    sigaddset(&block_mask, SIGUSR1);
 //    sigaddset(&block_mask, SIGUSR2);
	sa.sa_sigaction = ft_btoc;
    // sa.sa_mask = block_mask;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_sep_color('0', '=', 20, GRN);
	ft_printf("Server PID: %s%d%s\n", YEL, pid, NC);
	ft_sep_color('0', '=', 20, GRN);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}

/*	Bits to character
 *	Receives a character bit by bit and the prints it to stdout
 *	*/
static void	ft_btoc(int sig, siginfo_t *info, void *context)
{
	static int	bit;
	static int	byte[8];

	(void)info;
	(void)context;
	if (sig == SIGUSR1)
		byte[bit++] = 0;
	else
		byte[bit++] = 1;
	if (bit == 8)
	{
		ft_print_byte(byte);
		bit = 0;
	}
}
/* This function takes an array of 8 bits and converts it into a character.
 *	Iterates over the bits in reverse order (LSB first), 
 *	Shifts the current value of to_print left by one bit, 
 *	Adds to the current bit.
 * */
static void	ft_print_byte(int *byte)
{
	int				i;
	unsigned char	to_print;

	i = 7;
	to_print = 0;
	while (i >= 0)
		to_print = to_print * 2 + byte[i--];
	ft_printf("%c", to_print);
}
