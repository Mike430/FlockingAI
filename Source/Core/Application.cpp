#include "Application.h"

Application *Application::Self = nullptr;

Application *Application::GetInstance()
{
    if ( Self == nullptr )
    {
        Application::Self = new Application();
        if ( Application::Self != nullptr )
        {
            if ( Application::Self->Initialise() == false )
            {
                LOG( "We could not establish a stable application" );
                MURDER_APP;
                return nullptr;
            }
        }
    }
    return Application::Self;
}

void Application::Shutdown()
{
    if ( Self == nullptr )
    {
        delete Self;
    }
}

Application::Application()
        : m_Window( nullptr )
          , m_Surface( nullptr )
          , m_Renderer( nullptr )
          , m_ImguiContext( nullptr )
{
}

Application::~Application()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer( m_Renderer );
    SDL_DestroyWindow( m_Window );
    SDL_Quit();
}

bool Application::Initialise()
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        LOG( "SDL failed to initialise." );
        return false;
    }

    m_Window = SDL_CreateWindow( "FlockingAI",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 WINDOW_WIDTH,
                                 WINDOW_HEIGHT,
                                 SDL_WINDOW_SHOWN );

    if ( m_Window == nullptr )
    {
        LOG( "Failed to create a window: %s.", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer( m_Window,
                                     -1,
                                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    if ( m_Renderer == nullptr )
    {
        LOG( "Failed to created an SDL renderer: %s.", SDL_GetError());
        return false;
    }

    m_Surface = SDL_GetWindowSurface( m_Window );
    if ( m_Surface == nullptr )
    {
        LOG( "Failed to retrieve the screen surface for drawing to: %s.", SDL_GetError());
        return false;
    }

    IMGUI_CHECKVERSION();
    m_ImguiContext = ImGui::CreateContext();

    if ( m_ImguiContext == nullptr )
    {
        LOG( "Failed to intialise an imgui context." );
        return false;
    }

    ImGui::SetCurrentContext( m_ImguiContext );
    ImGui_ImplSDL2_InitForSDLRenderer( m_Window, m_Renderer );
    ImGui_ImplSDLRenderer2_Init( m_Renderer );

    // Build ImGUI atlas
    ImGuiIO &io = ImGui::GetIO();
    unsigned char *tex_pixels = nullptr;
    int tex_w, tex_h;
    io.Fonts->GetTexDataAsRGBA32( &tex_pixels, &tex_w, &tex_h );

    return true;
}

void Application::StartGameLoop()
{
    SDL_Event Event;
    bool ShouldQuit;

    while ( ShouldQuit == false )
    {
        while ( SDL_PollEvent( &Event ))
        {
            if ( Event.type == SDL_QUIT ) ShouldQuit = true;
            ImGui_ImplSDL2_ProcessEvent( &Event );
        }
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        SDL_SetRenderDrawColor( m_Renderer,
                                255,
                                0,
                                0,
                                255 );
        SDL_RenderClear( m_Renderer );
        SDL_FillRect( m_Surface,
                      NULL,
                      SDL_MapRGB( m_Surface->format,
                                  0xFF,
                                  0,
                                  0 ));

        ImGui::Begin( "My DearImGui Window" );
        ImGui::Text( "hello, world" );
        ImGui::End();

        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData( ImGui::GetDrawData());

        //Update the surface
        SDL_UpdateWindowSurface( m_Window );
        SDL_RenderPresent( m_Renderer );
    }
}

void Application::Update()
{

}

void Application::Draw()
{

}
