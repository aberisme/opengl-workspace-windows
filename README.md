# OpenGL Portable Workspace for Windows

A ready-to-use C++ OpenGL and freeglut workspace for 64-bit Windows. The repository includes a portable MSYS2 UCRT64 toolchain, so students do not need to install MinGW separately.

## Video Tutorial
[![Code Demo](https://img.youtube.com/vi/pSaMlxv6AZo/0.jpg)](https://youtu.be/pSaMlxv6AZo)

## Requirements

- Windows 10 or Windows 11 (64-bit)
- [Visual Studio Code](https://code.visualstudio.com/)
- The **C/C++** extension by Microsoft (`ms-vscode.cpptools`)
- Git, or GitHub Desktop, for cloning the repository

## Get the workspace

Clone the repository:

```powershell
git clone https://github.com/aberisme/opengl-workspace-windows.git
cd opengl-workspace-windows
code .
```

Alternatively, clone it with GitHub Desktop and select **Open in Visual Studio Code**.

> Always open the repository folder itself in VS Code. Do not open only a `.cpp` file or the `.vscode` folder.

## Run a program

Each `.cpp` file is treated as an independent program and should contain its own `main()` function.

1. Open the `.cpp` file you want to run.
2. Click inside its editor tab so it becomes the active file.
3. Save it with `Ctrl+S`.
4. Press `Ctrl+Shift+B` to build the active file.
5. Press `F5` to build and debug, or `Ctrl+F5` to run without debugging.

For example, opening `triangle.cpp` builds `triangle.exe` beside the source file.

You can also open the Command Palette with `Ctrl+Shift+P`, select **Tasks: Run Task**, and choose **Build and Run Active OpenGL File**.

## Expected repository structure

```text
opengl-workspace-windows/
├── .vscode/
│   ├── c_cpp_properties.json
│   ├── launch.json
│   └── tasks.json
├── toolchain/
│   └── ucrt64/
│       ├── bin/
│       ├── include/
│       ├── lib/
│       └── libexec/
├── main.cpp
└── README.md
```

Do not move or rename `toolchain/ucrt64`; the VS Code configuration uses that exact relative path.

## Source-code header

For code that can also be used on macOS, use this conditional header:

```cpp
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
```

## Troubleshooting

### The build task cannot find `g++.exe`

Confirm that this file exists:

```text
toolchain\ucrt64\bin\g++.exe
```

Also make sure the repository root—not its parent folder—is open in VS Code.

### The program builds but no window appears

Open the Windows taskbar and check whether the OpenGL window opened behind VS Code. This program displays its output in a separate graphics window, not as text in the terminal.

### A DLL is missing

Confirm that `toolchain\ucrt64\bin\libfreeglut.dll` exists. Run the program through the provided VS Code task so its temporary `PATH` includes the bundled DLLs.

### The Run Code button fails

The **Run Code** button usually belongs to the Code Runner extension and does not use this repository's OpenGL linker settings. Use `Ctrl+Shift+B`, `F5`, `Ctrl+F5`, or **Tasks: Run Task**.

### Multiple source files belong to one program

The active-file task compiles only the currently open `.cpp` file. For a program composed of several source files, use a dedicated build task or CMake.

## Platform note

The bundled UCRT64 compiler and `.exe` files run only on 64-bit Windows. macOS users should clone the separate macOS repository.

