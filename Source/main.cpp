#include <iostream>
#include <SDL.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

int main(int argc, char* args[])
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL failed to initialise." << std::endl;
        return 0;
    }
    else
    {
        SDL_version sdlLinked;
        SDL_GetVersion(&sdlLinked);
        printf("SDL (%d.%d.%d) successfully initialise - TO THE MOON!\n.",sdlLinked.major,sdlLinked.minor,sdlLinked.patch);
    }

    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        SDL_Renderer* Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        IMGUI_CHECKVERSION();
        ImGuiContext* Context = ImGui::CreateContext();
        ImGui::SetCurrentContext(Context);
        ImGui_ImplSDL2_InitForSDLRenderer(window, Renderer);
        ImGui_ImplSDLRenderer2_Init(Renderer);
        screenSurface = SDL_GetWindowSurface( window );

        // Build atlas
        ImGuiIO& io = ImGui::GetIO();
        unsigned char* tex_pixels = nullptr;
        int tex_w, tex_h;
        io.Fonts->GetTexDataAsRGBA32(&tex_pixels, &tex_w, &tex_h);

        screenSurface = SDL_GetWindowSurface( window );
        SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
        SDL_UpdateWindowSurface( window );
        SDL_Event e; bool quit = false;

        while( quit == false )
        {
            while( SDL_PollEvent( &e ) )
            {
                if( e.type == SDL_QUIT ) quit = true;

                ImGui_ImplSDL2_ProcessEvent(&e);
            }
            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
            SDL_RenderClear(Renderer);
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0, 0 ) );

            ImGui::Begin("My DearImGui Window");
            ImGui::Text("hello, world");
            ImGui::End();

            ImGui::Render();
            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

            //Update the surface
            SDL_UpdateWindowSurface( window );
            SDL_RenderPresent(Renderer);
        }
    }

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}
