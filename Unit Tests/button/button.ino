int buttonPin = 13;
bool buttonState = false;
void setup()
{
    pinMode(buttonPin, INPUT);
    Serial.begin(115200);
}

void loop()
{
    buttonState = digitalRead(buttonPin);
    Serial.println(buttonState);
}
