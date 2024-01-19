# AVR Programmierung

=== "Windows"

    ### 1. Installation des Treibers
    Die Programmierung unter Windows benötigt die Installation [dieses Treibers](https://github.com/digistump/DigistumpArduino/releases/download/1.6.7/Digistump.Drivers.zip). Hier eine kurze Videoanleitung:


    <figure class="video_container">
    <video controls="true" allowfullscreen="true">
        <source src="../../assets/videos/win_install_driver.mp4" type="video/mp4">
    </video>
    </figure>

    ### 2. Installation Platformio
    Am einfachsten lässt sich der Microcontroller mit Hilfe von [Platformio](https://platformio.org/) unter Visual Studio Code programmieren. Hier eine kleine Videoanleitung:

    <figure class="video_container">
    <video controls="true" allowfullscreen="true">
        <source src="../../assets/videos/win_install_vscode_pio.mp4" type="video/mp4">
    </video>
    </figure>

    Wie im Video gezeigt, installiere bitte [Visual Studio Code](https://code.visualstudio.com/).
    In Visual Studio Code installierst du dann die Erweiterung `PlatformIO`.

    Bitte beachte dass die Installation der Erweiterung lange dauern kann und am Ende einene Neustart von VSCode erfordert.

=== "Linux"

    Installiere dir das Paket `platformio` um die Firmware kompilieren zu können.

    Als Entwicklungsumgebung bietet sich [VS Code](https://code.visualstudio.com/docs/setup/linux) an. 
    Es bietet mit dem `platformio` Plugin eine gute Integration, aber jeder andere Editor tut es auch.

    Eine Übersicht zu Programmierbeispielen und wie du sie ausführst findest du [hier](ProgExamples.de.md).