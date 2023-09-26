#include "Core/Application.h"
#include "Core/GameObject.h"

int main( int argc, char *args[] )
{
    Application *App = Application::GetInstance();

    for(int i = 0; i < 5; ++i)
    {
        new GameObject();
    }

    App->StartGameLoop();
    Application::Shutdown();
    return 0;
}
