# Programming Examples

## Download

To install existing example programs on the board, you must have extracted [our source files](https://github.com/HaCraFu/assembly-kits/archive/refs/heads/main.zip). Approximately like this:

<figure class="video_container">
  <video controls="true" allowfullscreen="true">
    <source src="../../../assets/videos/extract.mp4" type="video/mp4">
  </video>
</figure>

## Opening

Then open the `firmware` folder in Visual Studio Code to be able to execute the following installation commands. You may only connect the board to the PC when the command prompts you with the text
```
> Please plug in the device (will time out in 60 seconds) ...
```
The whole thing then looks approximately like this:


<figure class="video_container">
  <video controls="true" allowfullscreen="true">
    <source src="../../../assets/videos/use_vscode.mp4" type="video/mp4">
  </video>
</figure>

!!! Examples
    === "Arrow"

        On the [Bau(m)satz](../../kits/baumsatz.md), this program shows a small arrow animation.

        Install with the command
        ```
        pio run -e arrow -t upload
        ```

        Modify the program in the file `firmware/src/arrow/main.cpp`

    === "Random"

        Makes one of the six LEDs light up randomly at startup. No guarantee of [uniform distribution](https://en.wikipedia.org/wiki/Continuous_uniform_distribution)!

        Install with the command
        ```
        pio run -e random -t upload
        ```

        Modify the program in the file `firmware/src/random/main.cpp`

    === "Random LED"

        Switches to a random LED after a short pause.

        Install with the command
        ```
        pio run -e random_led -t upload
        ```

        Modify the program in the file `firmware/src/random_led/main.cpp`

    === "Provisioning Bau(m)satz"

        The initial firmware. Turns on all LEDs one after another. Then switches between LED pairs every 8 seconds.

        Install with the command
        ```
        pio run -e provisioning_baumsatz_usb -t upload
        ```

        Modify the program in the file `firmware/src/provisioning_baumsatz/main.cpp`

    === "Provisioning Unicorn"

        The initial firmware. Turns on all LEDs one after another. Then follows an animation.

        Install with the command
        ```
        pio run -e provisioning_unicorn_usb -t upload
        ```

        Modify the program in the file `firmware/src/provisioning_unicorn/main.cpp`

    === "Keyboard"

        Example program for keyboard emulation.

        When you plug the board into the PC, it registers as a keyboard that types `Frohe Weihnachten wuenscht der HaCraFu!` every 5 seconds.
        This can be used to develop applications similar to the [Rubber Ducky](https://shop.hak5.org/products/usb-rubber-ducky).

        Install with the command
        ```
        pio run -e keyboard -t upload
        ```

        Modify the program in the file `firmware/src/keyboard/main.cpp`

    === "Touch dice"

        Example program for touch. When you touch the USB pins with a moist finger, the program randomly selects a different LED.

        Install with the command
        ```
        pio run -e touch_dice -t upload
        ```

        Modify the program in the file `firmware/src/touch_dice/main.cpp`
