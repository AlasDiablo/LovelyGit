#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int help_message()
{
    printf("Usage: lovelygit [OPTION] [COMMIT MESSAGE]\n");
    printf("Option list:             \n");
    printf("  -h, --help             Show help message\n");
    printf("  -f, --fix              Add emoji for bugfix\n");
    printf("  -r, --refactor         Add emoji for code refactor\n");
    printf("  -w, --wip              Add emoji for work in progress content\n");
    printf("  -n, --normal           Add emoji for normal code commit\n");
    return 0;
}

int error_message()
{
    printf("Invalid argument numbers!\n");
    printf("\n");
    help_message();
    return 1;
}

int commit(char* str)
{
    printf("Commit preview: %s\n", str);
    printf("Validate ? [y/n]: ");
    char c = getchar();
    char * command = malloc((strlen(str) + 16) * sizeof(char));
    strcat(command, "git commit -m \"");
    strcat(command, str);
    strcat(command, "\"");
    switch (c)
    {
    case 'y':
        system(command);
        return 0;
    case 'n':
        printf("Cancelling\n");
        return 0;
    default:
        printf("Invalid parameter!");
        return 1;
    }
}

int check_parametter(char** argv)
{
    char* str = argv[1];
    char* commit_str = argv[2];
    char* tmp = malloc((strlen(commit_str) + 12) * sizeof(char));
    
    if (strcmp(str, "-h") == 0 || strcmp(str, "--help") == 0)
    {
        return help_message();
    }
    else if (strcmp(str, "-f") == 0 || strcmp(str, "--fix") == 0)
    {
        strcat(tmp, "🐜 - ");
    }
    else if (strcmp(str, "-r") == 0 || strcmp(str, "--refactor") == 0)
    {
        strcat(tmp, "♻️ - ");
    }
    else if (strcmp(str, "-w") == 0 || strcmp(str, "--wip") == 0)
    {
        strcat(tmp, "🚧 - ");
    }
    else if (strcmp(str, "-n") == 0 || strcmp(str, "--normal") == 0)
    {
        strcat(tmp, "📝 - ");
    }
    else
    {
        return error_message();
    }
    
    strcat(tmp, commit_str);
    return commit(tmp);   
}

int check_parametter_one_arg(char** argv)
{
    char* str = argv[1];
    if (strcmp(str, "-h") == 0 || strcmp(str, "--help") == 0)
    {
        return help_message();
    }
    else
    {
        return commit(str);
    }
}

int main(int argc, char** argv)
{
    int exit_code = 0;

    switch (argc)
    {
    case 2:
        exit_code = check_parametter_one_arg(argv);
        break;
    case 3:
        exit_code = check_parametter(argv);
        break;
    default:
        exit_code = error_message();
        break;
    }
    
    return exit_code;
}
