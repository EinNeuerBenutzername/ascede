#ifndef ASCEDE_DEF
#define ASCEDE_DEF
#include "src/raylib.h"
struct {
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
} Window = {0};

struct {
    int state;
} __Asc_Window = {0};

struct {
    bool (*isDown)(int key);
    bool (*isUp)(int key);
    bool (*isPressed)(int key);
    bool (*isReleased)(int key);
} Key = {0};

struct {
    void (*poll)(void);
    void (*end)(void);
} Loop = {0};

struct {
    double (*get)(void);
    double (*getFrame)(void);
    void (*sleep)(double seconds);
    void (*wait)(double FPS);
    double (*getFPS)(void);
    double (*getRealFPS)(void);
} Time = {0};

#ifndef __ASC_TIME_HISTORIES
#define __ASC_TIME_HISTORIES 30
#endif
static struct {
    double previous;
    double current;
    double frame;
    double FPS;
    unsigned int frameCounter;
    double extratime;
    int abnormal;
    int histIndex;
    double history[__ASC_TIME_HISTORIES];
    double average;
    double targetFPS;
} __Asc_Time = {0};

struct {
    void (*updateBegin)(void);
    void (*clear)(Color color);
    void (*swap)(void);
    void (*update)(void);
} Buffer = {0};

struct {
    RenderTexture2D (*init)(int width, int height);
    void (*denit)(RenderTexture2D rtx);
    void (*updateBegin)(RenderTexture2D rtx);
    void (*update)(void);
    void (*drawBounds)(RenderTexture2D rtx, Rectangle bounds);
} Rtx;

void asc_init();

static void __Asc_Window_Init(int width, int height, const char *title); //*
static bool __Asc_Window_IsResizable(void); //*
static void __Asc_Window_SetResizable(bool toggle); //*
static void __Asc_Window_ToggleFlags(int flags, bool toggle); //*

static void __Asc_Loop_End(void);

static void __Asc_Time_Wait(double fps);
static double __Asc_Time_GetFPS(void);
static double __Asc_Time_GetRealFPS(void);
static double __Asc_Time_GetFrame(void);

static void __Asc_Rtx_DrawBounds(RenderTexture2D rtx, Rectangle bounds); //*

#endif
