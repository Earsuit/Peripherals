/*
    Code for arduino for the serial test.
*/

void setup() {
    Serial.begin(115200);
    Serial1.begin(115200);
}

void loop() {
    for(int i=0;i<5;i++)
        Serial1.write(i);
}


