//
// Code for Particle Photon to use the HC-SR04 Ultrasonic Sensor
// Mostly I pulled the code out of the Particle HC_SR04.cpp file to customize it a little
//
int trigPin = D4;
int echoPin = D5;

int maxDist = 200;
int minDist = 0;

double distCm = 0.0;
double distIn = 0.0;

double getDistanceCM()
{
    sendTriggerPulse(trigPin);
    waitForEcho(echoPin, HIGH, 100);
    long startTime = micros();
    waitForEcho(echoPin, LOW, 100);
    long endTime = micros();
    long duration = endTime - startTime;
    double distance = duration / 29.0 / 2.0;
    if (distance < minDist || distance > maxDist)
    {
        return -1;
    }
    return distance;
}

double getDistanceInch()
{
    double distCM = getDistanceCM();
    if (distCM == -1)
    {
        return -1;
    }
    return (distCM / 2.5);
}

void sendTriggerPulse(int pin)
{
    digitalWrite(pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pin, LOW);
}

void waitForEcho(int pin, int value, long timeout)
{
    long giveupTime = millis() + timeout;
    while (digitalRead(pin) != value && millis() < giveupTime)
    {
    }
}

void setup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop()
{
    distCm = getDistanceCM();
    distIn = getDistanceInch();
    Particle.publish("Distance-CM", String(distCm));
    Particle.publish("Distance-IN", String(distIn));
    delay(1000);
}
