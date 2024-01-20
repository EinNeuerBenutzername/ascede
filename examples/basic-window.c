#include "ascede.h"
int main(){
    Window.init(500, 250, "test");
    Window.setMinSize(500, 250);

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
