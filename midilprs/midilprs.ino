#include <MIDI.h>

#include <SoftwareSerial.h>

#define MAX_NOTE 127

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
  mySerial.begin(31250);
  

  MIDI.begin(1);  // Initialize the MIDI library
  //flag=1;
}

void all_notes_off(){

  for(int i=0;i<MAX_NOTE;i++) {
    MIDI.sendNoteOn(i, 0, 1);
  }

}

void loop() {
 
  if(Serial.available()){
    

    op = Serial.parseInt();
    // Skip the comma
    Serial.read();
    // Read the second value after the comma
    pitch = Serial.parseInt();

    if(op==1){
      MIDI.sendNoteOn(pitch, 127, 1);
         
      digitalWrite(13, 1);   
      
      
    }
    if(op==0){
      
      MIDI.sendNoteOn(pitch, 0, 1);
    
      digitalWrite(13, 0);
       
    }

    if(op==-1){

      MIDI.sendStop();
      all_notes_off();

    }
   
    
    
  }

}

