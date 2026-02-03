![Pickerlock Logo](./repo_assets/logo.png)
#### A simple lock picking game made for [20 Second Game Jam 2025](https://itch.io/jam/20-second-game-jam-2025).

[See the itch.io page.](https://abes400.itch.io/pickerlock)  
Made with [Raylib 5.5](https://www.raylib.com/) using C++.  
Distributed under MIT License.

**[Jump to Build Instructions](#build-instructions)**  
**[Jump to Building Installers](#building-installers)**

<hr>

Main Menu             |  Gameplay
:-------------------------:|:-------------------------:
![Main Menu](./repo_assets/mainmenu.png)  |  ![Gameplay](./repo_assets/gameplay.png)

<hr>

## About the Game
You don't know how and when you decided to do so, but somehow, you found yourself enrolled in a lock picking contest. No prize, no praise, just 20 seconds  and an opportuity to show off your speed. There is one simple rule: NO MISTAKES! Otherwise, you're out.

### Controls
- **Arrow Keys:** Pick the locks  
- **Mouse:** Interact with menus

### 3 Difficulty Modes
- **Easy:** Each lock opens with **3** moves.
- **Medium:** Each lock opens with **4** moves.
- **Hard:** Each lock opens with **5** moves.

<br>

## Credits
Programming and Visuals - **Abes400**  
Menu Music - **"Safe At Home"** by **[Marcelo Fernández](https://www.marcelofernandezmusic.com/)**  (Licensed under [CC-BY 4.0](https://creativecommons.org/licenses/by/4.0/))  
In-game Music: -  **"A Journey Awaits"** by **[Pierre Bondoerffer](https://opengameart.org/users/pbondoer)**

<br>

## Build Instructions
**NOTE**: From now on, the toppermost directory of this repository will be referred to as the ***Repo Directory***. As you clone this repository, this directory will probably be named as **Pickerlock**. The sub contents of **Repo Directory** should be as follows:  
```
Repo_Directory\
├─ project\
├─ screenshots\
├─ .gitignore
├─ LICENSE
├─ Makefile
└─ README.md
```

### Windows (x64)
- #### Prerequisites for Windows
    - **MSYS2** with MINGW64 -- *[Download From Here](https://www.msys2.org/) if not installed*
    - **GCC** for MINGW64 -- *Run `pacman -S mingw-w64-x86_64-gcc` on **MSYS2 Terminal** if not installed*
    - **Make** for MINGW64 -- *Run `pacman -S make` on **MSYS2 Terminal** if not installed*

- #### Building for Windows
    On MSYS2 **MINGW64** Bash:  
    ```
    # Go to the Repo Directory
    cd /path/to/the/Repo_Directory

    # Compile the source code and copy the assets
    make
    ```
    On success, you should see the **output** folder containing the **Standalone Executable** and the **Assets** at `Repo_Directory\dist\windows_x64`.

<br>

### macOS (Universal)
- #### Prerequisites for macOS
    - **Xcode Command Line Tools**  -- *Run `xcode-select --install` on **Terminal** if not installed*

- #### Building for macOS
    On Terminal:
    ```
    # Go to the Repo Directory
    cd /path/to/the/Repo_Directory

    # Compile the source code and pack the Application Bundle
    make osx
    ```
    On success, you should see the **Universal Standalone Application Bundle** at `Repo_Directory/dist/macosx_universal`.

<br>

## Building Installers

### Windows (x64)
- #### Prerequisites for Windows
    - **NullSoft Scriptable Install System (NSIS)** -- *[Download From Here](https://nsis.sourceforge.io/Download)*

- #### Building Installer for Windows
    - Open **NSIS**
    - Select **Compile NSI scripts**
    - Drag & drop the **[Windows Installer Script](./project/appres/win/windows_installer.nsi)** to the ***MakeNSISW*** window.
    - On success, you should see the ***Installer executable*** at `Repo_Directory\dist\windows_x64`.

<br>

### macOS (Universal)
- #### Prerequisites for macOS
    - **create-dmg Command Line Tool**  -- *Run `brew install create-dmg` on **Terminal** if not installed (Homebrew required)*

- #### Building Installer for macOS
    On Terminal:
    ```
    # Go to the Repo Directory
    cd /path/to/the/Repo_Directory

    # Create the .dmg file with create-dmg
    make dmg
    ```
    On success, you should see the **Installer Disk Image** at `Repo_Directory/dist/macosx_universal`.

<br>

### Clear the `dist` directory
```
make clear
```
