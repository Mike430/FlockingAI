#include "World.h"

#include "GameObject.h"

//----------------------------------------------------------

World::World()
: m_isShuttingDown(false)
, m_gameObjects()
{
}

//----------------------------------------------------------

World::~World()
{
    m_isShuttingDown = true;

    for(int i = 0; i < m_gameObjects.size(); ++i)
    {
        delete m_gameObjects[i];
        LOG("Game object cleaned up");
    }

    LOG("World emptied");
    m_gameObjects.clear();
}

//----------------------------------------------------------

void World::RegisterGameObject( GameObject *InObject )
{
    for ( int i = 0; i < m_gameObjects.size(); ++i )
    {
        if ( m_gameObjects[ i ] == InObject )
        {
            LOG( "Duplicate object attempting to be added to world registry." );
            MURDER_APP;
            return;
        }
    }

    LOG("New Game Object Registered");
    m_gameObjects.push_back( InObject );
}

//----------------------------------------------------------

void World::UnRegisterGameObject( GameObject *InObject )
{
    if(m_isShuttingDown != false)
    {
        for ( int i = 0; i < m_gameObjects.size(); ++i )
        {
            if ( m_gameObjects[ i ] == InObject )
            {
                delete m_gameObjects[ i ];
                m_gameObjects.erase( m_gameObjects.begin() + i );
                LOG("Game object purged");
                return;
            }
        }
    }
}

//----------------------------------------------------------

void World::Update( const float InDeltaTime )
{
    for ( int i = 0; i < m_gameObjects.size(); ++i )
    {
        m_gameObjects[i]->Update(InDeltaTime);
    }
}

//----------------------------------------------------------

void World::Draw(SDL_Renderer* InRenderer)
{
    for ( int i = 0; i < m_gameObjects.size(); ++i )
    {
        if(m_gameObjects[i]->m_texture != nullptr)
        {
        }
    }
}

//----------------------------------------------------------