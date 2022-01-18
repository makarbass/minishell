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
	int com_count;
	char **argc;
	char *comand;
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

int	once_quote(char *line, int i, t_min *min)
{
	i++;
	while (line[i] != '\'')
	{
		min->argc[min->com_count] = (char *)realloc(min->argc[min->com_count], sizeof(char) * (i - 1));
		min->argc[min->com_count][i] = line[i];
		printf("%c", min->argc[min->com_count][i]);
		i++;
	}
	return (i);
}

void	two_quote(char *line, int i)
{

}

int	dollar_funk(char *line, int i, t_min *min)
{
	int j;
	
	i++;
	j = i;
	while (line[j] != ' ' && line[j] != '$' && line[j])
		j++;
	min->comand = (char *)malloc(sizeof(char) * (j - i));
	j = 0;
	while (line[i] != ' ' && line[i] != '$' && line[i])
		min->comand[j++] = line[i++];
	return (i);
}

void    ft_parser(t_min *min, char *line)
{
	int i;

	i = 0;
	min->argc = (char **)malloc(sizeof(char));
	while (line[i])
	{
		if (line[i] == '\'')
			i = once_quote(line, i, min);
		else if (line[i] == '\"')
			two_quote(line, i);
		else if (line[i] == '$')
			i = dollar_funk(line, i, min);
		else if (line[i] == ' ')
			min->argc = (char **)realloc(min->argc, sizeof(char) * ++min->com_count);
		else
		{
			min->argc[min->com_count] = (char *)realloc(min->argc[min->com_count], sizeof(char) * i);
			min->argc[min->com_count][i] = line[i];
			printf("%c", min->argc[min->com_count][i]);
		}
		i++;
	}
	printf("\n");
}

int main(int ac, char **av, char **env)
{
	char *line;
	t_min min;

	min.com_count = 0;
	line = readline("minishell$ ");
	dup_env(env);
	ft_parser(&min, line);
	// printf("%s\n", line);
}