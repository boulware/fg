#if !defined(FIGHTER_H)

#include "input_buffer.h"
#include "sprite.h"

class fighter;

enum class direction : int8
{
    Left = -1,
    Neutral = 0,
    Right = 1,
    Undefined = 42,
};

class fighter_state
{
public:
    std::string Label;
    
    direction Direction;
    real32 HorizontalSpeed;
    real32 VerticalSpeed;

    std::vector<sprite> Sprites;

    fighter_state(std::string Label, real32 HorizontalSpeed = 0.0f, real32 VerticalSpeed = 0.0f);
    
    virtual void Enter(fighter* Fighter) {};    
    virtual fighter_state* HandleInput(fighter* Fighter, input_buffer* Input) = 0;
    virtual void Update(fighter* Fighter) {};
    virtual void Exit(fighter* Fighter, fighter_state* NewState);
};

class fighter_neutral_state : public fighter_state
{
public:
    fighter_neutral_state();
    fighter_state* HandleInput(fighter*, input_buffer*);
};

class fighter_walking_state : public fighter_state
{
public:
    fighter_walking_state(real32 HorizontalSpeed);
    fighter_state* HandleInput(fighter*, input_buffer*);
    void Update(fighter* Fighter);
};

class fighter_jumping_state : public fighter_state
{
public:
//    void Enter(fighter*);
    void Enter(fighter* Fighter);
    fighter_jumping_state(real32 HorizontalSpeed, real32 InitialVerticalSpeed, real32 VerticalAcceleration);
    fighter_state* HandleInput(fighter*, input_buffer*);
    void Update(fighter*);
private:
    bool32 Landed;
    
    real32 InitialVerticalSpeed;
    real32 VerticalAcceleration;

    bool32 FastFall;
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
    
    fighter_neutral_state* NeutralState;
    fighter_walking_state* WalkingState;
    fighter_jumping_state* JumpingState;

    sprite Sprite;
public:
    
    fighter(real32, real32, real32 MoveSpeed = 6.0f);
    ~fighter();
    
    void HandleInput(input_buffer* Input);
    void Update();
    void Blit();
};

#define FIGHTER_H
#endif
