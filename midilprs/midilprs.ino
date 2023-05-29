#include <MIDI.h>

#include <SoftwareSerial.h>
   
using Transport = MIDI_NAMESPACE::SerialMIDI<SoftwareSerial>;
int rxPin = 8;
int txPin = 9;

SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);
Transport serialMIDI(mySerial);
MIDI_NAMESPACE::MidiInterface<Transport> MIDI((Transport&)serialMIDI);




int op=-1;
int pitch = -100;  // Variable to store the MIDI pitch value

void setup() {
  Serial.begin(31250);  // Set the baud rate to match the Serial monitor
  

  MIDI.begin(1);  // Initialize the MIDI library
  //flag=1;
}

void loop() {
 
  if(Serial.available()){
    
    /*int bytesRead = Serial.readBytesUntil('\n', buffer, bufferSize);
    buffer[bytesRead] = '\0';  // Null-terminate the buffer

    // Parse the values from the buffer
    char* token = strtok(buffer, ",");
    for (int i = 0; i < 2; i++) {
      if (token != NULL) {
        values[i] = atoi(token);
        token = strtok(NULL, ",");
      } 
    }
    op=values[0];
    pitch=values[1];
    */
    //Serial.println(op);
    //Serial.println(pitch);
    op = Serial.parseInt();
    // Skip the comma
    Serial.read();
    // Read the second value after the comma
    pitch = Serial.parseInt();

    if(op==1){
      MIDI.sendNoteOn(pitch, 127, 1);
      
      //Serial.println("on");
      //Serial.println(pitch);
      
    }
    if(op==0){
      
     
      MIDI.sendNoteOn(pitch, 0, 1);
      /*delay(1000);
      MIDI.sendNoteOn(pitch, 0, 1);
      delay(1);
      MIDI.sendNoteOn(pitch, 0, 1);*/
      /*digitalWrite(13, 1);
      digitalWrite(13, 0);
      */
      
     

      //Serial.println("off");
      //Serial.println(pitch);
    }
   
    
  }
 
  

}
