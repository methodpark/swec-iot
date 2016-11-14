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

void loop()
{
    led.toggle();
    delay(300);
}
