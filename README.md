# Intense Scrap

Intense Scrap is a portable Spotify music player built around an ESP32 and a small TFT display.

It is designed to show the currently playing track and provide simple physical controls for previous, play/pause, and next.

## Project files

- `cad.scad` — OpenSCAD enclosure design
- `board.kicad_pcb` — KiCad PCB design
- `firmware/intense_scrap.ino` — Arduino/ESP32 firmware starter
- `bom.csv` — project bill of materials

## Firmware

The firmware uses the planned GPIO mapping for the TFT and three buttons. It provides the display/button control foundation and Spotify Web API calls for previous, play/pause, and next.

Wi-Fi credentials and the Spotify access token are placeholders and must be configured locally. **Do not commit real credentials or tokens.**

Arduino libraries used:

- Adafruit GFX Library
- Adafruit ST7735 and ST7789 Library

## Design

The enclosure uses a light, translucent CAD-style design so the electronics can be subtly visible through the case while remaining enclosed.

The device uses three physical buttons instead of a rotary encoder. The TFT is a display, not a touchscreen.

## Goal

Build a small, portable Spotify controller/display while learning CAD, PCB design, ESP32 hardware, buttons, displays, and electronics.

## What We Are Building

### Intense Scrap — Concept

![Intense Scrap concept board](Intense%20Scrap%20Music%20Player%20Concept%20Board.png)

### Product Design

![Intense Scrap product design](Screenshot%20%28212%29.png)

### Design / Build Reference

![Intense Scrap build reference](Screenshot%20%28213%29.png)

## Fabrication status

Gerber/drill outputs are intentionally not included yet because the current PCB is still a prototype and the exact production footprints for the ESP32 module, USB-C, regulator, charging circuit, and audio section still need final verification.

Once the PCB passes ERC/DRC and the exact production components are locked, Gerbers and drill files should be exported from KiCad and added to the repository.
