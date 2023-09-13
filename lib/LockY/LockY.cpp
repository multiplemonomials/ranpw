#include "LockY.h"
#include <random>

int floatToLine(float toAngle, bool second = false);
bool decimalCheck(float numberOne, float numberTwo, int decimalPlaces);

LockY::LockY(lcdPin lcdPin, Joystick joystickPin, PinName potenUp, PinName potenDown) : 
    lcd(lcdPin.MOSI, lcdPin.SCK, lcdPin.RESET, lcdPin.A0, lcdPin.nCS),
    joystick(joystickPin),
    potentiometerUP(potenUp),
    potentiometerDown(potenDown){}


int LockY::startingPage(){
    lcd.cls();

    //left arrow
    lcd.line(5,1,5,7,1);
    lcd.line(5,1,2,4,1);
    lcd.line(2,4,5,7,1);

    //circle
    lcd.circle(123,4,2,1);

    lcd.locate(50,0);
    lcd.printf("LockY");
    lcd.locate(0,10);
    lcd.printf("Use the two potentiometer to crack the safe");
    ThisThread::sleep_for(100ms);
    while(1){
        if(joystick.center.read()){
            lcd.cls();

            //left arrow
            lcd.line(5,1,5,7,1);
            lcd.line(5,1,2,4,1);
            lcd.line(2,4,5,7,1);

            //circle
            lcd.circle(123,4,2,1);

            lcd.locate(50,0);
            lcd.printf("LockY");
            lcd.locate(25,10);
            lcd.printf("1000 points = 1 food");

            ThisThread::sleep_for(100ms);
            while(1){
                if(joystick.center.read()){
                    lcd.cls();

                    //left arrow
                    lcd.line(5,1,5,7,1);
                    lcd.line(5,1,2,4,1);
                    lcd.line(2,4,5,7,1);

                    //circle
                    lcd.circle(123,4,2,1);

                    lcd.locate(50,0);
                    lcd.printf("LockY");
                    lcd.locate(25,10);
                    lcd.printf("Points = (int)1000/second");
                    ThisThread::sleep_for(100ms);
                    while(1){
                        if(joystick.center.read()){
                            return main();
                        }
                        if(joystick.left.read()){
                            return 0;
                        }
                    }
                }
                if(joystick.left.read()){
                    return 0;
                }
            }
        }
        if(joystick.left.read()){
            return 0;
        }
    }
}


int LockY::main(){
    int totalPoints = 0;
    lcd.cls();

    //left arrow
    lcd.line(5,1,5,7,1);
    lcd.line(5,1,2,4,1);
    lcd.line(2,4,5,7,1);

    //circle
    lcd.circle(123,4,2,1);

    lcd.locate(50,0);
    lcd.printf("LockY");

    lcd.locate(32,12);
    lcd.printf("Best time: %d", highScore);

    bool lastJ = false;
    bool currentJ = false;
    while(1){
        currentJ = joystick.center.read();
        if(currentJ && !lastJ){
            int gamePoint = game();
            if(gamePoint > highScore){
                highScore = gamePoint;
                lcd.cls();
                lcd.locate(35,15);
                lcd.printf("NEW HIGHSCORE");
                while(1){
                    if(joystick.center.read()){
                        break;
                    }
                }
            }
            totalPoints += gamePoint;
            int totalPoints = 0;
            lcd.cls();

            //left arrow
            lcd.line(5,1,5,7,1);
            lcd.line(5,1,2,4,1);
            lcd.line(2,4,5,7,1);

            //circle
            lcd.circle(123,4,2,1);

            lcd.locate(50,0);
            lcd.printf("LockY");

            lcd.locate(32,12);
            lcd.printf("Best time: %d", highScore);
            ThisThread::sleep_for(100ms);
        }
        if(joystick.left.read()){
            return totalPoints;
        }
        lastJ = currentJ;
    }
}


int LockY::game(){
    lcd.cls();

    lcd.locate(50,0);
    lcd.printf("LockY");

    Timer timer;
    timer.start();
    bool win = false;

    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<float> distrib(0.0, 1.0);
    float leftSafe = distrib(gen);
    float rightSafe = distrib(gen);

    lcd.line(0,15,127,15,1);
    //safe
    lcd.line(floatToLine(leftSafe), 15, floatToLine(leftSafe, true), 15, 0);
    lcd.line(floatToLine(rightSafe), 15, floatToLine(rightSafe, true), 15, 0);

    while(!win){
        printf("%f", rightSafe);
        //Take data from the 2 potentiometer
        float pot1 = potentiometerDown.read();
        float pot2 = potentiometerUP.read();

        //decoder
        lcd.line(0,16,127,16,0);
        lcd.line(0,14,127,14,0);
        lcd.line(floatToLine(pot1), 16, floatToLine(pot1, true), 16, 1);
        lcd.line(floatToLine(pot2), 14, floatToLine(pot2, true), 14, 1);

        if((decimalCheck(pot1, leftSafe, 2) && decimalCheck(pot2, rightSafe, 2))||(decimalCheck(pot2, leftSafe, 2) && decimalCheck(pot1, rightSafe, 2))){
            win = true;
        }

        ThisThread::sleep_for(10ms);
    }
    timer.stop();

    lcd.cls();


    int score = 100000/((timer.elapsed_time()).count());
    //circle
    lcd.circle(123,4,2,1);

    lcd.locate(50,0);
    lcd.printf("LockY");

    lcd.locate(28, 10);
    lcd.printf("YOU HAVE WIN");
    lcd.locate(30,20); 
    lcd.printf("Final Score: %d", score);
    while(1){
        if(joystick.center.read()){
            return score;
        }
    }
}


int floatToLine(float toAngle, bool second){
    if(second){
        int toReturn = (int)(toAngle * 100)+10;
        return toReturn;
    }
    return (int)(toAngle * 100);
}


bool decimalCheck(float numberOne, float numberTwo, int decimalPlaces) {
    float factor = std::pow(10, decimalPlaces);
    int rounded1 = (int)(numberOne * factor);
    int rounded2 = (int)(numberTwo * factor);

    return rounded1 == rounded2;
}