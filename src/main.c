#include "../headers/game.h"
#include <SDL2/SDL_render.h>
#include <string.h>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900
#define MIN_DELTA_TIME 33.33 // 30fps

/*
    TODO: Use command line args for
    defining screen size and simulation
    entity count.
*/

struct opts {
    int width;
    int height;
    int count;
    int framerate;
};

char* substr(char* string, int offset, int stride)
{
    if (stride == 0)
        stride = strlen(string)-offset;

    //char sub_str[sub_len+1];
    int sublen = stride - offset;
    char *substr = (char*) malloc(sizeof(char)*sublen + 1);

    // Traverse substring
    for (int i = 0; i < stride; i++)
    {
        substr[i] = string[offset + i];
    }

    // Insert null terminator
    substr[stride] = '\0';

    return substr;
}

void handleArgs(struct opts *options, int argc, char **argv)
{
    if (argc <= 1)
        return;

    for (int i = 1; i < argc; i++)
    {
        // Check for 'tack'
        if (argv[i][0] != '-')
            continue;

        char *opt = substr(argv[i], 1, 1);
        char *val = substr(argv[i], 2, 0);

        switch (*opt)
        {
            case 'w': options->width = atoi(val); break;
            case 'h': options->height = atoi(val); break;
            case 'c': options->count = atoi(val); break;
            case 'f': options->framerate = atoi(val); break;
            default: break;
        }
    }
}

int main(int argc, char **argv)
{
    // Set default opts
    struct opts opts;
    opts.width = 600; // Window width
    opts.height = 600; // Window height
    opts.count = 64;  // Entity count
    opts.framerate = 30;  // Framerate lock

    // Set opts with args
    handleArgs(&opts, argc, argv);

    Game gctx;
    Game_Init(&gctx, opts.width, opts.height, opts.count, opts.framerate);

    while (gctx.running)
    {
        Game_HandleEvents(&gctx);
        Game_Update(&gctx);
        Game_Draw(&gctx);

        Clock_Tick(&gctx.clock);

        /*
            TODO:
            Fix framerate locking not working
        */

        // Lock framerate
        if (gctx.clock.delta_time < gctx.target_delta_time)
        {
            SDL_Delay(gctx.target_delta_time - gctx.clock.delta_time);
        }
    }

    // Cleanup
    Game_Stop(&gctx);
}
