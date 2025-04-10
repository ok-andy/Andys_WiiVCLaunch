# Andy's Wii VC Launch

A fork of Lynx64's Wii VC Launch because I wanted to have different default options lol

## Features

### Custom dialogs

- Select a display option (TV Only, TV and GamePad, etc.) with any controller
- Autolaunch into a specific display option bypassing all dialogs
  - Keep A pressed when launching a game to force open the Select a display option dialogs
  - Falls back to the GamePad screen if TV not connected

### Original built in dialogs

- Enables the GamePad sensor bar for built in dialogs
- Allow using a Pro Controller to Select a display option in the built in dialogs

### Video

- Set the resolution to 480p, 720p, 480i, or 576i (including 4:3 variants)
  - Can be set separately for Wii VC and Wii Mode

## Usage

Open the plugin config menu by pressing L, DPAD Down and Minus on the GamePad, Pro Controller or Classic Controller, or B, DPAD Down and Minus on a Wii Remote.

Press B on any controller to back out of the custom dialogs.

If custom dialogs are disabled:

- Autolaunch cannot be used
- Set resolution can still be used

"Preserve SYSCONF on Wii VC title launch" and "Permanent Wii Internet Settings" (Disables Wii Internet Connection Settings overwrite) are useful in combination with [Priiloader](https://github.com/DacoTaco/priiloader) or Wii homebrew that can change the Internet Connection settings. If you don't have Priiloader installed you don't need to worry about them and can leave them both on `false`.

## Building

For building you need:

- [wut](https://github.com/devkitPro/wut)
- [wups](https://github.com/wiiu-env/WiiUPluginSystem)
- [libnotifications](https://github.com/wiiu-env/libnotifications)
- [libmocha](https://github.com/wiiu-env/libmocha)

then run `make`

## Building using the Dockerfile

It's possible to use a docker image for building. This way you don't need anything installed on your host system other than Docker.

```
# Build docker image (only needed once)
docker build . -t wiivclaunch-builder

# make
docker run --rm -v ${PWD}:/project wiivclaunch-builder make

# make clean
docker run --rm -v ${PWD}:/project wiivclaunch-builder make clean
```
