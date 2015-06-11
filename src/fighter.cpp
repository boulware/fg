#include "fighter.h"

#include "Globals.h"

void
fighter_state::SetFaceDirection(face_direction NewFaceDirection)
{   
    FaceDirection = NewFaceDirection;

    GetCurrentSprite().Reset();
}

void
fighter_state::SetMoveDirection(move_direction NewMoveDirection)
{
    MoveDirection = NewMoveDirection;
}

sprite& fighter_state::GetCurrentSprite()
{
    try
    {
        sprite& Sprite = Sprites.at(FaceDirection);
        return Sprite;
    }
    catch(...)
    {
        Debug::WriteError("Tried to access fighter_state sub-state sprite for which a sprite had not been loaded (" + Label + ").");
        
        return sprite::LoadFailSprite;
    }
}

fighter_state::fighter_state(std::string Label, real32 BaseXSpeed, real32 BaseYSpeed)
        :
        Label(Label),
        BaseXSpeed(BaseXSpeed),
        BaseYSpeed(BaseYSpeed),
        CurrentXSpeed(0),
        CurrentYSpeed(0),
        FaceDirection(face_direction::right),
        MoveDirection(move_direction::neutral)
{
}

void
fighter_state::Enter(fighter& Fighter, fighter_state& PreviousState)
{
    SetMoveDirection(PreviousState.MoveDirection);
    SetFaceDirection(PreviousState.FaceDirection);
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
    GetCurrentSprite().AdvanceFrame();
}

void
fighter_state::Draw(int16 X, int16 Y)
{
    GetCurrentSprite().Draw(X, Y);
}

fighter_neutral_state::fighter_neutral_state()
        :
        fighter_state("neutral")
{
    AddSprite(face_direction::right, "RedSquare/neutral/face_right/.ani");
    AddSprite(face_direction::left, "RedSquare/neutral/face_left/.ani");
}

void
fighter_neutral_state::Enter(fighter &Fighter, fighter_state& PreviousState)
{
    SetMoveDirection(move_direction::neutral);
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
        SetFaceDirection(face_direction::left);
        SetMoveDirection(move_direction::left);
    }
    if(Input.MoveRight.IsDown && !Input.MoveLeft.IsDown)
    {
        SetFaceDirection(face_direction::right);
        SetMoveDirection(move_direction::right);
    }
    if(Input.Jump.IsDown)
    {   
        return &Fighter.JumpingState;
    }
    if(GetMoveDirection() != move_direction::neutral) return &Fighter.WalkingState;
    
    return nullptr;
}

fighter_walking_state::fighter_walking_state(real32 BaseXSpeed)
        :
        fighter_state("walk", BaseXSpeed)
{
    AddSprite(face_direction::left, "RedSquare/walk/moving_left/.ani");
    AddSprite(face_direction::right, "RedSquare/walk/moving_right/.ani");    
}

void
fighter_walking_state::Enter(fighter& Fighter, fighter_state& PreviousState)
{
    fighter_state::Enter(Fighter, PreviousState);
    
    switch(GetMoveDirection())
    {
        case(move_direction::left):
        {
            CurrentXSpeed = -BaseXSpeed;
        } break;
        case(move_direction::right):
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

    switch(GetMoveDirection())
    {
        case(move_direction::left):
        {
            if(!Input.MoveLeft.IsDown || Input.MoveRight.IsDown) return &Fighter.NeutralState;
        } break;
        case(move_direction::right):
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

    switch(GetMoveDirection())
    {
        case(move_direction::neutral):
        {
            CurrentXSpeed = 0;
        } break;
        case(move_direction::left):
        {
            CurrentXSpeed = -BaseXSpeed;
        } break;
        case(move_direction::right):
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
    AddSprite(face_direction::left, "RedSquare/jump/face_left/.ani");
    AddSprite(face_direction::right, "RedSquare/jump/face_right/.ani");
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
    AddSprite(face_direction::right, "RedSquare/sLP/face_right/.ani", false);
    AddSprite(face_direction::left, "RedSquare/sLP/face_left/.ani", false);
}

void
fighter_standing_light_punch_state::Update(fighter& Fighter)
{
    fighter_state::Update(Fighter);
}

fighter_state*
fighter_standing_light_punch_state::HandleInput(fighter& Fighter, const input_buffer& Input)
{
    if(GetCurrentSprite().GetAnimationEnded()) return &Fighter.NeutralState;

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
