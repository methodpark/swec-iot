// This #include statement was automatically added by the Particle IDE.
#include "OneWire/OneWire.h"

// This #include statement was automatically added by the Particle IDE.
#include "spark-dallas-temperature/spark-dallas-temperature.h"

class Led
{
    const int pin; // This is where your LED is plugged in. The other side goes to a resistor connected to GND.
    bool state;
    
    // trigger set/toggle methods with strings, for use by cloud function 
    int execCommand(String command)
    {
        if (command == "on")
            set(true);
        else if (command == "off")
            set(false);
        else if (command == "toggle")
            toggle();
        else
            return -1;
        
        return state ? 1 : 0;
    }
    
public:
    Led(int pin, const String& cloudName = "")
        : pin(pin), state(false)
    {
        pinMode(pin, OUTPUT); // Our LED pin is output (lighting up the LED)
        
        // We are also going to declare a Particle.function so that we can turn the LED on and off from the cloud.
        if (cloudName.length() > 0)
            Particle.function(cloudName, &Led::execCommand, this);
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

class Photoresistor
{
    const int inputPin; // This is where your photoresistor is plugged in. The other side goes to the "power" pin (below).
    const int powerPin; // This is the other end of your photoresistor. The other side is plugged into the "photoresistor" pin (above).
    // The reason we have plugged one side into an analog pin instead of to "power" is because we want a very steady voltage to be sent to the photoresistor.
    // That way, when we read the value from the other side of the photoresistor, we can accurately calculate a voltage drop.

    int currentValue; // used to store the value read from the photoresistor.

public:
    Photoresistor(int inputPin, int powerPin, const String& cloudName = "")
    : inputPin(inputPin), powerPin(powerPin), currentValue(42)
    {
        pinMode(inputPin, INPUT);  // Our photoresistor pin is input (reading the photoresistor)
        pinMode(powerPin, OUTPUT); // The pin powering the photoresistor is output (sending out consistent power)
    
        // Next, write the power of the photoresistor to be the maximum possible, so that we can use this for power.
        digitalWrite(powerPin, HIGH);
        
        // We are going to declare a Particle.variable() here so that we can access the value of the photoresistor from the cloud.
        if (cloudName.length() > 0)
            Particle.variable(cloudName, currentValue);
    }

    void update()
    {
        // check to see what the value of the photoresistor is and store it
        currentValue = analogRead(inputPin);
    }
};

class TemperatureSensor
{
    OneWire bus;
    DallasTemperature dallas;
    double currentValue;
    
public:
    TemperatureSensor(int dataPin, const String& cloudName = "")
    : bus(dataPin), dallas(&bus)
    {
        // publish the value to the particle cloud, if we have got a name if
        if (cloudName.length() > 0)
            Particle.variable(cloudName, currentValue);
    }
    
    void update()
    {
        dallas.requestTemperatures();
        currentValue = dallas.getTempCByIndex(0);
    }
};

Led led(D7, "led");
Photoresistor photo(A0, A5, "photo");
TemperatureSensor temp(D0, "temperature");

void loop()
{
    photo.update();
    temp.update();
    delay(200);
}
