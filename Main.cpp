#include "Main.h"
#include "wio.h"
#include "suli2.h"
#include "grove_button.h"
#include "grove_gesture_paj7620.h"
#include "grove_led_ws2812.h"

int pinsda = 4;
int pinscl = 5;

uint32_t time;

bool lightOn = false;
bool strict = false;
char* color = "FF8F07";

// set the state of the light (on or off)
void setLight(bool isOn)
{
    if (lightOn == isOn)
        return;
    else
        lightOn = isOn;

    if (isOn)
        GroveLedWs2812D2_ins->write_clear(30, color);
    else
        GroveLedWs2812D2_ins->write_clear(30, "000000");
}

// api method to toggle light state
void toggleLight(char* arg)
{
    setLight(!lightOn);
}

// api method to change the color of the led strip
void changeColor(char* arg)
{
    color = arg;
}


void setup()
{
    time = millis();

    wio.registerFunc("toggle", toggleLight);
    wio.registerFunc("color", changeColor);

    wio.registerVar("strict", strict);
}

void loop()
{
    uint32_t now = millis();

    // loop every 400ms
    if (now - time > 400)
    {
        time = now;
        
        // 1. check btn
        uint8_t isPressed;
        if (GroveButtonD0_ins->read_pressed(&isPressed) && isPressed == 1)
        {
            setLight(!lightOn);
            return;
        }

        // 2. check gesture
        uint8_t motion;
        if (GroveGestureI2C0_ins->read_motion(&motion) && motion > 0 && motion < 255)
        {
            // only turn on light if strict mode is disabled
            //  sometimes, the gesture triggers itself, which is a problem during the day
            //  or when i am not home
            //  the user can thus remotely enable / disable strict mode
            //  which disallows the gesture to turn on the lights

            if (lightOn)
                setLight(false);
            else if (!strict)
                setLight(true);

            return;
        }
    }
}