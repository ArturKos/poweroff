# PowerOFF

![C++ Builder](https://img.shields.io/badge/C%2B%2B%20Builder-6.0-00599C?style=flat&logo=cplusplus&logoColor=white)
![Platform](https://img.shields.io/badge/platform-Windows-0078D6?style=flat&logo=windows&logoColor=white)
![VCL](https://img.shields.io/badge/framework-VCL-blueviolet?style=flat)
![License](https://img.shields.io/badge/license-MIT-blue?style=flat)

Windows shutdown scheduler with system tray integration. Schedule an automatic shutdown, restart, or logoff at a precise time using a simple time picker interface.

## Features

- **Three shutdown modes** -- choose between power off (`EWX_POWEROFF | EWX_SHUTDOWN`), restart (`EWX_REBOOT`), or logoff (`EWX_LOGOFF`), each with the `EWX_FORCE` flag for immediate action
- **Precision time picker** -- select the target hour, minute, and second via three combo box dropdowns; defaults to the current system time on launch
- **Real-time clock display** -- a status bar continuously shows the current system time, updated every timer tick
- **System tray integration** -- runs in the background via a `TTrayIcon` component, staying out of the way until the scheduled time arrives
- **Windows privilege escalation** -- automatically acquires the `SE_SHUTDOWN_NAME` privilege via `AdjustTokenPrivileges` on Windows NT/2000/XP, enabling clean shutdowns even for non-elevated processes
- **NT and 9x compatibility** -- detects the Windows platform version via `GetVersionEx` and applies privilege escalation only on NT-based systems, falling back to direct `ExitWindowsEx` on Windows 9x
- **Non-resizable window** -- the form intercepts `FormCanResize` to maintain a fixed layout
- **Enable/disable toggle** -- a checkbox arms or disarms the scheduled action, allowing the user to set the time before activating

## Dependencies

| Dependency | Purpose |
|---|---|
| C++ Builder 6.0 | IDE and compiler |
| VCL (Visual Component Library) | GUI framework |
| `trayicon` component | System tray icon integration |
| Windows API (`ExitWindowsEx`, `AdjustTokenPrivileges`) | System shutdown and privilege management |

## Build Instructions

1. Open `PowerOFF.bpr` in Borland C++ Builder 6.0.
2. Ensure the `trayicon` third-party component is installed in the IDE.
3. Build the project (Ctrl+F9) or run directly (F9).

## Project Structure

```
poweroff/
  PowerOFF.bpr       # C++ Builder project file
  PowerOFF.cpp       # WinMain entry point -- initializes the application
  PowerOFF.res       # Compiled resource file
  main.cpp           # Main form -- timer logic, privilege escalation, shutdown dispatch
  main.h             # Main form header -- TForm1 class declaration
  main.dfm           # Main form layout (combo boxes, radio buttons, checkbox, tray icon)
  ALBERT.ICO         # Application icon
```

## How It Works

1. On launch, the time picker defaults to the current system time.
2. The user selects the desired shutdown/restart/logoff time and checks the "Enable" checkbox.
3. A `TTimer` fires every second, comparing the current time against the target.
4. When the times match, `SystemRestart()` is called:
   - On NT-based Windows, it opens the process token, enables `SE_SHUTDOWN_NAME`, and calls `ExitWindowsEx`.
   - On Windows 9x, it calls `ExitWindowsEx` directly.

## Screenshot

![image](https://user-images.githubusercontent.com/17749811/152384771-549bd59e-eb5f-4874-8035-46b5dc608a3d.png)
