/**
 * MojoShader; generate shader programs from bytecode of compiled
 *  Direct3D shaders.
 *
 * Please see the file LICENSE.txt in the source's root directory.
 *
 *  This file written by Ryan C. Gordon.
 */

#include <stdio.h>
#include "mojoshader.h"
#include "SDL.h"

int main(int argc, char **argv)
{
    int retval = 1;

    #if 0
    printf("MojoShader bestprofile\n");
    printf("Compiled against version %d\n", MOJOSHADER_VERSION);
    printf("Linked against version %d\n", MOJOSHADER_version());
    printf("\n");
    #endif

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        fprintf(stderr, "SDL_Init(SDL_INIT_VIDEO) error: %s\n", SDL_GetError());
    else
    {
        SDL_GL_LoadLibrary(NULL);
        if (SDL_SetVideoMode(640, 480, 0, SDL_OPENGL) == NULL)
            fprintf(stderr, "SDL_SetVideoMode() error: %s\n", SDL_GetError());
        else
        {
            const char *best = MOJOSHADER_glBestProfile(SDL_GL_GetProcAddress);
            MOJOSHADER_glContext *ctx;
            ctx = MOJOSHADER_glCreateContext(best, SDL_GL_GetProcAddress, 0, 0, 0);
            if (ctx == NULL)
                printf("MOJOSHADER_glCreateContext() fail: %s\n", MOJOSHADER_glGetError());
            else
            {
                printf("%s\n", best);
                retval = 0;  // success.
                MOJOSHADER_glDestroyContext(ctx);
            } // else
        } // else
        SDL_Quit();
    } // else

    return retval;
} // main

// end of bestprofile.c ...

