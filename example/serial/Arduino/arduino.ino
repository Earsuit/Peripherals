/*
    Code for arduino for the serial test.
*/

void setup() {
    Serial.begin(115200);
    Serial1.begin(115200);
}

void loop() {
    if(Serial1.available()){
        uint8_t a = Serial1.read();
        Serial.println(a,HEX);
    }
    Serial1.write(0x12);
}


