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
    printf("\nPress [ENTER] to continue...");
    clear_stdin();
}

int actualStringLength(const char *str)
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
            else
            {
                printf("Please enter a valid number\n"); // For funny users
                clear_lines(1);
            }
        }
    }
}

void main_menu()
{
    int choice;
    do
    {
        clear_screen();
        display_menu_design();

        printf("\n 1. Start Game\n 2. Quit\n\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        clear_stdin();
        switch (choice)
        {
        case 1:
            clear_screen();

            Hero *hero = initialize_hero();
            start_battle(hero);
            free_hero(hero);
            break;

        case 2:
            break;

        default:
            choice = 0;
            break;
        }
    } while (choice < 1 || choice > 2);
}
