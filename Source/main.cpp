#include "Core/Application.h"
#include "Game/Boid.h"

int main( int argc, char *args[] )
{
    RAND_SET_SEED(time(nullptr));
    Application *App = Application::GetInstance();

    { // setup a testing scenario
        std::vector< Boid * > Boids;
        s32 numOfBoids = 15;
        for ( int i = 0; i < numOfBoids; ++i )
        {
            Boid *NewObject = new Boid();
            float x = RAND_NUM_IN_RANGE( -WINDOW_HALF_WIDTH, WINDOW_HALF_WIDTH );
            float y = RAND_NUM_IN_RANGE( -WINDOW_HALF_HEIGHT, WINDOW_HALF_HEIGHT );
            NewObject->m_Transform.m_Position = { x, y };
            NewObject->m_Transform.m_Rotation = i * 15;
            NewObject->m_texture = i == 0 || i == ( numOfBoids - 1 ) ? App->GetTexture( "Assets/Player.png" ) : App->GetTexture( "Assets/Enemy.png" );
            NewObject->Behaviour = Steering::Behaviour::Arrive;
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
