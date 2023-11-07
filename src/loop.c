#include "loop.h"
#include "map.h"
#include "cli.h"

int event_loop(Context *context)
{
    system("/bin/stty raw");
    int first_iteration = 1;

    while (1)
    {
        if (first_iteration)
        {
            system("/bin/stty cooked");
            displayMap(context);
            system("/bin/stty raw");
            first_iteration = 0;
        }

        char input;
        if ((input = fgetc(stdin)) != EOF)
        {
            if (process_user_input(input, context) == 0)
            {
                system("/bin/stty cooked");
                return 0;
            }
            system("/bin/stty cooked");
            displayMap(context);
            system("/bin/stty raw");
        }
    }
    return 0;
}

int process_user_input(char userInput, Context *context)
{
    switch (userInput)
    {
    case 'z':
        if (context->pos_y - 1 < 0 || context->map[context->pos_x][context->pos_y - 1] == OBSTACLE)
        {
            break;
        }
        else if (context->map[context->pos_x][context->pos_y - 1] == MONSTER)
        {
            // if
            context->pos_y -= 1;
            break;
        }
        else
        {
            context->pos_y -= 1;
            break;
        }
    case 'd':
        if (context->pos_x + 1 > ROWS || context->map[context->pos_x + 1][context->pos_y] == OBSTACLE)
        {
            break;
        }
        else if (context->map[context->pos_x + 1][context->pos_y] == MONSTER)
        {
            // if
            context->pos_x += 1;
            break;
        }
        else
        {
            context->pos_x += 1;
            break;
        }
    case 's':
        if (context->pos_y + 1 > COLUMNS || context->map[context->pos_x][context->pos_y + 1] == OBSTACLE)
        {
            break;
        }
        else if (context->map[context->pos_x][context->pos_y + 1] == MONSTER)
        {
            // if
            context->pos_y += 1;
            break;
        }
        else
        {
            context->pos_y += 1;
            break;
        }
    case 'q':
        if (context->pos_x - 1 < 0 || context->map[context->pos_x - 1][context->pos_y] == OBSTACLE)
        {
            break;
        }
        else if (context->map[context->pos_x - 1][context->pos_y] == MONSTER)
        {
            // if
            context->pos_x -= 1;
            break;
        }
        else
        {
            context->pos_x -= 1;
            break;
        }
    case 'e':
        system("/bin/stty cooked");
        clear_screen();
        wait_for_enter();
        system("/bin/stty raw");

        break;

    case 'Q':
        // exits program
        return 0;
    }

    return 1;
}
