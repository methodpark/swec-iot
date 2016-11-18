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

Led led(D7, "led");

void lightsHandler(const char *event, const char *data)
{
  if (String(data) == "on")
    led.set(true);
  else
    led.set(false);
}

void setup()
{
    Particle.subscribe("lights", lightsHandler, MY_DEVICES);
}
