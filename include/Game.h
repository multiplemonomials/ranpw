#ifndef Game_H_
#define Game_H_

#include "LCatch.h"
#include "Pong.h"
#include "LockY.h"

class Game{
    public:
        LCatch lcatch;
        LockY lockY;
        // Pong pong;
        Game(lcdPin lcdPin, Joystick joystick);
};

inline Game::Game(lcdPin lcdPin, Joystick joystick) : lcatch(lcdPin, joystick), lockY(lcdPin, joystick, p21, p22){}
#endif //Game_H_