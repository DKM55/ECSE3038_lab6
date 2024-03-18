# Remote Temperature Monitoring and Light Control System

## Summary of Functions

### `patchTemp(float temp)`
This function sends the temperature data to a specified endpoint via an HTTP PATCH request. It expects a single parameter `temp`, which is the temperature value to be sent.

### `getLightState()`
This function retrieves the state of the light from a specified endpoint via an HTTP GET request. It returns a boolean value indicating whether the light is ON or OFF.

## Purpose of the Code
This code was written to implement a remote temperature monitoring and light control system. The system allows users to monitor the temperature remotely and control the state of a connected light over the internet.

The code utilizes an Arduino microcontroller, temperature sensor, WiFi module, and HTTP requests to communicate with a remote server hosting an API. It periodically reads the temperature from the sensor and sends it to the server. It also retrieves the state of the light from the server and controls the connected LED accordingly.


