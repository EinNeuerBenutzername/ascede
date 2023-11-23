# ascede

Ascede is a simple wrapper that I wrote for [Raylib](https://github.com/raysan5/raylib), and is intended for personal use. It is C99, header-only, and extremely user-friendly.

To use, put Raylib's `src` folder in ascede's directory, and `#include "ascede.h"` instead of `raylib.h`. When compiling, **link raylib** as when building with vanilla Raylib.

It is **a must** to and **enable** `SUPPORT_CUSTOM_FRAME_CONTROL` beforehand. Ascede's time module **wouldn't work otherwise**.

## Why ascede?

- Raylib has very terrible frame control with `SUPPORT_CUSTOM_FRAME_CONTROL` disabled.
  - Busy wait loops and half-busy wait loops are lies, and do not really contribute much to FPS stability. Raylib's `GetFPS()`, in the mean time, only returns a **fake** FPS value that covers up the problem, as far as I understand the vanilla time module.
- Raylib's function naming makes it very difficult to find the desired function through auto-completion when without enough familiarity with its API.
- Developing ascede also makes it easier for me to put forward tweaks on Raylib **without having to change its code**.
  - I used to boost my development through altering the codebase of Raylib, which was soon proved a very bad idea, as Raylib is a library under active development.

## Example

```C
#include "ascede.h"
int main(){
    asc_init();
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
  - Implemented time module and wrapped several most common functions.
  - Implemented function `Rtx.drawBounds()`.
