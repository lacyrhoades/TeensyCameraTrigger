[Picture of MIDI to camera adapter thing]

## Usage as a midi device

* Use midi to control the cameras
* Differnt "program changes" are different behavior
* Device will reset / unfocus all cameras after 30 seconds of inactivity

## Program 0 (most programs):

* Note On (low velocity): Focus all cameras
* Note On (high velocity): Fire all shutters
* Note Off (low velocity): Release shutter button, all cameras (remain focused)
* Note Off (high velocity): Release shutter and unfocus, all cameras

## Program 1:

* Note On (low velocity): Focus note number
* Note On (high velocity): Fire note number
* Note Off (low velocity): Release shutter on note number (remain focused)
* Note Off (high velocity): Release shutter & unfocus note number

## Using sendmidi in Terminal on macOS

```
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
```