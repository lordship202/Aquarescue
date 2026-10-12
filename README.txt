# AquaRescue SDG 6 — Arduino-connected prototype

## Files
- `index.html`: responsive dashboard (HTML, CSS and JavaScript)
- `arduino/AquaRescue.ino`: Arduino Uno sketch for a digital water-leak sensor and HC-SR04 ultrasonic distance sensor

## Hardware and wiring
- Arduino Uno + USB data cable
- Digital water leak sensor module: VCC -> 5V, GND -> GND, DO/OUT -> D2
- HC-SR04: VCC -> 5V, GND -> GND, TRIG -> D9, ECHO -> D10
- Keep all grounds connected. Do not put the Arduino or exposed electronics in water. Test with the sensor module only and keep electronics dry.

## Upload the Arduino code
1. Install/open Arduino IDE.
2. Open `arduino/AquaRescue.ino`.
3. Connect the Uno with a USB data cable.
4. Choose Tools -> Board -> Arduino Uno and select the correct Port.
5. Upload the sketch.
6. Close Serial Monitor before connecting the browser, because only one app can usually use the serial port at a time.

## Run the website with Web Serial
Web Serial is supported in current desktop Chrome/Edge on a secure context. Use `localhost` or HTTPS, not a plain `file://` URL.
1. Open the folder in Visual Studio Code.
2. Install the Live Server extension if needed.
3. Right-click `index.html` -> Open with Live Server.
4. Click **Connect Arduino**, choose the Uno port, and allow connection.
5. The dashboard should display live leak state and distance. Click **Disconnect Arduino** to return to demo mode.

## Sensor calibration
Many leak modules have both AO and DO pins and a small sensitivity potentiometer. This sketch reads DO. The default assumes LOW means wet; if your module behaves in reverse, set `LEAK_ACTIVE_LOW` to `false`. Test the module safely before relying on readings.

## Important limitations
- The website receives sensor data only; it does not yet drive motors. Robot movement buttons only move the on-screen illustration. Real movement needs a motor driver, motors, power supply, and additional Arduino commands with safety stops.
- The battery indicator is not measured by this wiring and is marked unavailable when connected.
- A leak/moisture sensor does not prove water is safe to drink. Potability needs appropriate certified water-quality testing.
- The website's simulated scan mode uses random demo values while no Arduino is connected.


## Expanded arena presentation
The dashboard now includes a more detailed arena scene (community, pipeline, tank, drain, obstacle, inspection point, leak marker, robot base and patrol route), a guided on-screen demo, demo leak/obstacle scenarios, a return-to-base action, and a tickable build/display checklist.

The guided demo and manual controls are screen-only animations. They do not drive physical motors. For a moving robot, add a motor driver and compatible DC motors, a suitable motor power supply, an emergency stop, and Arduino command handling before testing. Do not power motors directly from Arduino GPIO pins.
