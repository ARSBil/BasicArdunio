int a=5;
int b=7;

void setup() {
 Serial.begin(9600);

}

void loop() {
   if (a>b) {
    Serial.println("if bloğu içine girildiği."); 
   } else {
    Serial.println("if bloğu çalışmadı.");
   }
    while(1);
}
