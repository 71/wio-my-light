# Wio-my-light
A program I made for my [Wio Link](http://seeed-studio.github.io/Wio_Link).

It allows you to control your light (in my case, the Grove "WS2812 LED Strip 60") with an
IR distance interrupter: getting near the sensor will toggle the light.

# Connections
Leds to D1, sensor to D2, and digital light sensor to IC2.

# How to?

### 1. Clone this repository

    git clone https://github.com/6A/wio-my-light.git

### 2. Push program to device

    scriptcs Deploy.csx -- [device token]

You need [scriptcs](https://github.com/scriptcs/scriptcs) to automate the build process.

If you don't have it, follow [this API guide](http://seeed-studio.github.io/Wio_Link/#trigger-the-ota-process-for-node) to do things manually.

### 3. Wait for the program to get compiled
It'll take some time. You can check the status using this command:

    curl https://us.wio.seeed.io/v1/ota/status?access_token=[device token]

### 4. Voilà!
Done, your device now has offline toggling support!
