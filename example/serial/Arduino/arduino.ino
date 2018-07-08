/*
    Code for arduino for the serial test.
*/
int j=0;
void setup() {
    Serial.begin(115200);
    Serial1.begin(230400);
}

void loop() {
    if(Serial.available()){
        if(Serial.read()=='a'){
            for(int i=0;i<15;i++)
                Serial1.write(j++);
        }
    }
    
}


