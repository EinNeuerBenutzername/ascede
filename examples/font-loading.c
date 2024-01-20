#include "../../ascede.h"
#include <stdio.h>
int main(){
    Window.init(500, 250, "Font Loading");

    int fntDataSize;
    unsigned char *fntData;
    // Load data yourself here

    TypefaceData tf=Typeface.init(".ttf", fntData, fntDataSize, 48);
    Typeface.update(&tf,
        "0123456789!@#$%^&*()"
        "-_=+[{]}\\|:;\"'<>,./?`~"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
    );
    // This line can be omitted, for that Ascede checks if a character exists in typeface data.

    while(!Window.shouldClose()){
        Loop.poll();
        Buffer.updateBegin();
        Buffer.clear(WHITE);

        char fpsInfo[30];
        sprintf(fpsInfo, "FPS: %.1lf", Time.getFPS());
        Typeface.draw(&tf, fpsInfo, (Vector2){4, 4}, 32, BLACK);
        Typeface.draw(&tf, "test", (Vector2){4, 40}, 48, BLACK);

        Buffer.update();
        Buffer.swap();
        Time.wait(30);
        Loop.end();
    }

    Typeface.denit(tf);
    Window.close();
    return 0;
}



