#include "Core/Application.h"
#include "Game/Boid.h"

int main( int argc, char *args[] )
{
    Application *App = Application::GetInstance();

    {
        std::vector< Boid * > Boids;
        s32 numOfBoids = 15;
        for ( int i = 0; i < numOfBoids; ++i )
        {
            Boid *NewObject = new Boid();
            NewObject->m_Transform.m_Position = { -500.0f + 50.0f * i, -500.0f };
            NewObject->m_Transform.m_Rotation = i * 15;
            NewObject->m_texture = i == 0 || i == ( numOfBoids - 1 ) ? App->GetTexture( "Assets/Player.png" ) : App->GetTexture( "Assets/Enemy.png" );
            Boids.push_back( NewObject );
        }

        if ( Boids.size() > 1 )
        {
            for ( int i = 0; i < Boids.size(); ++i )
            {
                if ( i < Boids.size() - 1 )
                {
                    Boids[ i ]->m_Target = Boids[ i + 1 ];
                } else
                {
                    Boids[ i ]->m_Target = Boids[ 0 ];
                }
            }
        }
    }

    App->StartGameLoop();
    Application::Shutdown();
    return 0;
}
