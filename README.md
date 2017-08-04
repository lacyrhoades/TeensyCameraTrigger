Program 0 (most programs):
Note on low velocity: Focus all cameras
Note on high velocity: Fire all shutters
Note off low velocity: Unfire all cameras (remain focused)
Note off high velocity: Unfire and unfocus

Program 1:
Note on low velocity: Focus note number
Note on high velocity: Fire note number
Note off low velocity: Unfire note number (remain focused)
Note off high velocity: Unfire & unfocus note number

Using sendmidi on macOS

export DELAY=0.12
export FOCUS=1
sendmidi dev "Teensy" pc 0
sendmidi dev "Teensy" off 0 127
sendmidi dev "Teensy" pc 1
sleep $DELAY
sendmidi dev "Teensy" on 0 64
sleep $FOCUS
sendmidi dev "Teensy" on 0 127
sleep $DELAY
sendmidi dev "Teensy" off 0 64
sleep $DELAY
sendmidi dev "Teensy" on 0 127
sleep $DELAY
sendmidi dev "Teensy" off 0 64
sleep $DELAY
sendmidi dev "Teensy" on 0 127
sleep $DELAY
sendmidi dev "Teensy" off 0 64
sleep $DELAY
sendmidi dev "Teensy" on 0 127


sendmidi dev "Teensy" on 0 64
sleep 1
sendmidi dev "Teensy" on 0 127
sendmidi dev "Teensy" off 0 127
