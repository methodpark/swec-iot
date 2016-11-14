# SWEC 2016 IoT Workshop

## Step 1: Connecting

### About the Photon

https://www.particle.io/
> With Particle's Photon series of hardware development kits, connectivity modules, and accessories, you can quickly and easily build Wi-Fi connected products.
> The Photon architecture sits at the heart of a huge range of IoT products, from smart home products to commercial sensor networks.

The Photons can be connected to a power shield for mobile usage. The correct way to connect them:

![alt text](https://docs.particle.io/assets/images/shields/power-shield/power-shield-photon-plugged.png)

### Particle Cloud

We have created Particle accounts for up to five groups in the SWEC IoT workshop.
When **x** is your group number (1..5), your account on Particle (https://login.particle.io/login) is: 

`iot.swecx@gmail.com`

The password for all accounts is 

`MethodPark19a`

Two Particle Photons are connected with each account: `SWEC-x` (the one with the breadboard) and `SWEC-xa`.

## Step 2: First LED

### About I/Os

https://en.wikipedia.org/wiki/General-purpose_input/output

### Install the free 'Particle' app
* Android: https://play.google.com/store/apps/details?id=io.particle.android.app
* iOS: https://itunes.apple.com/us/app/particle-build-photon-electron/id991459054?ls=1&mt=8

### Toggling the on-board LED
* Connect one (or both) of your photons to the power supply
* Connect to your photon with the Particle App
* The photon currently runs the tinker firmware, which allows you to access the individual pins with the Particle App
* In the Paticle App: Set port 'D7' to 'digitalWrite' and then set it to 'HIGH'
 * This port is connected to the on-board LED

## Step 3: One more LED

### Adding the external LED

* The photon package contains
 * a LED
 * a resistor
 * a small scetch on how to connect the LED
* Never connect the LED without a resistor or it will get damaged
* Test the LED using the Particle App

### Write software to get the LED blinking

* Web IDE: https://build.particle.io/build
* Detailed description: https://docs.particle.io/guide/getting-started/examples/photon/#blink-an-leds

## Step 4: A Photoresistor

### What is a photoresistor?

* A resistor that changes it's resistance depending on how much light hits its surface

### Adding the photoresistor

* The photon package also contains
 * a photoresistor
 * a second resistor
 * a small scetch on how to connect the photoresistor
* Test the photoresistor using the Particle App

## Step 5: Publishing to the photon cloud

* Send your brightness into the photon cloud and read it with the Photon App
* Documentation for clound-functions: https://docs.particle.io/reference/firmware/photon/#cloud-functions

## Step 6: A temperature sensor

* Add the temperature sensor and publish the temperture to the photon cloud
* Documentation: http://diotlabs.daraghbyrne.me/3-working-with-sensors/DS18B20/

## Step 7: Connecting your photons

### Your Task

* Use the particle cloud to communicate with your photons
* One photon publishes some sensor data
 * e.g. temperature or brightness
* The other photon listens to this data and reacts to it
 * e.g. enable the on-board LED when brightness drops

### Publish/Subscribe in the photon cloud

* See reference documentation: https://docs.particle.io/reference/firmware/p<hoton/#cloud-functions

## Step 8: Getting connected with MQTT

### What is MQTT?

https://en.wikipedia.org/wiki/MQTT:
> MQTT is an ISO standard publish-subscribe-based "lightweight" messaging protocol for use on top of the TCP/IP protocol.
> It is designed for connections with remote locations where a "small code footprint" is required or the network bandwidth is limited.
> The publish-subscribe messaging pattern requires a message broker.
> The broker is responsible for distributing messages to interested clients based on the topic of a message.

### Yor Task

* Create new App and add the MQTT library
* Connect to the MQTT server and send a hello-world message when connected
* Subscribe to the buzzer and do something when the buzzer is pressed
 * e.g. toggle a LED 

### MQTT Server

* Hostname: openhabpi
* Port: 1883
* No authentication
* Suggested client name: The name of your photon

### MQTT library

* Callback to receive subscribed messages:
```
void mqtt_callback(char* topic, byte* payload, unsigned int length);
```
* Constructor:
```
MQTT::MQTT(String server_url, int port, callback* callback_ptr);
```
* Connecting to the server:
```
MQTT::connect(String client_name);
```
* Connecting with credentials:
```
MQTT::connect(String client_name, String user_name, String password);
```
* Publishing/Sending a message:
```
MQTT::publish(String topic, String payload);
```
* Subscribing to a topic, that will then be received via the callback:
```
MQTT::subscribe(String topic);
```

### Buzzer

* Topic: buzzer
* Payload: empty
* The message is sent each time the buzzer is pressed

## Step 9: Publish your temperture and brightness

* Send your temperature and brightness to the MQTT server
 * topic: "swec/temperature", payload: "x/t"
 * topic: "swec/brightness", payload: "x/b"
 * x: your group id (1-5)
 * t: temperature in celsius, e.g. 30.0
 * b: brightness, 0=absolute dark, 1023=very bright
 * intervall: 200ms

## Step 10: croud control

* Control the Hue with your photons