#include "ascede.h"
int main(){
    asc_init();
    Window.init(500, 250, "rendertexture");
    Window.setResizable(true);
    Window.setMinSize(500, 250);
    RenderTexture2D rtx=Rtx.init(100, 50);

    while(!Window.shouldClose()){
        Loop.poll();
        Buffer.updateBegin();
        Buffer.clear(BLACK);

        Rtx.updateBegin(rtx);
        Buffer.clear(MAROON);

        Rtx.update();
        Rtx.drawBounds(rtx, (Rectangle){0, 0, Window.getWidth(), Window.getHeight()});

        Buffer.update();
        Buffer.swap();
        Time.wait(60);
        Loop.end();
    }

    Rtx.denit(rtx);

    Window.close();
    return 0;
}
