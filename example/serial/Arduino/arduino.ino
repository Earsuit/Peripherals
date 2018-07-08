/*
    Code for arduino for the serial test.
*/

void setup() {
    Serial.begin(115200);
    Serial1.begin(115200);
}

void loop() {
    if(Serial.available()){
        if(Serial.read()=='a'){
            for(int i=0;i<15;i++)
                Serial1.write(i);
        }
    }
    
}


