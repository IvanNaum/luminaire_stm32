# Project

## Project Structure 

- [cmake](cmake/) - configs for building application
- [common](common/) - symbol link to common modules
- [Core](Core/) - source code
- [Drivers](Drivers/) - STM32 SDK, CMSIS, HAL, LL
- [openocd](openocd/) - configs for programming and debug board
- [vscode_template](vscode_template/) - templates for initializing project in VS code


## Initialization

1. Install [ARM toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) (use VPN)

    ``` shell
    sudo mv ./arm-gnu-toolchain-12.3.rel1-x86_64-arm-none-eabi /usr/local/share/arm-gnu-toolchain-12.3.rel1-x86_64-arm-none-eabi
    ```
    Include in your `.bashrc`:
    ``` shell
    export ARM_TOOLCHAIN_V12_DIR="/usr/local/share/arm-gnu-toolchain-12.3.rel1-x86_64-arm-none-eabi/bin"
    ```

1. Install [openocd](https://github.com/openocd-org/openocd)

    ``` shell
    git clone https://github.com/openocd-org/openocd
    cd openocd

    ./bootstrap
    ./configure
    make
    sudo make install
    ```

1. Copy vscode_templates to .vscode and edit absolute paths

    ``` shell
    cp -r ./vscode_templates ./.vscode
    ```

## Building

``` shell
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=./arm-none-eabi-gcc.cmake
cmake --build .
```

## VS Code Plugins

* [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
* [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
* [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
* [Cortex-Debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)
