#include "Core/Application.h"

#include "Core/World.h"

//----------------------------------------------------------

bool Application::IsShuttingDown = false;
Application *Application::Self = nullptr;

//----------------------------------------------------------

Application *Application::GetInstance()
{
    if(Application::IsShuttingDown)
    {
        return nullptr;
    }

    if ( Self == nullptr )
    {
        Application::Self = new Application();
        if ( Application::Self->Initialise() == false )
        {
            LOG( "We could not establish a stable application" );
            MURDER_APP;
            return nullptr;
        }
        Application::Self->m_World = new World();
    }
    return Application::Self;
}

//----------------------------------------------------------

void Application::Shutdown()
{
    Application::IsShuttingDown = true;
    if ( Self != nullptr )
    {
        for(const std::pair<std::string, SDL_Texture*>& entry : Self->m_TextureAssetPool)
        {
            SDL_DestroyTexture(entry.second);
        }

        delete Self;
    }
}

//----------------------------------------------------------

SDL_Texture* Application::GetTexture( const std::string& InAssetPath )
{
    Application* application = Application::GetInstance();
    for(const std::pair<std::string, SDL_Texture*>& entry : application->m_TextureAssetPool)
    {
        if( entry.first == InAssetPath)
        {
            return entry.second;
        }
    }

    SDL_Texture* NewTexture = LoadTexture(InAssetPath);

    if(NewTexture != nullptr)
    {
        application->m_TextureAssetPool.insert( std::pair< std::string, SDL_Texture * >( InAssetPath, NewTexture ));
    }

    return NewTexture;
}

//----------------------------------------------------------

SDL_Texture* Application::LoadTexture( const std::string& InAssetPath )
{
    SDL_Texture* NewTexture = nullptr;
    Application* application = Application::GetInstance();

    SDL_Surface* LoadedSurface = IMG_Load(InAssetPath.c_str());
    if(LoadedSurface == nullptr)
    {
        LOG("We could not load %s", InAssetPath.c_str());
    }
    else
    {
        NewTexture = SDL_CreateTextureFromSurface(application->m_Renderer, LoadedSurface);

        if(NewTexture == nullptr)
        {
            LOG("Unable to create texture from %s - SDL error: %s", InAssetPath.c_str(), SDL_GetError());
        }

        SDL_FreeSurface(LoadedSurface);
    }

    return NewTexture;
}

//----------------------------------------------------------

Application::Application()
        : m_Window( nullptr )
          , m_Surface( nullptr )
          , m_Renderer( nullptr )
          , m_ImguiContext( nullptr )
{
}

//----------------------------------------------------------

Application::~Application()
{
    delete m_World;
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer( m_Renderer );
    SDL_DestroyWindow( m_Window );
    SDL_Quit();

    LOG( "Application successfully destroyed." );
}

//----------------------------------------------------------

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

//----------------------------------------------------------

void Application::StartGameLoop()
{
    SDL_Event Event;
    bool ShouldQuit = false;
    bool IsPaused = false;

    const float FakeDeltaTime = 1.0f / 60.0f;
    double PreviousFrameUpdateTime = 0.0;
    double PreviousFrameRenderTime = 0.0;
    TimeStamp UpdateStart;
    TimeStamp UpdateEnd;
    TimeStamp RenderEnd;

    while ( ShouldQuit == false )
    {
        PreviousFrameUpdateTime = std::chrono::duration_cast<DurationMillis>(UpdateEnd - UpdateStart).count();
        PreviousFrameRenderTime = std::chrono::duration_cast<DurationMillis>(RenderEnd - UpdateEnd).count();
        UpdateStart = Clock::now();
        while ( SDL_PollEvent( &Event ))
        {
            if ( Event.type == SDL_QUIT )
            {
                ShouldQuit = true;
            }
            if ( Event.type == SDL_KEYUP )
            {
                if ( Event.key.keysym.sym == SDLK_ESCAPE )
                {
                    ShouldQuit = true;
                }

                if ( Event.key.keysym.sym == SDLK_SPACE )
                {
                    IsPaused = !IsPaused;
                }
            }

            ImGui_ImplSDL2_ProcessEvent( &Event );
        }

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        SDL_SetRenderDrawColor( m_Renderer,
                                0,
                                0,
                                0,
                                255 );
        SDL_RenderClear( m_Renderer );

        if(IsPaused == false)
        {
            m_World->Update( FakeDeltaTime );
        }
        UpdateEnd = Clock::now();
        m_World->Draw(m_Renderer);

        ImGui::Begin( "Stats" );
        ImGui::Text( "DeltaTime = %.5f\nFramerate = %.5f\nUpdate time = %.5f ms\nRender time = %.5f ms",
                     FakeDeltaTime,
                     1.0f / FakeDeltaTime,
                     PreviousFrameUpdateTime,
                     PreviousFrameRenderTime );
        ImGui::End();

        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData( ImGui::GetDrawData());

        SDL_UpdateWindowSurface( m_Window );
        RenderEnd = Clock::now(); // Vsync occurs when the renderer presents on the next line
        SDL_RenderPresent( m_Renderer );
    }
}

//----------------------------------------------------------
