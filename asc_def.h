#ifndef ASCEDE_DEF
#define ASCEDE_DEF
#include "src/raylib.h"
//*: with Raylib dependency

void __Asc_Window_Init(int width, int height, const char *title); //*
bool __Asc_Window_IsResizable(void); //*
void __Asc_Window_SetResizable(bool toggle); //*
void __Asc_Window_ToggleFlags(int flags, bool toggle); //*

void __Asc_Loop_End(void);

void __Asc_Time_Wait(double fps);
double __Asc_Time_GetFPS(void);
double __Asc_Time_GetRealFPS(void);
double __Asc_Time_GetFrame(void);

void __Asc_Rtx_DrawBounds(RenderTexture2D rtx, Rectangle bounds); //*

typedef struct {
    int state;
    Font font;
    const unsigned char *fontData;
    int fontDataSize;
} TypefaceData;

TypefaceData __Asc_Typeface_Init(const char *fileType, const unsigned char *fileData, int dataSize, int fontSize); //*
TypefaceData __Asc_Typeface_GetDefaultTf(void); //*
void __Asc_Typeface_Denit(TypefaceData *tf); //*
void __Asc_Typeface_Draw(TypefaceData *tf, const char *text, int posX, int posY, int fontSize, Color tint); //*
void __Asc_Typeface_DrawEx(TypefaceData *tf, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint); //*
void __Asc_Typeface_DrawWrapped(TypefaceData *tf, const char *text, Rectangle rec, int fontSize, Color tint); //*
void __Asc_Typeface_Update(TypefaceData *tf, const char *str); //*, memory manipulation (malloc(), free())

const struct { // Window
    void (*close)(void);
    void (*init)(int width, int height, const char * title);
    bool (*shouldClose)(void);
    void (*setExitKey)(int key);
    void (*setSize)(int width, int height);
    void (*setMinSize)(int minWidth, int minHeight);
    bool (*isResizable)(void);
    void (*setResizable)(bool toggle);
    void (*toggleFlags)(int flags, bool toggle);
    int (*getWidth)(void);
    int (*getHeight)(void);
    void (*toggleFullscreen)(void);
    bool (*isFullscreen)(void);
    void (*maximize)(void);
    bool (*isMaximized)(void);
    void (*minimize)(void);
    bool (*isMinimized)(void);
    void (*restore)(void);
    bool (*isResized)(void);
} Window = {
    .close=CloseWindow,
    .init=__Asc_Window_Init,
    .shouldClose=WindowShouldClose,
    .setExitKey=SetExitKey,
    .setSize=SetWindowSize,
    .setMinSize=SetWindowMinSize,
    .toggleFlags=__Asc_Window_ToggleFlags,
    .isResizable=__Asc_Window_IsResizable,
    .setResizable=__Asc_Window_SetResizable,
    .getWidth=GetScreenWidth,
    .getHeight=GetScreenHeight,
    .toggleFullscreen=ToggleFullscreen,
    .isFullscreen=IsWindowFullscreen,
    .maximize=MaximizeWindow,
    .isMaximized=IsWindowMaximized,
    .minimize=MinimizeWindow,
    .isMinimized=IsWindowMinimized,
    .restore=RestoreWindow,
    .isResized=IsWindowResized
};

const struct { // Key
    bool (*isDown)(int key);
    bool (*isPressed)(int key);
    bool (*isReleased)(int key);
    int (*inputKeyCode)(void);
    int (*inputCodepoint)(void);
} Key = {
    .isDown=IsKeyDown,
    .isPressed=IsKeyPressed,
    .isReleased=IsKeyReleased,
    .inputKeyCode=GetKeyPressed,
    .inputCodepoint=GetCharPressed
};

const struct { // Loop
    void (*poll)(void);
    void (*end)(void);
} Loop = {
    .poll=PollInputEvents,
    .end=__Asc_Loop_End
};

const struct { // Time
    double (*get)(void);
    double (*getFrame)(void);
    void (*sleep)(double seconds);
    void (*wait)(double targetFPS);
    double (*getFPS)(void);
    double (*getRealFPS)(void);
} Time = {
    .get=GetTime,
    .getFrame=__Asc_Time_GetFrame,
    .sleep=WaitTime,
    .wait=__Asc_Time_Wait,
    .getFPS=__Asc_Time_GetFPS,
    .getRealFPS=__Asc_Time_GetRealFPS
};

const struct { // Buffer
    void (*updateBegin)(void);
    void (*clear)(Color color);
    void (*swap)(void);
    void (*update)(void);
} Buffer = {
    .updateBegin=BeginDrawing,
    .clear=ClearBackground,
    .update=EndDrawing,
    .swap=SwapScreenBuffer
};

const struct { // Rtx (RenderTexture2D)
    RenderTexture2D (*init)(int width, int height);
    void (*denit)(RenderTexture2D rtx);
    void (*updateBegin)(RenderTexture2D rtx);
    void (*update)(void);
    void (*drawBounds)(RenderTexture2D rtx, Rectangle bounds);
} Rtx = {
    .init=LoadRenderTexture,
    .denit=UnloadRenderTexture,
    .updateBegin=BeginTextureMode,
    .update=EndTextureMode,
    .drawBounds=__Asc_Rtx_DrawBounds
};

const struct { // Mouse
    int (*getX)(void);
    int (*getY)(void);
    Vector2 (*getDelta)(void);
    float (*getWheel)(void);
    void (*setPos)(int x, int y);
    bool (*isDown)(int button);
    bool (*isPressed)(int button);
    bool (*isReleased)(int button);
    bool (*isOnScreen)(void);
} Mouse = {
    .getX=GetMouseX,
    .getY=GetMouseY,
    .getDelta=GetMouseDelta,
    .getWheel=GetMouseWheelMove,
    .setPos=SetMousePosition,
    .isDown=IsMouseButtonDown,
    .isPressed=IsMouseButtonPressed,
    .isReleased=IsMouseButtonReleased,
    .isOnScreen=IsCursorOnScreen
};

struct { // Typeface
    TypefaceData (*init)(const char *fileType, const unsigned char *fileData, int dataSize, int fontSize);
    TypefaceData (*getDefaultTf)(void);
    void (*denit)(TypefaceData *tf); // data within Typeface{} has to be freed manually afterwards
    void (*draw)(TypefaceData *tf, const char *text, int posX, int posY, int fontSize, Color tint);
    void (*drawEx)(TypefaceData *tf, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint);
    void (*drawWrapped)(TypefaceData *tf, const char *text, Rectangle rec, int fontSize, Color tint);
    void (*update)(TypefaceData *tf, const char *str);
} Typeface = {
    .init=__Asc_Typeface_Init,
    .getDefaultTf=__Asc_Typeface_GetDefaultTf,
    .denit=__Asc_Typeface_Denit,
    .draw=__Asc_Typeface_Draw,
    .drawEx=__Asc_Typeface_DrawEx,
    .drawWrapped=__Asc_Typeface_DrawWrapped,
    .update=__Asc_Typeface_Update
};

struct { // Shape
    void (*drawRec)(int posX, int posY, int width, int height, Color color);
} Shape = {
    .drawRec=DrawRectangle
};

struct { // Tint
    Color (*fade)(Color color, float fade);
} Tint = {
    .fade=Fade
};

struct { // Audio...?
    void (*init)(void);
    void (*close)(void);
    bool (*isReady)(void);
    void (*setMasterVolume)(void);
} Audio = {
    0
};


#endif
