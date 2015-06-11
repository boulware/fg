#include "fighter.h"

void
fighter_state::SetSubState(sub_state NewSubState, bool32 ResetSprite)
{
    SubState = NewSubState;

    if(ResetSprite)
    {
        try
        {
            Sprites.at(NewSubState).Reset();
        }
        catch(...)
        {
            Debug::WriteError("Tried to reset sub-state sprite for which a sprite did not exist (" + Label + ").");
        }
    }
}

fighter_state::fighter_state(std::string Label, real32 BaseXSpeed, real32 BaseYSpeed)
        :
        Label(Label),
        BaseXSpeed(BaseXSpeed),
        BaseYSpeed(BaseYSpeed),
        CurrentXSpeed(0),
        CurrentYSpeed(0),
        SubState(sub_state::neutral)
{
}

void
fighter_state::Enter(fighter& Fighter, fighter_state& PreviousState)
{
    SetSubState(PreviousState.SubState);
    if(Global::DebugMode)
    {
        Debug::WriteDebug("Entering state: " + Label);
    }
}

void
fighter_state::Exit(fighter &Fighter)
{
    if(Global::DebugMode)
    {
        Debug::WriteDebug("Exiting state: " + Label);
    }
}

void
fighter_state::Update(fighter &Fighter)
{
    Sprites.at(SubState).AdvanceFrame();
}

void
fighter_state::Draw(int16 X, int16 Y)
{
    try
    {
        Sprites.at(SubState).Draw(X, Y);
    }
    catch(...)
    {
        Debug::WriteError("Tried to draw sub-state sprite for which one did not exist (" + Label + ").");
    }
}

fighter_neutral_state::fighter_neutral_state()
        :
        fighter_state("neutral")
{
    AddSprite(sub_state::neutral, Global::ImagePath + "RedSquare/neutral/neutral/.ani");
}

void
fighter_neutral_state::Enter(fighter& Fighter, fighter_state& PreviousState)
{
    SetSubState(sub_state::neutral);
}

fighter_state*
fighter_neutral_state::HandleInput(fighter& Fighter, const input_buffer& Input)
{
    if(Input.LP.WasPressed)
    {
        return &Fighter.StandingLPState;
    }
    if(Input.MoveLeft.IsDown && !Input.MoveRight.IsDown)
    {
        SetSubState(sub_state::moving_left, false);
    }
    if(Input.MoveRight.IsDown && !Input.MoveLeft.IsDown)
    {
        SetSubState(sub_state::moving_right, false);
    }
    if(Input.Jump.IsDown)
    {   
        return &Fighter.JumpingState;
    }
    if(GetSubState() != sub_state::neutral) return &Fighter.WalkingState;
    
    return nullptr;
}

fighter_walking_state::fighter_walking_state(real32 BaseXSpeed)
        :
        fighter_state("walk", BaseXSpeed)
{
    AddSprite(sub_state::moving_left, Global::ImagePath + "RedSquare/walk/moving_left/.ani");
    AddSprite(sub_state::moving_right, Global::ImagePath + "RedSquare/walk/moving_right/.ani");    
}

void
fighter_walking_state::Enter(fighter& Fighter, fighter_state& PreviousState)
{
    fighter_state::Enter(Fighter, PreviousState);
    switch(GetSubState())
    {
        case(sub_state::moving_left):
        {
            CurrentXSpeed = -BaseXSpeed;
        } break;
        case(sub_state::moving_right):
        {
            CurrentXSpeed = BaseXSpeed;
        } break;
        default:
        {
            InvalidState();
        }
    }
}

fighter_state*
fighter_walking_state::HandleInput(fighter& Fighter, const input_buffer& Input)
{
    if(Input.Jump.IsDown) return &Fighter.JumpingState;

    switch(GetSubState())
    {
        case(sub_state::moving_left):
        {
            if(!Input.MoveLeft.IsDown || Input.MoveRight.IsDown) return &Fighter.NeutralState;
        } break;
        case(sub_state::moving_right):
        {
            if(!Input.MoveRight.IsDown || Input.MoveLeft.IsDown) return &Fighter.NeutralState;
        } break;
        default:
        {
            InvalidState();
            return &Fighter.NeutralState;
        } break;
    }
    
    return nullptr;
}

void
fighter_jumping_state::Enter(fighter& Fighter, fighter_state& PreviousState)
{
    fighter_state::Enter(Fighter, PreviousState);
        
    switch(GetSubState())
    {
        case(sub_state::neutral):
        {
            CurrentXSpeed = 0;
        } break;
        case(sub_state::moving_left):
        {
            CurrentXSpeed = -BaseXSpeed;
        } break;
        case(sub_state::moving_right):
        {
            CurrentXSpeed = BaseXSpeed;
        } break;
        default:
        {
            InvalidState();
        } break;
    }
    
    CurrentYSpeed = InitialYSpeed;
    FastFall = false;
    Landed = false;
}

fighter_jumping_state::fighter_jumping_state(real32 HorizontalSpeed,
                                             real32 InitialYSpeed, real32 VerticalAcceleration)
        :
        fighter_state("jump", HorizontalSpeed, InitialYSpeed),
        Landed(false),
        InitialYSpeed(InitialYSpeed),
        VerticalAcceleration(VerticalAcceleration),
        FastFall(false)
{
    AddSprite(sub_state::neutral, Global::ImagePath + "RedSquare/jump/neutral/.ani");
    AddSprite(sub_state::moving_left, Global::ImagePath + "RedSquare/jump/moving_left/.ani");
    AddSprite(sub_state::moving_right, Global::ImagePath + "RedSquare/jump/moving_right/.ani");
}

fighter_state*
fighter_jumping_state::HandleInput(fighter& Fighter, const input_buffer& Input)
{   
    if(Landed)
    {
        return &Fighter.NeutralState;
    }
    if(Input.Crouch.IsDown)
    {
        if(CurrentYSpeed >= 0) FastFall = true;
    }

    return nullptr;
}

void
fighter_jumping_state::Update(fighter& Fighter)
{
    fighter_state::Update(Fighter);
    
    if(!FastFall)
    {
        CurrentYSpeed += VerticalAcceleration;
    }
    else
    {
        CurrentYSpeed += 4*VerticalAcceleration;
    }
    
    if(Fighter.Y + CurrentYSpeed >= 500 && CurrentYSpeed > 0)
    {
        Fighter.Y = 500;
        CurrentYSpeed = 0;
        Landed = true;
    }
}

fighter_standing_light_punch_state::fighter_standing_light_punch_state()
        :
        fighter_state("sLP")
{
    AddSprite(sub_state::neutral, Global::ImagePath + "RedSquare/sLP/neutral/.ani", false);
}

void
fighter_standing_light_punch_state::Update(fighter& Fighter)
{
    fighter_state::Update(Fighter);
}

fighter_state*
fighter_standing_light_punch_state::HandleInput(fighter& Fighter, const input_buffer& Input)
{
    if(Sprites.at(GetSubState()).GetAnimationEnded()) return &Fighter.NeutralState;

    return nullptr;
}

void
fighter::StepPosition()
{
    X += FighterState->CurrentXSpeed;
    Y += FighterState->CurrentYSpeed;
}

fighter::fighter(real32 X, real32 Y, real32 MoveSpeed)
        :
        X(X), Y(Y),
        NeutralState(),
        WalkingState(fighter_walking_state(MoveSpeed)),
        JumpingState(fighter_jumping_state(MoveSpeed, -20.0f, 1.0f))
{   
    FighterState = &NeutralState;
}

fighter::~fighter()
{
}

void
fighter::HandleInput(input_buffer& Input)
{
    fighter_state* NewState = FighterState->HandleInput(*this, Input);

    if(NewState)
    {
        FighterState->Exit(*this);
        NewState->Enter(*this, *FighterState);
        FighterState = NewState;
    }
}

void
fighter::Update()
{
    FighterState->Update(*this);
    StepPosition();
}

void
fighter::Draw()
{
    FighterState->Draw(X, Y);
}
