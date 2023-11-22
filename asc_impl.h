#ifndef ASCEDE_IMPL
#define ASCEDE_IMPL
#include "src/raylib.h"
void asc_init(){
    Window.close=CloseWindow;
    Window.init=__Asc_Window_Init;
    Window.shouldClose=WindowShouldClose;
    Window.setExitKey=SetExitKey;
    Window.setExitKey(-32768);
    Window.setSize=SetWindowSize;
    Window.setMinSize=SetWindowMinSize;
    Window.toggleFlags=__Asc_Window_ToggleFlags;
    Window.isResizable=__Asc_Window_IsResizable;
    Window.setResizable=__Asc_Window_SetResizable;
    Window.getWidth=GetScreenWidth;
    Window.getHeight=GetScreenHeight;

    Key.isUp=IsKeyUp;
    Key.isDown=IsKeyDown;
    Key.isPressed=IsKeyPressed;
    Key.isReleased=IsKeyReleased;

    Loop.poll=PollInputEvents;
    Loop.end=__Asc_Loop_End;

    Time.get=GetTime;
    Time.getFrame=__Asc_Time_GetFrame;
    Time.sleep=WaitTime;
    Time.wait=__Asc_Time_Wait;
    Time.getFPS=__Asc_Time_GetFPS;
    Time.getRealFPS=__Asc_Time_GetRealFPS;

    Buffer.updateBegin=BeginDrawing;
    Buffer.clear=ClearBackground;
    Buffer.update=EndDrawing;
    Buffer.swap=SwapScreenBuffer;

    Rtx.init=LoadRenderTexture;
    Rtx.denit=UnloadRenderTexture;
    Rtx.updateBegin=BeginTextureMode;
    Rtx.update=EndTextureMode;
    Rtx.drawBounds=__Asc_Rtx_DrawBounds;
}

static void __Asc_Window_Init(int width, int height, const char *title){
    InitWindow(width, height, title);
    Window.setResizable(true);
    Window.toggleFlags(FLAG_WINDOW_RESIZABLE|FLAG_WINDOW_ALWAYS_RUN, true);
}
static bool __Asc_Window_IsResizable(void){
    return IsWindowState(FLAG_WINDOW_RESIZABLE);
}
static void __Asc_Window_SetResizable(bool toggle){
    if(toggle){
        __Asc_Window.state|=FLAG_WINDOW_RESIZABLE;
        SetWindowState(FLAG_WINDOW_RESIZABLE);
    }else{
        __Asc_Window.state&=~FLAG_WINDOW_RESIZABLE;
        ClearWindowState(FLAG_WINDOW_RESIZABLE);
    }
}
static void __Asc_Window_ToggleFlags(int flags, bool toggle){
    if(toggle){
        __Asc_Window.state|=flags;
        SetWindowState(flags);
    }else{
        __Asc_Window.state&=~flags;
        ClearWindowState(flags);
    }
}
static void __Asc_Loop_End(){
    __Asc_Time.current=Time.get();
    __Asc_Time.frame=__Asc_Time.current-__Asc_Time.previous;
    __Asc_Time.previous=__Asc_Time.current;
    __Asc_Time.frameCounter++;
    if(__Asc_Time.frame>0){
        __Asc_Time.histIndex=(__Asc_Time.histIndex+1)%__ASC_TIME_HISTORIES;
        __Asc_Time.average-=__Asc_Time.history[__Asc_Time.histIndex];
        __Asc_Time.history[__Asc_Time.histIndex]=__Asc_Time.frame/(double)__ASC_TIME_HISTORIES;
        __Asc_Time.average+=__Asc_Time.history[__Asc_Time.histIndex];
        __Asc_Time.FPS=1.0f/__Asc_Time.average;
    }else{
        __Asc_Time.abnormal=__ASC_TIME_HISTORIES;
        __Asc_Time.FPS=0;
    }
    if(__Asc_Time.abnormal)__Asc_Time.abnormal--;
}

static void __Asc_Time_Wait(double targetFPS){
    if(targetFPS<=0.5f)return;
    if(targetFPS>32767.0f)return;
    __Asc_Time.targetFPS=targetFPS;
    double extra=__Asc_Time.extratime;
    double previous=__Asc_Time.previous;
    double target=1.0f/targetFPS;
    double wait=previous+target-Time.get();
    // Prevent losing too many frames.
    double absextra=extra>0?extra:-1.0f*extra;
    if(absextra>target*5.0f && absextra>0.1f){
        extra=0;
        __Asc_Time.abnormal=__ASC_TIME_HISTORIES;
    }
    if(wait+extra>0){
        Time.sleep(wait+extra);
    }else{
        __Asc_Time.abnormal=__ASC_TIME_HISTORIES;
    }
    extra+=previous+target-Time.get();
    __Asc_Time.extratime=extra;
}
static double __Asc_Time_GetFPS(void){
    if(__Asc_Time.abnormal==0){
        return __Asc_Time.targetFPS;
    }else{
        return __Asc_Time.FPS;
    }
}
static double __Asc_Time_GetRealFPS(void){
    return __Asc_Time.FPS;
}
static double __Asc_Time_GetFrame(void){
    return __Asc_Time.frame;
}

static void __Asc_Rtx_DrawBounds(RenderTexture2D rtx, Rectangle bounds){
    Texture2D texture=rtx.texture;
    float scale=bounds.width*1.0f/texture.width<bounds.height*1.0f/texture.height?
        bounds.width*1.0f/texture.width: bounds.height*1.0f/texture.height;
    DrawTexturePro(texture,
        (Rectangle){0, texture.height, texture.width, -texture.height},
        (Rectangle){
            bounds.x+(bounds.width-scale*texture.width)/2.0f,
            bounds.y+(bounds.height-scale*texture.height)/2.0f,
            scale*texture.width, scale*texture.height
        }, (Vector2){0,0}, 0, WHITE
    );
}

#endif
