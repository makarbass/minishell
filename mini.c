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
	char **env_dup;
	char *comand;
}               t_min;

int     ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 || *s2)
    {
        if (*s1 != *s2)
            return ((unsigned char)*s1 - (unsigned char)*s2);
        s1++;
        s2++;
    }
    return (0);
}

void	dup_env(char **env, t_min *min)
{
	int size;
	int i;
	int j;

	i = 0;
	size = 0;
	while (env[size])
		size++;
	min->env_dup = (char **)malloc(sizeof(min->env_dup) * size + 1);
	if (!min->env_dup)
		return ;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
			j++;
		min->env_dup[i] = (char *)malloc((sizeof(*min->env_dup) * j) + 1);
		i++;
	}
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			min->env_dup[i][j] = env[i][j];
			j++;
		}
		i++;
	}
	// i = 0;
	// while (min->env_dup[i])
	// {
	// 	j = 0;
	// 	while (min->env_dup[i][j])
	// 		printf("%c", min->env_dup[i][j++]);
	// 	printf("\n");
	// 	i++;
	// }
	// printf("%d\n", size);
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
	// if (ft_strcmp(min->comand, "pwd") || ft_strcmp(min->comand, "PWD"))
	// 	ft_pwd(min);
	// else if (ft_strcmp(min->comand, "echo") || ft_strcmp(min->comand, "ECHO"))
	// 	ft_echo(min);
	// else if (ft_strcmp(min->comand, "cd") || ft_strcmp(min->comand, "CD"))
	// 	ft_cd(min);
	// else if (ft_strcmp(min->comand, "export") || ft_strcmp(min->comand, "EXPORT"))
	// 	ft_export(min);
	// else if (ft_strcmp(min->comand, "unset") || ft_strcmp(min->comand, "UNSET"))
	// 	ft_unset(min);
	// else if (ft_strcmp(min->comand, "env") || ft_strcmp(min->comand, "ENV"))
	// 	ft_env(min);
	// else if (ft_strcmp(min->comand, "exit") || ft_strcmp(min->comand, "EXIT"))
	// 	ft_exit(min);
	free(min->comand);
	return (i);
}

int	once_quote(char *line, int i, t_min *min)
{
	int j;

	j = ++i;
	while (line[i] != '\'')
	{
		min->argc[min->com_count] = (char *)realloc(min->argc[min->com_count], sizeof(char) * (i - j));
		min->argc[min->com_count][i] = line[i];
		printf("%c", min->argc[min->com_count][i]);
		i++;
	}
	return (i);
}

int	two_quote(char *line, int i, t_min *min)
{
	int j;
	int start_coint;

	start_coint = ++i;
	j = i;
	while (line[i] != '\"')
	{
		if (line[i] == '$')
			i = dollar_funk(line, i, min);
		min->argc[min->com_count] = (char *)realloc(min->argc[min->com_count], sizeof(char) * (j - start_coint));
		min->argc[min->com_count][j] = line[i];
		printf("%c", min->argc[min->com_count][i]);
		j++;
		i++;
	}
	return (i);
}

void ft_parser(t_min *min, char *line)
{
	int i;
	int j;
	int flag;

	i = 0;
	j = 0;
	flag = 0;
	if (line[i])
		min->argc = (char **)malloc(sizeof(char*));
	while (line[i])
	{
		if (line[i] != ' ')
			flag = 1;
		if (flag == 0 && line[i] == ' ')
			j--;
		else if (flag == 1 && line[i] == ' ')
		{
			int prov = i;
			while(line[prov])
				if (line[prov++] != ' ')
					flag = 0;
			if (flag == 1)
				break;
			min->argc = (char **)realloc(min->argc, sizeof(char*) * (++min->com_count + 1));
			// printf("%d\n", min->com_count);
		}
		else if (line[i] == '\'')
			i = once_quote(line, i, min);
		else if (line[i] == '\"')
			i = two_quote(line, i, min);
		else if (line[i] == '$')
			i = dollar_funk(line, i, min);
		else
		{
			if (!min->argc[min->com_count])
				min->argc[min->com_count] = (char *)malloc(sizeof(char) * (j + 1));
			else
				min->argc[min->com_count] = (char *)realloc(min->argc[min->com_count], sizeof(char) * (j + 1));
			min->argc[min->com_count][j] = line[i];
			printf("%c", min->argc[min->com_count][j]);
		}
		// printf("%c", line[i]);
		i++;
		j++;
	}
	// printf("%d\n", min->com_count);
	printf("\n");
}

void	ft_free(t_min *min)
{
	int i;

	i = 0;
	while (min->argc[i])
		free(min->argc[i++]);
	free(min->argc);
}

int main(int ac, char **av, char **env)
{
	char *line;
	t_min min;

	min.com_count = 0;
	line = readline("minishell$ ");
	dup_env(env, &min);
	ft_parser(&min, line);
	ft_free(&min);
	// printf("%s\n", min.comand);
}