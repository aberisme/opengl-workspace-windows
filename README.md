# Portable C++ OpenGL/GLUT Workspace

This repository provides a beginner-friendly C++ OpenGL workspace for Visual Studio Code. On Windows 10/11, the repository can include a portable MSYS2 UCRT64 compiler and freeglut so students do not need to install MSYS2 separately.

The sample program opens a GLUT window titled **simple** and displays a filled white square on a black background.

## Platform support

| Platform | Current support | Additional requirement |
| --- | --- | --- |
| Windows 10/11, 64-bit | Portable workspace | Visual Studio Code and the Microsoft C/C++ extension |
| macOS on Apple Silicon | Source code supported, but not the bundled Windows toolchain | Xcode Command Line Tools and a macOS-specific build configuration |
| macOS on Intel | Source code supported, but not the bundled Windows toolchain | Xcode Command Line Tools and a macOS-specific build configuration |
| Linux | Source code supported, but not the bundled Windows toolchain | GCC, OpenGL development libraries, and freeglut |

> Cloning this repository does **not** make the bundled Windows compiler run on macOS. Files such as `g++.exe`, `gdb.exe`, and `libfreeglut.dll` are Windows binaries. Apple Silicon Macs must compile the same source code using Apple Clang and the macOS OpenGL and GLUT frameworks.

## Repository structure

```text
OpenGL-Portable/
├── .vscode/
│   ├── tasks.json
│   ├── launch.json
│   └── c_cpp_properties.json
├── toolchain/
│   └── ucrt64/
│       ├── bin/
│       ├── etc/
│       ├── include/
│       ├── lib/
│       ├── share/
│       └── x86_64-w64-mingw32/
├── main.cpp
└── README.md
```

The `.vscode` folder contains the Visual Studio Code build, IntelliSense, and debugging configuration. The Windows configuration uses paths relative to `${workspaceFolder}`, allowing the repository to be extracted into any normal user folder.

## Required VS Code extension

Install **C/C++ by Microsoft**:

1. Open Visual Studio Code.
2. Press `Ctrl+Shift+X` on Windows or `Command+Shift+X` on macOS.
3. Search for `C/C++`.
4. Install the extension published by Microsoft.

Extension identifier:

```text
ms-vscode.cpptools
```
<img width="1209" height="357" alt="Screenshot 2026-09-08 140927" src="https://github.com/user-attachments/assets/7644b892-1b5c-4c9d-be42-8508643e293a" />

# Windows 10/11 instructions

## 1. Download or clone the repository

Using Git:

```powershell
git clone <repository-url>
cd <repository-folder>
```

Replace the placeholders with the repository's actual URL and folder name.

Alternatively, select **Code → Download ZIP** on GitHub and extract the ZIP. Do not run the project from inside the compressed ZIP.

## 2. Open the correct folder

In Visual Studio Code, select **File → Open Folder** and open the repository root—the folder containing `main.cpp`, `.vscode`, and `toolchain`.

If the repository does not yet contain a source file, create `main.cpp` in the repository root beside `README.md`. Do not place it inside `.vscode` or `toolchain`.

## 3. Verify the portable compiler

Open **Terminal → New Terminal** in Visual Studio Code and run:

```powershell
Test-Path ".\toolchain\ucrt64\bin\g++.exe"
```

Expected result:

```text
True
```

Verify freeglut:

```powershell
Test-Path ".\toolchain\ucrt64\include\GL\glut.h"
Test-Path ".\toolchain\ucrt64\lib\libfreeglut.dll.a"
Test-Path ".\toolchain\ucrt64\bin\libfreeglut.dll"
```

All three commands should return `True`.

## 4. Build the active C++ file

1. Open the `.cpp` file you want to compile.
2. Click inside its editor tab so it is the active file.
3. Save it using `Ctrl+S`.
4. Press `Ctrl+Shift+B`.

The active-file task creates an executable beside the source file:

```text
main.cpp     → main.exe
triangle.cpp → triangle.exe
circle.cpp   → circle.exe
```

Successful compilation may show no compiler messages. The absence of errors and the creation of the `.exe` file indicate success.

## 5. Run or debug from Visual Studio Code

Open the desired `.cpp` file and use:

| Action | Shortcut |
| --- | --- |
| Build active file | `Ctrl+Shift+B` |
| Build and debug active file | `F5` |
| Build and run without debugging | `Ctrl+F5` |

If prompted to choose a launch configuration, select **Debug Active OpenGL File**.

To use the explicit run task:

1. Press `Ctrl+Shift+P`.
2. Select **Tasks: Run Task**.
3. Select **Build and Run Active OpenGL File**.

The expected result is a separate OpenGL window titled **simple**. The program does not normally print text in the VS Code terminal.

## Important limitation for source files

The active-file configuration is designed for independent, single-file exercises. Each `.cpp` file should contain one `main()` function.

For a program composed of multiple source files such as `main.cpp`, `shapes.cpp`, and `window.cpp`, use CMake or update the build task to compile all required sources.

# macOS Apple Silicon instructions

The C++ source is compatible with M1, M2, M3, and M4 Macs because it selects the macOS header with:

```cpp
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
```

The macro must be written exactly as `__APPLE__`, with two underscores before and after `APPLE`.

## 1. Install Apple Command Line Tools

Open the macOS Terminal and run:

```bash
xcode-select --install
```

This installs Apple Clang and the macOS SDK. If the tools are already installed, macOS will report that no installation is necessary.

Verify the compiler:

```bash
clang++ --version
```

On an Apple Silicon Mac, the output should identify an `arm64` Apple target. You can also check:

```bash
uname -m
```

Expected result:

```text
arm64
```

## 2. Compile on macOS

From the repository root, run:

```bash
clang++ -std=c++17 -Wall -Wextra -g main.cpp -o main -framework OpenGL -framework GLUT
```

Run the program:

```bash
./main
```

For another file, replace `main.cpp` and `main` with the desired source and output names:

```bash
clang++ -std=c++17 -Wall -Wextra -g triangle.cpp -o triangle -framework OpenGL -framework GLUT
./triangle
```

The Windows `.vscode` files in this repository cannot be used unchanged on macOS because they reference `.exe` files, UCRT64, GDB, `freeglut`, and `opengl32`. A separate macOS VS Code configuration or a cross-platform CMake configuration is required for one-shortcut builds on Mac.

# Sample source code

```cpp
#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POLYGON);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(-0.5f,  0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f( 0.5f, -0.5f);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("simple");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
```

# Troubleshooting

## VS Code reports that no build task exists

Confirm that the repository root was opened and that this file exists:

```text
.vscode/tasks.json
```

## `GL/glut.h: No such file or directory` on Windows

Confirm:

```powershell
Test-Path ".\toolchain\ucrt64\include\GL\glut.h"
```

Also verify that `c_cpp_properties.json` points to the compiler inside `toolchain/ucrt64`.

## `cannot find -lfreeglut`

Confirm:

```powershell
Test-Path ".\toolchain\ucrt64\lib\libfreeglut.dll.a"
```

## Windows cannot find `libfreeglut.dll`

Confirm:

```powershell
Test-Path ".\toolchain\ucrt64\bin\libfreeglut.dll"
```

Run the program through the included VS Code task or launch configuration so the portable `bin` directory is temporarily added to `PATH`.

## `cannot execute cc1plus`

The portable compiler is incomplete. Do not copy only `g++.exe` or the `bin` folder. The toolchain must retain its supporting `include`, `lib`, and `x86_64-w64-mingw32` directories, together with any other directories supplied by the minimal UCRT64 installation.

## The program runs but nothing appears in the terminal

The expected output is a graphical GLUT window, not terminal text. Check the Windows taskbar in case the window opened behind Visual Studio Code.

# Portability summary

- The bundled UCRT64 environment makes the repository portable across compatible 64-bit Windows 10/11 computers.
- Visual Studio Code and the Microsoft C/C++ extension remain prerequisites unless they are bundled separately.
- The Windows toolchain is not executable on macOS or Linux.
- The source code is portable because it selects the appropriate GLUT header for each operating system.
- A cross-platform CMake configuration is recommended if the same repository must support one-command builds on Windows, macOS, and Linux.

# License notice

If this repository redistributes GCC, GDB, freeglut, or other MSYS2 packages, retain their license files and review their redistribution terms. Do not remove the toolchain's license notices when preparing a classroom ZIP or release.
