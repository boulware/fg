#if !defined(FIGHTER_H)

#include "input_buffer.h"
#include "sprite.h"

class fighter;

class fighter_state
{
protected:
    enum class sub_state : int8
    {
        neutral,
        moving_left,
        moving_right,
     };
private:
    sub_state SubState;
protected:
    virtual void InvalidState() { Debug::WriteError("State in invalid substate (" + Label + ")"); }

    std::map<sub_state, sprite> Sprites;
    void AddSprite(sub_state SpriteSubState, std::string SpriteFilepath) { Sprites.insert(std::pair<sub_state, sprite>(SpriteSubState, {SpriteFilepath})); }
    void SetSubState(sub_state NewSubState, bool32 ResetSprite = true);
    sub_state GetSubState() { return SubState; }
public:
    real32 BaseXSpeed;
    real32 BaseYSpeed;
    
    real32 CurrentXSpeed;
    real32 CurrentYSpeed;
    
    std::string Label;

    fighter_state(std::string Label, real32 BaseXSpeed = 0, real32 BaseYSpeed = 0);
    
    virtual void Enter(fighter& Fighter, fighter_state& PreviousState);
    virtual fighter_state* HandleInput(fighter& Fighter, input_buffer& Input) = 0;
    virtual void Update(fighter& Fighter);
    virtual void Exit(fighter& Fighter) {}

    void Draw(int16 X, int16 Y);
};

class fighter_neutral_state : public fighter_state
{
private:
public:
    fighter_neutral_state();
 
    void Enter(fighter& Fighter, fighter_state& PreviousState) override;
    fighter_state* HandleInput(fighter& Fighter, input_buffer& Input) override;    
};

class fighter_walking_state : public fighter_state
{
private:
public:
    fighter_walking_state(real32 HorizontalSpeed);
    
    void Enter(fighter& Fighter, fighter_state& PreviousState) override;
    fighter_state* HandleInput(fighter& Fighter, input_buffer& Input) override;
};

class fighter_jumping_state : public fighter_state
{
private:
    bool32 Landed;

    real32 InitialYSpeed;
    real32 VerticalAcceleration;

    bool32 FastFall;
public:
    fighter_jumping_state(real32 HorizontalSpeed, real32 InitialVerticalSpeed, real32 VerticalAcceleration);
    
    void Enter(fighter& Fighter, fighter_state& PreviousState) override;
    fighter_state* HandleInput(fighter& Fighter, input_buffer& Input) override;
    void Update(fighter& Fighter) override;
};

class fighter
{
    friend class fighter_state;
    friend class fighter_neutral_state;
    friend class fighter_walking_state;
    friend class fighter_jumping_state;
protected:
    void StepPosition();
private:
    real32 X, Y;
    real32 MoveSpeed;

    fighter_state* FighterState;
    
    fighter_neutral_state NeutralState;
    fighter_walking_state WalkingState;
    fighter_jumping_state JumpingState;
public:    
    fighter(real32, real32, real32 MoveSpeed = 6.0f);
    ~fighter();
    
    void HandleInput(input_buffer& Input);
    void Update();
    void Draw();
};

#define FIGHTER_H
#endif
