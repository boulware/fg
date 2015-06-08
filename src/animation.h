#if !defined(ANIMATION_H)

#include "Constants.h"

#include "frame.h"

class animation
{
private:
    // TODO(tyler): This can probably be optimized to a fixed-size structure if needed.
    std::vector<frame> Frames;
    uint16 CurrentFrame;
public:
    animation();

    void AppendFrame(std::string Filename);
    void LoadFrameDirectory(std::string Directory);
    void AdvanceFrame();
    //    void InsertFrame(frame Frame, int16 FrameIndex = -1);
    void Blit(bitmap* DestBitmap, int16 XOffset, int16 YOffset);
};

#define ANIMATION_H
#endif
