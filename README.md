# ascede

Ascede is a simple wrapper that I wrote for [Raylib](https://github.com/raysan5/raylib), and is intended for personal use. It is C99, **header-only**, and intended to be extremely user-friendly.

To use, put Raylib's `src` folder in ascede's directory, and `#include "ascede.h"` instead of `raylib.h`. When compiling, **link raylib** as when building with vanilla Raylib.

It is **a must** to **enable** the compiling flag `SUPPORT_CUSTOM_FRAME_CONTROL` for Raylib beforehand. Ascede's time module **wouldn't work otherwise**.

## Why ascede?

- Raylib has very terrible frame control with `SUPPORT_CUSTOM_FRAME_CONTROL` disabled.
  - Busy wait loops and half-busy wait loops are lies, and do not really contribute much to FPS stability. Raylib's `GetFPS()`, in the mean time, only returns a **fake** FPS value that covers up the problem, as far as I understand the vanilla time module.
- Raylib's function naming makes it very difficult to find the desired function through auto-completion when without enough familiarity with its API.
- Developing ascede also makes it easier for me to put forward tweaks on Raylib **without having to change its code**.
  - I used to boost my development through altering the codebase of Raylib, which was soon proved a very bad idea, as Raylib is a library under active development.

## Step-by-step build for beginners

1. Download sources for Ascede and Raylib.
2. Replace Raylib's `config.h` header file with the one provided by Ascede.
   - Alternative: I made a few changes in it to suit the development of Ascede. You might as well ignore the file and make your own alterations instead.
3. Compile Raylib from source. In case you don't know how, check Raylib's repo.
4. Copy Ascede's headers to just outside of Raylib's `src` folder.
   - Alternative: Change the `#include` path in `asc_def.h` to include `raylib.h`.
5. `#include "asc_def.h"` in your development, and `#include "ascede.h"` in the source file that requires implementations.

## Example

```C
#include "ascede.h"
int main(){
    Window.init(400, 300, "test");
    Window.setMinSize(200, 150);

    while(!Window.shouldClose()){
        Loop.poll();
        Buffer.drawBegin();
        Buffer.clear(WHITE);

        Buffer.drawEnd();
        Buffer.swap();
        Time.wait(60);
        Loop.end();
    }
    Window.close();
    return 0;
}
```

## Version history

- Update #1 - Nov 23, 2023
  - Wrapped the modules of `Window`, `Buffer`, `Loop` and `Rtx` (for type `RenderTexture`).
  - Implemented time module and wrapped several most common functions.
  - Implemented function `Rtx.drawBounds()`.
- Update #2 - Jan 20, 2024
  - Wrapped the modules of `Mouse`, `Key`, `Typeface` and `Shape`.
  - Implemented typeface manipulations, including a smart loading of Unicode fonts.
  - Implemented function `Typeface.update()`.
  - Removed `asc_init()` and made wrapper function pointers constant for consistency.

## Future to-dos

- Implement text module, and implement function `Text.drawRec()` as provided in Raylib's official examples.
  - Maybe integrate UTF8-based string manipulation... Or maybe not.
- Improve Raylib's sound and music module.
  - Implement seamless playbacks and sound channels.
- Implement a memory-leak tracker that tracks through Ascede's `init()` and `denit()` functions.
  - Use a linked list to track through memory leaks.
  - Also wrap up a malloc, probably?