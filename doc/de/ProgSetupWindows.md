# Einrichtung der Programmierumgebung unter Windows

## 1. Installation des Treibers
Die Programmierung unter Windows benötigt die Installation [dieses Treibers](https://github.com/digistump/DigistumpArduino/releases/download/1.6.7/Digistump.Drivers.zip).

![Digistump Windows Treiber](../img/setup_windows_driver.png)

## 2. Installation Platformio
Am einfachsten lässt sich der Microcontroller mit Hilfe von [Platformio](https://platformio.org/) programmieren.

Dazu installiere bitte [Python](https://www.python.org/downloads/windows/). Und setze das Häkchen um Python im PATH zu registrieren:
![Python Windows Setup](../img/setup_windows_python.png)

Jetzt öffne eine Konsole (z.B. cmd.exe oder Powershell oder Windows Terminal) und installiere Platformio mit dem Befehl
```
pip install platformio
```
![pip install platformio](../img/setup_python_platformio.png)
