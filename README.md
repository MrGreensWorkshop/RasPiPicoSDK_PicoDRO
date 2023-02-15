## PicoDRO

[<img src="https://img.shields.io/github/issues/MrGreensWorkshop/RasPiPicoSDK_PicoDRO" alt="GitHub issues" data-no-image-viewer>](https://github.com/MrGreensWorkshop/RasPiPicoSDK_PicoDRO/issues)
[<img src="https://img.shields.io/github/forks/MrGreensWorkshop/RasPiPicoSDK_PicoDRO" alt="GitHub forks" data-no-image-viewer>](https://github.com/MrGreensWorkshop/RasPiPicoSDK_PicoDRO/blob/main/README.md#readme)
[<img src="https://img.shields.io/github/stars/MrGreensWorkshop/RasPiPicoSDK_PicoDRO" alt="GitHub stars" data-no-image-viewer>](https://github.com/MrGreensWorkshop/RasPiPicoSDK_PicoDRO/blob/main/README.md#readme)
[<img src="https://img.shields.io/github/license/MrGreensWorkshop/RasPiPicoSDK_PicoDRO" alt="GitHub license" data-no-image-viewer>](https://github.com/MrGreensWorkshop/RasPiPicoSDK_PicoDRO/blob/main/LICENSE.txt)
[<img src="https://shields.io/badge/Github%20Sponsors-Support%20me-blue?logo=GitHub+Sponsors" alt="Support me on GitHub Sponsors" data-no-image-viewer>](https://github.com/sponsors/MrGreensWorkshop "Support me on GitHub Sponsors")
[<img src="https://shields.io/badge/Patreon-Support%20me-blue?logo=Patreon" alt="Support me on Patreon" data-no-image-viewer>](https://patreon.com/MrGreensWorkshop "Support me on Patreon")
[<img src="https://shields.io/badge/Ko--fi-Tip%20me-blue?logo=kofi" alt="Tip me via Ko-fi" data-no-image-viewer>](https://ko-fi.com/MrGreensWorkshop "Tip me via Ko-fi")

---

[<img src="/docs/video_pic.jpg" max-height="250" alt="DIY digital readout with Linear scales using Raspberry Pi Pico">](https://youtu.be/lGm3rTDp7nE)

### Introduction

You can make your own digital readout with Linear scales / encoders using Raspberry Pi Pico. Only linear scales with RS-422 output are currently supported. It is compatible with TouchDRO App V3 via USB.

Thank you for considering [supporting my work!](#you-can-support-my-work)

#### Background

I was looking to add the DRO feature to my small milling machine. I wanted to use junky but good-condition parts to support the SDGs. I found a few linear scales at an online auction and bought them. Then I found the pinouts as I explained in [this video](https://youtu.be/LyS_wd5C0y0).

### Features

- 3 axis support (X,Y,Z)
- Adjustable read interval
- Dynamic data refresh rate
- Adjustable data refresh rate

### Compilation

1. Clone the repo as shown below, or [download latest release](https://github.com/MrGreensWorkshop/RasPiPicoSDK_PicoDRO/releases/latest).

    ```shell
    git clone https://github.com/MrGreensWorkshop/RasPiPicoSDK_PicoDRO.git
    ```
1. Please make sure you are using the [Pico SDK v1.5.0](https://github.com/raspberrypi/pico-sdk/releases/tag/1.5.0) or later, because the implementations described below are necessary.
    - **Disabling DTR check for USB CDC**, As we are going to use TouchDro App, we need to disable the DTR check for the USB CDC connection.
    - **Setting as self-powered USB device**, Since the circuit is designed as a self-powered USB device, to tell the USB host that we are not draining power from it, we need to set the attribute called bmAttributes in the USB configuration descriptor.
1. Open the project in VS Code because it adds SDK to the environment string. (Check the [.vscode/settings.json](https://github.com/MrGreensWorkshop/RasPiPicoSDK_PicoDRO/blob/main/.vscode/settings.json) file for details.)
    - Or add PICO_SDK_PATH to your environment string. 
1. Compile using build.sh 
    ```shell
    chmod +x build.sh
    ./build.sh
    ```
    - Or run
    ```shell
    cmake -B build -S . && make -j4 -C build
    ```
    
### Running

1. Make sure you watch the video at the top of the page.
2. Build the circuit below.

<img src="/docs/PicoDroCircuitDiagram.jpg" max-height="300" alt="DIY digital readout with Linear scales using Raspberry Pi Pico">

3. Get the binary
    - You can compile the project and get the binary as explained above.
    - Or you can use precompiled binary files from the [latest release](https://github.com/MrGreensWorkshop/RasPiPicoSDK_PicoDRO/releases/latest), download the "binary.zip" and unzip.
1. Put the Raspberry Pi Pico into bootloader mode by pushing the bootsel button while plugging it into your computer.
1. Copy the `build/PicoDRO.uf2` file to the Raspberry Pi Pico either by dragging and dropping or using the `cp` command as shown below.

    | Linux | macOS |
    | :---- | ----- |
    | `cp build/PicoDRO.uf2 /media/<user>/RPI-RP2` | `cp build/PicoDRO.uf2 /Volumes/RPI-RP2` |
1. TouchDRO App V3 or higher version is required to use via USB, but it has not been released yet. But you can get the app by entering the Android test program. For details, please check the [official TouchDRO website](https://www.touchdro.com/resources/info/touchdro-v3.html#accessToBetaTesting). (Android 5.0 or higher is required.)
1. Download and Open the App.
1. To set USB as the default interface, please set `Settings > Use USB Connection` and set `USB Baud Rate` to `115200`.
1. To set resolution to 1.00 microns, please open `Settings > X Axis Settings > Resolution` and enter `25400` to set encoder steps per inch.

### Documentation

Check out the video at the top of the page.

### Credits

I want to thank all projects that gave me an opportunity to make this project possible. Please consider to support these projects too.

- [QuadratureDecoder](https://github.com/adamgreen/QuadratureDecoder) This is a library that counts quadrature encoder signal transitions in the background using the RP2040's PIO and DMA hardware.
- [TouchDRO Application](https://www.touchdro.com/resources/dro-manual/features.html) is a free Android application that provides all standard DRO features combined with easy to read high-resolution multi-touch display and superior computing power offered by modern phones and tablets. It is also ad-free.

### You Can Support My Work

Creating projects like this takes a great amount of time. Much appreciated if you consider supporting me so that I can continue projects like this and creating new contents for everyone.

- You can support me on [GitHub Sponsors](https://github.com/sponsors/MrGreensWorkshop "Support me on GitHub Sponsors") (monthly or one time)
- You can be one of my patrons on [Patreon](https://patreon.com/MrGreensWorkshop "Be my Patron") (monthly)
- You can tip me via [Ko-fi](https://ko-fi.com/MrGreensWorkshop "Tip Me via Ko-fi") (one time)

### Contribute

Pull Requests are welcome. Please check the instructions in the Issues and Pull Request templates.
<!--
### Contributors

Thank you for your contributions!
-->
### License

As it says in the [Apache License 2.0](https://github.com/MrGreensWorkshop/RasPiPicoSDK_PicoDRO/blob/main/LICENSE.txt), you can use my code anywhere as long as you include the license file and copyright notice. Also, state if you make any changes.

`Copyright (c) 2022 Mr. Green's Workshop https://www.MrGreensWorkshop.com`

Please add link to my page so I can get credit for my work.

Thank you!

### Other Licenses

This project incorporates libraries written below. Without these libraries, I couldn't make this project possible.

| Library                              | file(s) |
| :----------------------------------- | ------- |
| [ QuadratureDecoder](https://github.com/adamgreen/QuadratureDecoder), Copyright 2021 Adam Green (https://github.com/adamgreen/). QuadratureDecoder is distributed under the terms of the Apache License Version 2.0. | [Qdec](https://github.com/MrGreensWorkshop/RasPiPicoSDK_PicoDRO/tree/cf4ea2f01e0efe79339fd23c5473e978ff1312fd/src/qdec) |
