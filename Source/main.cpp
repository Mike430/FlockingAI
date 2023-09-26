#include "Core/Application.h"
#include "Core/GameObject.h"

int main( int argc, char *args[] )
{
    Application *App = Application::GetInstance();

    for(int i = 0; i < 15; ++i)
    {
        GameObject* NewObject = new GameObject();
        NewObject->m_Transform.m_Position = {-500.0f + 50.0f * i, -500.0f + 50.0f * i};
        NewObject->m_Transform.m_Rotation = i * 15;
        NewObject->m_texture = App->GetTexture("Assets/Enemy.png");
    }

    App->StartGameLoop();
    Application::Shutdown();
    return 0;
}
