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
    uint8_t buffer[10];
    if(Serial1.readBytes(buffer, 10)==10)
    for(int i=0;i<10;i++){
        Serial.print(buffer[i]);
        Serial.print(" ");
    }
    Serial.println();
}


