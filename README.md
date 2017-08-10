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

## amidi on RaspberryPi

amidi -p hw:1 -S 'C0 00 C0 01 C0 00' # cancel all
amidi -p hw:1 -S 'C0 00 90 00 40' # focus all
amidi -p hw:1 -S 'C0 00 90 00 7F' # fire all
amidi -p hw:1 -S '80 00 40' # half-cancel

amidi -p hw:1 -S 'C0 00' # program 0
amidi -p hw:1 -S '90 00 40' # focus, note on, all cameras
sleep 1
amidi -p hw:1 -S '90 00 7F' # fire, note on, all cameras
sleep 0.6
amidi -p hw:1 -S '80 00 40' # note off, un-focus all
sleep 0.1
amidi -p hw:1 -S '90 00 7F' # fire, note on, all cameras
sleep 0.1
amidi -p hw:1 -S '80 00 7F' # note off, all cameras

amidi -p hw:1 -S 'C0 01' # program 1
amidi -p hw:1 -S '90 00 40' # note on, focus camera zero
amidi -p hw:1 -S '90 01 40'
amidi -p hw:1 -S '90 02 40'
amidi -p hw:1 -S '90 03 40'
sleep 0.2
amidi -p hw:1 -S '90 00 7F' # note on, fire camera zero
amidi -p hw:1 -S '80 00 7F' # note off, camera zero
sleep 0.2
amidi -p hw:1 -S '90 01 7F'
amidi -p hw:1 -S '80 01 7F'
sleep 0.2
amidi -p hw:1 -S '90 02 7F'
amidi -p hw:1 -S '80 02 7F'
sleep 0.2
amidi -p hw:1 -S '90 03 7F'
amidi -p hw:1 -S '80 03 7F'


amidi -p hw:1 -S 'C0 01 90 02 40'
amidi -p hw:1 -S '90 02 7F'
amidi -p hw:1 -S 'C0 01 90 03 40'
amidi -p hw:1 -S 'FF'

## Using sendmidi in Terminal on macOS

```

export FOCUS=1
export DELAY=0.2
sendmidi dev "Teensy" pc 0
sleep $DELAY
sendmidi dev "Teensy" pc 1
sleep $DELAY
sendmidi dev "Teensy" pc 0
sleep $DELAY
sendmidi dev "Teensy" on 0 64
sleep $FOCUS
sendmidi dev "Teensy" on 0 127
sleep $DELAY
sendmidi dev "Teensy" off 0 127
sleep $DELAY

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