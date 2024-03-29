# Programmierbeispiele

## Download

Um vorhandene Beispielprogramme auf die Platine zu installieren musst du [unsere Quelldateien](https://github.com/HaCraFu/assembly-kits/archive/refs/heads/main.zip) entpackt haben. Ungefähr so:

<figure class="video_container">
  <video controls="true" allowfullscreen="true">
    <source src="../../../assets/videos/extract.mp4" type="video/mp4">
  </video>
</figure>

## Öffnen

Öffne dann in Visual Studio Code Ordner `firmware` um die folgenden Installationsbefehle ausführen zu können. Du darfst die Platine erst mit dem PC verbinden, wenn dich der Befehl mit dem Text
```
> Please plug in the device (will time out in 60 seconds) ...
```
dazu auffordert. Das ganze sieht dann ungefähr so aus:


<figure class="video_container">
  <video controls="true" allowfullscreen="true">
    <source src="../../../assets/videos/use_vscode.mp4" type="video/mp4">
  </video>
</figure>

!!! Beispiele
    === "Arrow"

        Auf dem [Bau(m)satz](../../../kits/baumsatz) zeigt dieses Programm eine kleine Pfeilanimation.

        Installieren mit dem Befehl 
        ```
        pio run -e arrow -t upload
        ```

        Verändern des Programms in der Datei `firmware/src/arrow/main.cpp`

    === "Random"

        Lässt zufällig eine der sechs LED beim Start leuchten. Keine Gewähr für [Gleichverteilung](https://de.wikipedia.org/wiki/Stetige_Gleichverteilung)!

        Installieren mit dem Befehl 
        ```
        pio run -e random -t upload
        ```

        Verändern des Programms in der Datei `firmware/src/random/main.cpp`

    === "Random LED"

        Wechselt nach kurzer Pause zu einer zufälligen LED.

        Installieren mit dem Befehl 
        ```
        pio run -e random_led -t upload
        ```

        Verändern des Programms in der Datei `firmware/src/random_led/main.cpp`

    === "Provisioning Bau(m)satz"

        Die initiale Firmware. Schaltet nacheinander alle LEDs an. Wechselt danach alle 8 Sekunden zwischen LED-Paaren weiter.

        Installieren mit dem Befehl 
        ```
        pio run -e provisioning_baumsatz_usb -t upload
        ```

        Verändern des Programms in der Datei `firmware/src/provisioning_baumsatz/main.cpp`

    === "Provisioning Unicorn"

        Die initiale Firmware. Schaltet nacheinander alle LEDs an. Danach folgt eine Animation.

        Installieren mit dem Befehl 
        ```
        pio run -e provisioning_unicorn_usb -t upload
        ```

        Verändern des Programms in der Datei `firmware/src/provisioning_unicorn/main.cpp`

    === "Keyboard"

        Beispielprogramm für Keyboardemulation. 

        Steck man die Platine in den PC, meldet sie sich als Keyboard an, welches alle 5 Sekunden `Frohe Weihnachten wuenscht der HaCraFu!` tippt.
        Hiermit lassen sich Anwendungen ähnlich zum [Rubber Ducky](https://shop.hak5.org/products/usb-rubber-ducky) entwickeln.

        Installieren mit dem Befehl 
        ```
        pio run -e keyboard -t upload
        ```

        Verändern des Programms in der Datei `firmware/src/keyboard/main.cpp`

    === "Touch dice"

        Beispielprogramm für Touch. Berührt man die USB-Pins mit dem feuchten Finger würfelt das Programm eine andere LED aus.

        Installieren mit dem Befehl 
        ```
        pio run -e touch_dice -t upload
        ```

        Verändern des Programms in der Datei `firmware/src/touch_dice/main.cpp`
