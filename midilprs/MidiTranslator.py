import mido
import serial
import time

arduino = serial.Serial(port='COM10', baudrate=31250)


def write_arduino(x):
    print(x)
    arduino.write(bytes(x, 'utf-8'))
    arduino.flush()
    


# Set up the virtual MIDI port name
virtual_port_name = 'ArdMidi 0'

# Create an input port using the 'portmidi' backend
in_port = mido.open_input(virtual_port_name)#, backend='portmidi')

# Read MIDI messages from the virtual port
for message in in_port:
    #print(message)
    mes=str(message)
    if mes.find("note_on")>-1:
        print(1)
        note=mes.split("note=", 1)[1][0:3]
        print(note)
        write_arduino("1,"+note+",")
        
        
        
    if mes.find("note_off")>-1:
        print(0)
        note=mes.split("note=", 1)[1][0:3]
        print(note)
        write_arduino("0,"+note+",")
        time.sleep(0.1)
        

        
    