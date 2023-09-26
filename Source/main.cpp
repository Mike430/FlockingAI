#include "Core/Application.h"
#include "Core/GameObject.h"

int main( int argc, char *args[] )
{
    Application *App = Application::GetInstance();

    for(int i = 0; i < 5; ++i)
    {
        GameObject* NewObject = new GameObject();
        NewObject->m_Transform.m_Position = {-50.0f + 20.0f * i, -50.0f + 20.0f * i};
    }

    App->StartGameLoop();
    Application::Shutdown();
    return 0;
}
