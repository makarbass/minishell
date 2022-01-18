#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_min
{
	int exit;
	int x; 
	int y;
}               t_min;

void	dup_env(char **env)
{
	int size;
	char **env_dup;
	int i;
	int j;

	i = 0;
	size = 0;
	while (env[size])
		size++;
	env_dup = (char **)malloc(sizeof(env_dup) * size);
	while (env[i])
	{
		j = 0;
		while (env[i][j])
			j++;
		env_dup[i] = (char *)malloc(sizeof(*env_dup) * j);
		i++;
	}
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			env_dup[i][j] = env[i][j];
			j++;
		}
		i++;
	}
	// i = 0;
	// while (env_dup[i])
	// {
	// 	j = 0;
	// 	while (env_dup[i][j])
	// 		printf("%c", env_dup[i][j++]);
	// 	printf("\n");
	// 	i++;
	// }
	// printf("%d\n", size);
	// env_dup = (char *)malloc(sizeof(env_dup) * )
}

void	once_quote(char *line)
{
	printf("hel\n");
}

void	two_quote(char *line)
{

}

void    ft_parser(t_min *min, char *line)
{
	int i;
	int k;
	char **args;

	i = 0;
	k = 0;
	args = (char **)malloc(sizeof(char));
	while (line[i])
	{
		args[k] = (char *)realloc(args[k], sizeof(char) * i);
		if (line[i] == '\'')
			once_quote(line);
		else if (line[i] == '\"')
			two_quote(line);
		else if (line[i] == ' ')
			args = (char **)realloc(args, sizeof(char) * ++k);
		else
		{
			args[k][i] = line[i];
			printf("%c", args[k][i]);
		}
		i++;
	}
	printf("\n");
}

int main(int ac, char **av, char **env)
{
	char *line;
	t_min min;
	line = readline(line);
	dup_env(env);
	ft_parser(&min, line);
	// printf("%s\n", line);
}