#if !defined(FIGHTER_H)

#include "input_buffer.h"
#include "sprite.h"

class fighter;

class fighter_state
{
protected:
    enum class face_direction : int8
    {
        left,
        right,
    };
    enum class move_direction : int8
    {
        left,
        right,
        neutral,
    };
private:
    face_direction FaceDirection;
    move_direction MoveDirection;
protected:
    virtual void InvalidState() { Debug::WriteError("State in invalid substate (" + Label + ")"); }

    std::map<face_direction, sprite> Sprites;
    void AddSprite(face_direction SpriteFaceDirection, std::string SpriteFilepath, bool Loops = true) { Sprites.insert(std::pair<face_direction, sprite>(SpriteFaceDirection, {SpriteFilepath, Loops})); }
    
    void SetFaceDirection(face_direction NewFaceDirection);
    void SetMoveDirection(move_direction NewMoveDirection);
    face_direction GetFaceDirection() { return FaceDirection; }
    move_direction GetMoveDirection() { return MoveDirection; }

    sprite& GetCurrentSprite();
public:
    real32 BaseXSpeed;
    real32 BaseYSpeed;
    
    real32 CurrentXSpeed;
    real32 CurrentYSpeed;
    
    std::string Label;

    fighter_state(std::string Label, real32 BaseXSpeed = 0, real32 BaseYSpeed = 0);
    
    virtual void Enter(fighter& Fighter, fighter_state& PreviousState);
    virtual fighter_state* HandleInput(fighter& Fighter, const input_buffer& Input) = 0;
    virtual void Update(fighter& Fighter);
    virtual void Exit(fighter& Fighter);

    void Draw(int16 X, int16 Y);
};

class fighter_neutral_state : public fighter_state
{
private:
public:
    fighter_neutral_state();
 
    void Enter(fighter& Fighter, fighter_state& PreviousState) override;
    fighter_state* HandleInput(fighter& Fighter, const input_buffer& Input) override;    
};

class fighter_walking_state : public fighter_state
{
private:
public:
    fighter_walking_state(real32 HorizontalSpeed);
    
    void Enter(fighter& Fighter, fighter_state& PreviousState) override;
    fighter_state* HandleInput(fighter& Fighter, const input_buffer& Input) override;
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
    fighter_state* HandleInput(fighter& Fighter, const input_buffer& Input) override;
    void Update(fighter& Fighter) override;
};

class fighter_standing_light_punch_state : public fighter_state
{
private:
public:
    fighter_standing_light_punch_state();

    fighter_state* HandleInput(fighter& Fighter, const input_buffer& Input) override;
    void Update(fighter& Fighter) override;
};

class fighter
{
    friend class fighter_state;
    friend class fighter_neutral_state;
    friend class fighter_walking_state;
    friend class fighter_jumping_state;
    friend class fighter_standing_light_punch_state;
protected:
    void StepPosition();
private:
    real32 X, Y;
    real32 MoveSpeed;

    fighter_state* FighterState;
    
    fighter_neutral_state NeutralState;
    fighter_walking_state WalkingState;
    fighter_jumping_state JumpingState;
    fighter_standing_light_punch_state StandingLPState;
public:    
    fighter(real32, real32, real32 MoveSpeed = 6.0f);
    ~fighter();
    
    void HandleInput(input_buffer& Input);
    void Update();
    void Draw();
};

#define FIGHTER_H
#endif
