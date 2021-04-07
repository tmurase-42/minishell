#include <stdio.h>
// fprintf()
// printf()
// stderr
// getchar()
// perror()
#include <sys/wait.h>
// waitpid() and associated macros
#include <unistd.h>
// chdir()
// fork()
// exec()
// pid_t
#include <stdlib.h>
// malloc()
// realloc()
// free()
// exit()
// execvp()
// EXIT_SUCCESS, EXIT_FAILURE
#include <string.h>
// strcmp()
// strtok()

/* 
ビルトインシェルのコマンドに対応する関数の宣言
*/
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

/* 
ビルトインシェルの関数に対応するコマンドの宣言
*/
char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[])(char **) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit
};

int lsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

/* 
ビルトイン関数の実装
*/
int lsh_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("lsh");
        }
    }

    return 1;
}

int lsh_help(char **args) {
    int i;
    printf("Shuichi Nagao's LSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in: \n");

    for (i = 0; i < lsh_num_builtins(); i++) {
        printf(" %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");

    return 1;
}

int lsh_exit(char **args) {
    return 0;
}
int	lsh_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("lsh");
		}
		exit(0);
	}
	else if (pid < 0)
	{
		perror("lsh");
	}
	else
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

int lsh_execute(char **args)
{
	int i;
	if (args[0] == NULL)
	{
		return 1;
	}
	for (i = 0; i < lsh_num_builtins(); i++){
		if (strcmp(args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}
	return lsh_launch(args);
}



#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **lsh_split_line(char *line)
{
	int bufsize = LSH_TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;
	
	if (!tokens)
	{
		fprintf(stderr, "lsh:allocation error\n");
		exit(0);
	}

	token = strtok(line, LSH_TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += LSH_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "lsh: allocation error\n");
				exit(0);
			}
		}
		token = strtok(NULL, LSH_TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}


#define LSH_RL_BUFSIZE 1024


//char *lsh_read_line(void)
//{
//	char *line = NULL;
//	ssize_t  bufsize = 0;
//	
//	getline(&line, &bufsize, stdin);
//	return line;
//}
char *lsh_read_line(void)
{
	int	bufsize = LSH_RL_BUFSIZE;
	int	position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;

	if (!buffer)
	{
		fprintf(stderr, "lsh: allocatuin error/\n");
		exit(0);
	}

	while (1)
	{
		c = getchar();
		if (c == EOF || c == '\n')
		{
			buffer[position] = '\n';
			return buffer;
		}
		else
		{
			buffer[position] = c;
		}
		position++;
	
		if (position >= bufsize)
		{
			bufsize += LSH_RL_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
			{
				fprintf(stderr, "lsh: allocation error\n");
				exit(0);
			}
		}
	}
}



void	lsh_loop(void)
{
	char *line;
	char **args;
	int	status;

	do {
		printf("minishell>");
		line = lsh_read_line();
		args = lsh_split_line(line);
		status = lsh_execute(args);

		free(line);
		free(args);
	} while (status);
}


int main(int argc, char *argv[])
{
	lsh_loop();

	return 0;
}
