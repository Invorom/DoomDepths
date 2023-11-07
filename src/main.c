#include "cli.h"
#include "map.h"
#include "loop.h"

int main(int argc, char **argv)
{
    // main_menu();

    Context *context = malloc(sizeof(Context));

    // Init the map
    mapInit(context);

    if (event_loop(context) == 0)
    {
        return EXIT_SUCCESS;
    }

    return 0;
}
