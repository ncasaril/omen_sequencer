# omen_sequencer
Colour setup and control for HP Omen Sequencer keyboard under Linux

## Prerequisites

```
sudo apt install build-essential libhidapi-hidraw0 libhidapi-dev
```

## Build and Install

```
make
sudo make install
```

## Usage

```
omen_coloursetup [-v] [-L] <mode>
  -v verbose
  -L List available modes
```

## Set colours at boot/resume from sleep

Edit provided _lib_systemd_system_sleep.sh and place in /lib/systemd/system/sleep.sh

## Add new colour modes

Use instructions from uwbrply (https://github.com/JohnDMcMaster/usbrply) to capture packets sent to keyboard:

Sample workflow for capturing Windows VM traffic from Linux host and replaying traffic in Python:
* Example: program a Xilinx dev board under Linux without knowing anything about the JTAG adapter USB protocol
* Linux: Install Wireshark
* Linux: Enable usbmon so Wireshark can capture USB (sudo modprobe usbmon, see http://wiki.wireshark.org/CaptureSetup/USB)
* Linux: Boot Windows VM (ie through VMWare)
* Linux: Start Wireshark. Make sure you have USB permissions (ie you may need to sudo)
* Connect USB device to computer
* Linux: use lsusb to determine which device bus is on. Try to choose a bus (port) with no other devices
* Linux: start catpure on bus from above
* Linux: attach USB device to Windows guest
* Windows: start your application, do your thing, etc to generate packets
* Linux: stop capture
* Linux: save capture. Save in pcap-ng format (either should work)
* Export packet dissections, as plain text, enable Bytes, disable Summary and Details
* Use setup_to_h.sh to make an h file of the wireshark dump
* edit colour_setups.h and add the new mode from the created h file following the pattern
* edit colour_setup.c to allow use of the new setup
