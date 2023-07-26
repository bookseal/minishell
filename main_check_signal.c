#include "main.h"

void signal_handler(int signal_num) {
   	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal_num == SIGQUIT)
	{
		;
	}
	if (signal_num == SIGTERM)
	{
		// printf("\033[1A"); // cursor up
		// printf("\033[10C"); // cursor 10 forward
		printf(" exit\n");
		exit(-1);
	}
}
void check_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, signal_handler);

}

void set_signals(void)
{
	struct termios term;

	if (!tcgetattr(0, &term))
		perror("tcgetattr");
	term.c_lflag &= -ECHOCTL;
	if (!tcsetattr(0, 0, &term))
		perror("tcsetattr");
	check_signal();
}