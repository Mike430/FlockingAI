#include "Core/Application.h"

int main( int argc, char *args[] )
{
    Application *App = Application::GetInstance();
    App->StartGameLoop();
    Application::Shutdown();
    return 0;
}
