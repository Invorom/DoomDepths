#include "cli.h"
#include "hero.h"
#include "battle.h"

void clear_screen()
{
    printf("\e[1;1H\e[2J");
}

void clear_lines(int lines)
{
    for (int i = 0; i < lines; ++i)
        printf("\x1b[1F\x1b[2K");
}

void wait_for_enter()
{
    printf("\n     Press [ENTER] to continue...");
    clear_stdin();
    struct termios orig_termios;
    struct termios new_termios;

    // Get the current terminal attributes
    tcgetattr(STDIN_FILENO, &orig_termios);
    new_termios = orig_termios;

    // Disable canonical mode and echoing
    new_termios.c_lflag &= ~(ICANON | ECHO);

    // Set the new terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    // Set non-blocking input
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

    while (1)
    {
        char input;
        ssize_t bytesRead = read(STDIN_FILENO, &input, 1);

        if (bytesRead > 0)
        {
            if (input == '\n')
            {
                restore_terminal_attributes(orig_termios); // Avoid broken terminal
                return;
            }
        }
    }
}

int get_actual_string_length(const char *str)
{
    int length = 0;
    int inColorCode = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\x1B')
        { // Check for ANSI escape code
            inColorCode = 1;
        }
        else if (inColorCode && str[i] == 'm')
        {
            inColorCode = 0;
        }
        else if (!inColorCode)
        {
            length++;
        }
    }

    return length;
}

void restore_terminal_attributes(struct termios orig_termios)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

char listen_user_input()
{
    struct termios orig_termios;
    struct termios new_termios;

    // Get the current terminal attributes
    tcgetattr(STDIN_FILENO, &orig_termios);
    new_termios = orig_termios;

    // Disable canonical mode and echoing
    new_termios.c_lflag &= ~(ICANON | ECHO);

    // Set the new terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    // Set non-blocking input
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

    while (1)
    {
        char input;
        ssize_t bytesRead = read(STDIN_FILENO, &input, 1);

        if (bytesRead > 0)
        {
            if (input >= '0' && input <= '9')
            {
                restore_terminal_attributes(orig_termios); // Avoid broken terminal
                return input;
            }
        }
    }
}

int main_menu()
{
    char input = '0';
    FILE *file = fopen("savefile.json", "r");
    int saveExists = (file != NULL);
    if (file != NULL) {
        fclose(file);
    }

    clear_screen();
    display_menu_design();

    printf("\n     1. Start Game\n");
    if (saveExists) {
        printf("     2. Load Save\n");
    }
    printf("     %d. Quit\n\n", saveExists ? 3 : 2);
    printf("     Enter your choice: \n\n");
    fflush(stdout);

    while (input != '1' && input != '2' && (!saveExists || input != '3'))
    {
        input = listen_user_input();
    }

    switch (input)
    {
    case '1':
        clear_screen();
        return 1;

    case '2':
    clear_screen();
    return 2;
    case '3':
        clear_screen();
        printf("     See you next time!\n");
        return 0;

    default:
        clear_screen();
        printf("     Something went wrong\n");
        return -1;
    }
}