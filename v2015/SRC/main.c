#include "pch.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include "dibuixos.h"

/*
 * 
 * dibuixos [options] [dibuixo]
 * 
 * options:
 *  --help : show usage
 *  -r<width>x<height>x[bpp] : resolucion. Por defecto es -r800x600
 *  -f : fullscreen
 *  -l : play demo in infinite loop
 *
 * dibuixo:
 *  demo : All of dibuixos
 *  <dibuixo> : one of dibuixo (see README for more help)
 * 
 */
 
 static int initSDL()
 {
     Uint32 flags=SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
     int x=(fullscreen) ? 0 : SDL_WINDOWPOS_CENTERED;
     int y=(fullscreen) ? 0 : SDL_WINDOWPOS_CENTERED;
     
     if (SDL_Init(SDL_INIT_VIDEO) < 0) 
         return SDL_SetError("Error en InitSDL: %s",SDL_GetError());
    
    if (fullscreen)
        flags |= SDL_WINDOW_FULLSCREEN;
     
    if ((window=SDL_CreateWindow("dibuixos",x,y,width,height,flags))==NULL)
        return SDL_SetError("Error en SDL_CreateWindow: %s",SDL_GetError());
        
    if ((glcontext=SDL_GL_CreateContext(window))==NULL)
    {
        SDL_DestroyWindow(window);
        return SDL_SetError("Error en SDL_GL_CreateContext: %s",SDL_GetError());
    }
    
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);
         
     return 0;
 }
 
 static void dib_loop()
 {
     int quit=0;
     SDL_Event e;
     
      //Enable text input
      SDL_StartTextInput(); //While application is running 
      while( !quit ) 
      {
          while( SDL_PollEvent( &e ) != 0 )
          { 
                //User requests quit
                if( e.type == SDL_QUIT )
                    quit = 1;
                else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                    quit = 1;
                else
                    update(&e);
          }
          render();
          //Update screen
          SDL_GL_SwapWindow(window);
      } 
      
      //Disable text input
      SDL_StopTextInput(); 
 }
 
 static void SDLfinalize()
 {
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
 }

int main(int argc, char **argv)
{
    int exit;
    int ret=readargs(argc,argv,&exit);
    
    if (ret || exit)
    {
        showusage((ret) ? SDL_GetError() : NULL);
        
        return (!ret) ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    
    if (initSDL())
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"dibuixos",SDL_GetError(),NULL);
        
        return EXIT_FAILURE;        
    }
    
    if (!setdibuixo((dibuixo_arg!=NULL) ? dibuixo_arg : (DIBUIXO *) &dib_presentacio ))
    {
        dib_loop();
        setdibuixo(NULL);
    }
    SDLfinalize();
    
	return EXIT_SUCCESS;
}
