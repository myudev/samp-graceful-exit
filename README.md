SAMP Graceful Exit - Don't get your data lost.
======
## What is this?
This plug-in provides you with a simple but powerful function - catch signals on Windows on Linux.

With this plug-in you're able to catch user signals sent to the process and interrupt on f.e. CTRL+C shutdowns allowing your to save your data before server shutdown.

Keep in mind that this plug-in can't catch every process shutdown as systems force the shutdown of a system in one or another way.

## Important notes
> On Windows you're able to catch controlled signals (closing the window, pressing ctrl+c) but keep in mind that we're only able to interupt the termination of the process for **10 seconds**.

> On Linux you're also able to catch controlled signals (closing the terminal, interrupts, termination requests) with one difference once a SIGKILL signal get's sent the process immediately exits.

## Installation
The installation is simple, just download the latest version from the GitHub Releases Page and install it like every other plug-in.

## Usage
The plug-in just provides 1 callback and 2 functions there's not much to tell about them other then one example:
```c

public OnGameModeInit()
{
  SetCatchExit(true); // not setting this will make the plug-in effectively useless.
  return 1;
}

new bool:stuff_saved;
forward SaveUserData();
public SaveUserData()
{
  stuff_saved = true;
  SetCatchExit(false); // allow the program to exit safely now!
  //ExitProcess(); // or exit manually!
  printf("Saved user data!");
}

public OnUngracefulExit(ExitFlags:reason)
{
  if(reason & EXIT_USER)
  {
    if(reason & EXIT_CTRLC)
      printf("Press CTRL-C again if user data has been saved.");
    else
      printf("Wait for user data to be saved till exit.");
      
    if(!stuff_saved)	SetTimer("SaveUserData", 2500, 0); // simulate delay
  }

  return true;
}
```
