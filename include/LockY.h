#ifndef LockY_H_
#define LockY_H_

#include "Struct.h"
#include <C12832.h>

class LockY{
    private:
        C12832 lcd;
        Joystick joystick;
        AnalogIn potentiometerDown;
        AnalogIn potentiometerUP;
        int highScore;
        int main();
        int game();
        void drawArc(int x, int y, int radius, int startAngle, int endAngle, uint8_t color);
    public:
        LockY(lcdPin lcdPin, Joystick joystickPin, PinName potenUp, PinName potenDown);
        int startingPage();
};

#endif //LockY_H_