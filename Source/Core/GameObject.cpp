#include "Core/GameObject.h"

#include "Core/Application.h"
#include "Core/World.h"

//----------------------------------------------------------

GameObject::GameObject()
: m_Transform()
, m_texture( nullptr )
{
    if(Application *application = Application::GetInstance())
    {
        if(World *world = application->GetWorld())
        {
            m_World = world;
            world->RegisterGameObject( this );
        }
    }
}

//----------------------------------------------------------

GameObject::~GameObject()
{
    if(Application *application = Application::GetInstance())
    {
        if(World *world = application->GetWorld())
        {
            world->UnRegisterGameObject( this );
        }
    }
}

//----------------------------------------------------------
