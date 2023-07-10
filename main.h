#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

typedef enum {
    NO_REDIRECT = 0,
	PIPE, // '|'
    REDIRECT_IN,  // '<'
	HEREDOC, // '<<'
    REDIRECT_OUT,  // '>'
    APPEND_OUT,  // '>>'
} tags;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env *next;
}	t_env;

typedef struct s_cmd
{
	char	*builtin;
	char	*path;
	char	**argv;
}			t_cmd;

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	t_cmd	*cmd;
	t_env	*env;
	struct s_pipex	*next;
}			t_pipex;

typedef struct s_token
{
	char	*value;
	bool	single_quotes;
	bool	double_quotes;
	tags	tag;
	struct s_token	*next;
} t_token;

typedef struct s_lexical
{
	bool	in_single_quotes;
	bool	in_double_quotes;	
	bool	single_quotes;
	bool	double_quotes;
	tags	tag;
	char	*start;
	t_env	*env_head;
} t_lexical;

t_pipex	*syntax_analyzer(t_token	*tokens, t_env *env_head);

// lexical_analyzer
t_token	*lexical_analyzer(char *input, t_env *env_head);

// parser
t_pipex *parser(char *input, t_env *env);

// envs
t_env	*envp_to_t_env(char	*envp[]);
char	*replace_envs(char *start, t_env *env_head);

// executor
int 		executor(t_pipex *p_head);

// signal
void check_signal(void);

// libft
char	*ft_strtrim(char *s1, char *set);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**envp_to_env(char **envp);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2, char sep);