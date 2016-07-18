# Wio-my-light
A program I made for my [Wio Link](http://seeed-studio.github.io/Wio_Link).

It allows you to control your light (in my case, the Grove "WS2812 LED Strip 60") with:
- Gestures (using the Grove "Gesture v1.0")
- Button (using the Grove "Button")
- Internet (using the API)

# How to?

### 1. Clone this repository

    git clone https://github.com/6A/wio-my-light.git`

### 2. Push program to device

    scriptcs Deploy.csx -- [device token]

You need [scriptcs](https://github.com/scriptcs/scriptcs) to automate the build process.

If you don't have it, follow [this API guide](http://seeed-studio.github.io/Wio_Link/#trigger-the-ota-process-for-node) to do things manually.

### 3. Wait for the program to get compiled
It'll take some time. You can check the status using this command:

    curl https://us.wio.seeed.io/v1/ota/status?access_token=[device token]

### 4. Voilà!
Done, your device has now both offline and online support! Now let's add a few features!

##### Toggle light from the Internet

    curl https://us.wio.seeed.io/v1/node/function/toggle?access_token=[device token] -d arg="none"

##### Change color from the Internet

    curl https://us.wio.seeed.io/v1/node/function/color?access_token=[device token] -d arg="FFFFFF"

##### Enable / disable strict mode
In my case, the gesture often triggered itself without any reason.  
I thus added a "strict mode" to the program, that I enable when I'm not in the room.

When enabled, the gesture will not work to turn on the light. Only the button and the Internet will work.  
When disabled, everything will work.

You can enable / disable strict mode using the API:

    curl -X POST https://us.wio.seeed.io/v1/node/variable/strict/[0 or 1]?access_token=[device token]

# Notes
The loop is only called every 400ms. That means some gestures won't get recognized, and the button must be pressed a bit longer to trigger the event.
You can change this if you want to.