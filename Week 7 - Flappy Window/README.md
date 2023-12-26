# Basic Timer

Week 7 of PAW. My attempt at creating a game using the Win32 API. The positions are of the windows are updated every `UPDATE_TIME` seconds in which a WM_TIMER message is sent to the message queue.

## Compile
The project can be compiled using:
```cl /Zi main.cpp user32.lib Gdi32.lib```
THe `/Zi` is used for debugging purposes.