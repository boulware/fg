#include "fighter.h"

fighter_state::fighter_state(std::string Label, real32 HorizontalSpeed, real32 VerticalSpeed)
        :
        Direction(direction::Neutral),
        Label(Label),
        HorizontalSpeed(HorizontalSpeed),
        VerticalSpeed(VerticalSpeed)
{
}

void
fighter_state::Exit(fighter* Fighter, fighter_state* NewState)
{
    NewState->Direction = Direction;
}

fighter_neutral_state::fighter_neutral_state()
        :
        fighter_state("neutral")
{
}

fighter_state*
fighter_neutral_state::HandleInput(fighter* Fighter, input_buffer* Input)
{
    if(Input->Jump.IsDown)
    {   
        if(Input->MoveLeft.IsDown && !Input->MoveRight.IsDown)
        {
            Direction = direction::Left;
        }
        else if(Input->MoveRight.IsDown && !Input->MoveLeft.IsDown)
        {
            Direction = direction::Right;
        }
        else
        {
            Direction = direction::Neutral;
        }

        return Fighter->JumpingState;
    }
    if(Input->MoveLeft.IsDown && !Input->MoveRight.IsDown)
    {
        Direction = direction::Left;
        
        return Fighter->WalkingState;
    }
    if(Input->MoveRight.IsDown && !Input->MoveLeft.IsDown)
    {
        Direction = direction::Right;
        
        return Fighter->WalkingState;
    }
    
    return nullptr;
}

fighter_walking_state::fighter_walking_state(real32 HorizontalSpeed)
        :
        fighter_state("walk", HorizontalSpeed)
{
}

void
fighter_walking_state::Update(fighter* Fighter)
{
    switch(Direction)
    {
        case(direction::Left):
        {
        } break;
        case(direction::Right):
        {
        } break;
        default:
        {
            Debug::WriteString("Walking state is corrupted!\n");
        } break;
    }
}

fighter_state*
fighter_walking_state::HandleInput(fighter* Fighter, input_buffer* Input)
{
    if(Input->Jump.IsDown) return Fighter->JumpingState;
    
    switch(Direction)
    {
        case(direction::Left):
        {
            if(!Input->MoveLeft.IsDown) return Fighter->NeutralState;
            if(Input->MoveRight.IsDown) return Fighter->NeutralState;
        } break;
        case(direction::Right):
        {
            if(!Input->MoveRight.IsDown) return Fighter->NeutralState;
            if(Input->MoveLeft.IsDown) return Fighter->NeutralState;
        } break;
        default:
        {
            Debug::WriteString("Invalid direction in fighter_walking_state\n");
        } break;
    }
    
    return nullptr;
}

void
fighter_jumping_state::Enter(fighter* Fighter)
{
    VerticalSpeed = InitialVerticalSpeed;
    FastFall = false;
    Landed = false;
}

fighter_jumping_state::fighter_jumping_state(real32 HorizontalSpeed,
                                             real32 InitialVerticalSpeed, real32 VerticalAcceleration)
        :
        fighter_state("jump", HorizontalSpeed, InitialVerticalSpeed),
        Landed(false),
        InitialVerticalSpeed(InitialVerticalSpeed),
        VerticalAcceleration(VerticalAcceleration),
        FastFall(false)
{
}

fighter_state*
fighter_jumping_state::HandleInput(fighter* Fighter, input_buffer* Input)
{   
    if(Landed)
    {
        return Fighter->NeutralState;
    }
    if(Input->Crouch.IsDown)
    {
        if(VerticalSpeed >= 0) FastFall = true;
    }

    return nullptr;
}

void
fighter_jumping_state::Update(fighter* Fighter)
{
    if(!FastFall)
    {
        VerticalSpeed += VerticalAcceleration;
    }
    else
    {
        VerticalSpeed += 4*VerticalAcceleration;
    }
    
    if(Fighter->Y + VerticalSpeed >= 500 && VerticalSpeed > 0)
    {
        Fighter->Y = 500;
        VerticalSpeed = 0;
        Landed = true;
    }
}

void
fighter::StepPosition()
{
    X += (int8)(FighterState->Direction) * FighterState->HorizontalSpeed;
    Y += FighterState->VerticalSpeed;
}

fighter::fighter(real32 X, real32 Y, real32 MoveSpeed)
        :
        X(X), Y(Y),
        NeutralState(new fighter_neutral_state),
        WalkingState(new fighter_walking_state(MoveSpeed)),
        JumpingState(new fighter_jumping_state(MoveSpeed, -20.0f, 1.0f)),
        // TODO(tyler): Move sprite to fighter states.
        Sprite(Global::ImagePath + "RedSquare/Neutral/.ani")
{   
    FighterState = NeutralState;
}

fighter::~fighter()
{
    delete NeutralState;
    delete WalkingState;
    delete JumpingState;
}

void
fighter::HandleInput(input_buffer* Input)
{
    fighter_state* NewState = FighterState->HandleInput(this, Input);

    if(NewState)
    {
        FighterState->Exit(this, NewState);
        FighterState = NewState;
        FighterState->Enter(this);
    }
}

void
fighter::Update()
{
    FighterState->Update(this);
    StepPosition();

    Sprite.AdvanceFrame();
}

void
fighter::Blit()
{
    Sprite.Draw(X, Y);
}
