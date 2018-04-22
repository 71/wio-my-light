#include "Main.h"
#include "wio.h"
#include "suli2.h"
#include "grove_led_ws2812.h"

const uint32_t INTERVAL = 150;
const uint32_t WAIT     = 1500;
const uint32_t MIN_LUX  = 120;

uint32_t time;
uint32_t wait = INTERVAL;

bool lightOn = false;

// set the state of the light (on or off)
void setLight(bool isOn)
{
    lightOn = isOn;

    if (isOn)
    {
        GroveLedWs2812D1_ins->write_start_rainbow_flow(30, 100, 1);
        GroveLedWs2812D1_ins->write_stop_rainbow_flow();
        lightOn = true;
    }
    else
    {
        GroveLedWs2812D1_ins->write_clear(30, "000000");
        lightOn = false;
    }
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
        uint32_t lux;

        if (!GroveDigitalLightI2C0_ins->read_lux(&lux) || !GroveIRDistanceInterrupterD2_ins->read_approach(&approach))
            return;

        if (lightOn && (lux > MIN_LUX || approach == 1))
        {
            setLight(false);

            wait = WAIT;
        }
        else if (!lightOn && lux <= MIN_LUX && approach == 1)
        {
            setLight(true);

            wait = WAIT;
        }
        else
        {
            wait = INTERVAL;
        }
    }
}
