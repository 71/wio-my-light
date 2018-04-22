#include "Main.h"
#include "wio.h"
#include "suli2.h"
#include "grove_led_ws2812.h"

const uint32_t INTERVAL = 300;
const uint32_t WAIT = 1000;
const char* COLOR = "FF8F07";

uint32_t time;
uint32_t wait = INTERVAL;

bool lightOn = false;

// set the state of the light (on or off)
void setLight(bool isOn)
{
    lightOn = isOn;

    if (isOn)
        GroveLedWs2812D1_ins->write_clear(30, COLOR);
    else
        GroveLedWs2812D1_ins->write_clear(30, "000000");
}

void setup()
{
    time = millis();
}

void loop()
{
    uint32_t now = millis();

    if (now - time > wait)
    {
        time = now;

        uint8_t approach;
        
        if (GroveIRDistanceInterrupterD2_ins->read_approach(&approach) && approach == 1)
        {
            setLight(!lightOn);

            wait = WAIT;
        }
        else
        {
            wait = INTERVAL;
        }
    }
}
