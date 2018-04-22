
#ifndef __MAIN_H__
#define __MAIN_H__

#include "suli2.h"
#include "grove_led_ws2812.h"
#include "grove_ir_distance_intr.h"
#include "grove_digital_light.h"

extern GroveLedWs2812 *GroveLedWs2812D1_ins;
extern GroveIRDistanceInterrupter *GroveIRDistanceInterrupterD2_ins;
extern GroveDigitalLight *GroveDigitalLightI2C0_ins;

#endif