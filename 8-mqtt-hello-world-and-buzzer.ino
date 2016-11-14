#include "MQTT/MQTT.h"

void mqtt_callback(char* topic, byte* payload, unsigned int length);

class Led
{
    const int pin; // This is where your LED is plugged in. The other side goes to a resistor connected to GND.
    bool state;
    
public:
    Led(int pin)
        : pin(pin), state(false)
    {
        pinMode(pin, OUTPUT); // Our LED pin is output (lighting up the LED)
    }
    
    void set(bool on)
    {
        state = on;
        digitalWrite(pin, on ? HIGH : LOW);
    }
    
    void toggle()
    {
        set(!state);
    }
};

Led led(D0);
MQTT mqtt("openhabpi", 1883, mqtt_callback);
String clientName = "swec99";

// recieve message
void mqtt_callback(char* topic, byte* payload, unsigned int length)
{
    if (String(topic).equals("buzzer"))
        led.toggle();
}

void setup()
{
    // connect to the server
    mqtt.connect(clientName);

    // publish/subscribe
    if (mqtt.isConnected()) {
        mqtt.publish(clientName + "/message", "Hello World!");
        mqtt.subscribe("buzzer");
    }
}

void loop()
{
    if (mqtt.isConnected())
        mqtt.loop();
}
