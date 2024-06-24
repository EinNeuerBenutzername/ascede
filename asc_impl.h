#ifndef ASCEDE_IMPL
#define ASCEDE_IMPL
#include "asc_def.h"
#include <stdlib.h>

// memory leak tracker
typedef struct __Struct_Asc_Mem_Link __Struct_Asc_Mem_Link;
struct __Struct_Asc_Mem_Link {
    __Struct_Asc_Mem_Link *previous;
    void *ptr;
    __Struct_Asc_Mem_Link *next;
};


//-----------------------

struct {
    int state;
} __Asc_Window = {0};

void __Asc_Window_Init(int width, int height, const char *title){
    InitWindow(width, height, title);
    Window.setResizable(true);
    Window.toggleFlags(FLAG_WINDOW_ALWAYS_RUN, true);
}
bool __Asc_Window_IsResizable(void){
    return IsWindowState(FLAG_WINDOW_RESIZABLE);
}
void __Asc_Window_SetResizable(bool toggle){
    if(toggle){
        __Asc_Window.state|=FLAG_WINDOW_RESIZABLE;
        SetWindowState(FLAG_WINDOW_RESIZABLE);
    }else{
        __Asc_Window.state&=~FLAG_WINDOW_RESIZABLE;
        ClearWindowState(FLAG_WINDOW_RESIZABLE);
    }
}
void __Asc_Window_ToggleFlags(int flags, bool toggle){
    if(toggle){
        __Asc_Window.state|=flags;
        SetWindowState(flags);
    }else{
        __Asc_Window.state&=~flags;
        ClearWindowState(flags);
    }
}

#ifndef __ASC_TIME_HISTORIES
#define __ASC_TIME_HISTORIES 30
#endif

struct {
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

void __Asc_Loop_End(){
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

void __Asc_Time_Wait(double targetFPS){
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
double __Asc_Time_GetFPS(void){
    if(__Asc_Time.abnormal==0){
        return __Asc_Time.targetFPS;
    }else{
        return __Asc_Time.FPS;
    }
}
double __Asc_Time_GetRealFPS(void){
    return __Asc_Time.FPS;
}
double __Asc_Time_GetFrame(void){
    return __Asc_Time.frame;
}

void __Asc_Rtx_DrawBounds(RenderTexture2D rtx, Rectangle bounds){
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

TypefaceData __Asc_Typeface_Init(const char *fileType, const unsigned char *fileData, int dataSize, int fontSize){
    TypefaceData tf;
    int cp[3]={0, 0, 0}; // Sometimes it just breaks without duplicate initial zeroes, idk why
    tf.font=LoadFontFromMemory(fileType, fileData, dataSize, fontSize, cp, 3);
    tf.fontData=fileData;
    tf.fontDataSize=dataSize;
    tf.state=1;
    return tf;
}
TypefaceData __Asc_Typeface_GetDefaultTf(void){
    TypefaceData tf;
    tf.font=GetFontDefault();
    tf.fontData=NULL;
    tf.fontDataSize=0;
    tf.state=2;
    return tf;
}
void __Asc_Typeface_Denit(TypefaceData *tf){
    UnloadFont(tf->font);
    tf->fontData=NULL;
    tf->fontDataSize=0;
    tf->state=0;
}
void __Asc_Typeface_Draw(TypefaceData *tf, const char *text, int posX, int posY, int fontSize, Color tint){
    if(!tf->state)return;
    Typeface.update(tf, text);
    DrawTextEx(tf->font, text, (Vector2){posX, posY}, fontSize, (tf->state==2)?fontSize/10:0, tint);
}
void __Asc_Typeface_DrawEx(TypefaceData *tf, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint){
    if(!tf->state)return;
    Typeface.update(tf, text);
    DrawTextPro(tf->font, text, position, origin, rotation, fontSize, spacing, tint);
}
void __Asc_Typeface_DrawWrapped(TypefaceData *tf, const char *text, Rectangle rec, int fontSize, Color tint){
    if(!tf->state)return;
    Typeface.update(tf, text);
    (void)text;
    (void)rec;
    (void)fontSize;
    (void)tint;
}
void __Asc_Typeface_Update(TypefaceData *tf, const char *str){
    if(!tf->fontData || !tf->fontDataSize)return;
    int cpSize, *cp=LoadCodepoints(str, &cpSize);
    Font *font=&tf->font;
    int typefaceShouldUpdate=0;
    for(int i=0; i<cpSize; i++){
        int found=0;
        for(int j=0; j<font->glyphCount; j++){
            if(font->glyphs[j].value==cp[i]){
                found=1;
                break;
            }
        }
        if(!found){
            typefaceShouldUpdate=1;
            break;
        }
    }
    if(!typefaceShouldUpdate || !cpSize)return;
    GlyphInfo *glyphs=LoadFontData(tf->fontData, tf->fontDataSize, font->baseSize, cp, cpSize, FONT_DEFAULT);
    UnloadCodepoints(cp);
    if(glyphs){
        int fontGlyphCount=font->glyphCount, len=fontGlyphCount;
        GlyphInfo *glyphUnion=malloc(sizeof(GlyphInfo)*(cpSize+len));
        if(fontGlyphCount){
//            memcpy(glyphUnion, font->glyphs, sizeof(GlyphInfo)*fontGlyphCount);
            for(int i=0; i<fontGlyphCount; i++){
                glyphUnion[i]=font->glyphs[i];
            }
        }
        for(int i=0; i<cpSize; i++){
            int found=0;
            for(int j=0; j<len; j++){
                if(glyphUnion[j].value==glyphs[i].value){
                    found=1;
                    UnloadImage(glyphs[i].image);
                    break;
                }
            }
            if(!found){
                glyphUnion[len]=glyphs[i];
//                memcpy(glyphUnion+len, glyphs+i, sizeof(GlyphInfo));
                len++;
            }
        }
        if(fontGlyphCount)free(font->glyphs);
        free(glyphs);
        font->glyphs=glyphUnion;
        font->glyphCount=len;
        if(len!=fontGlyphCount){
            free(font->recs);
            Image atlas=GenImageFontAtlas(font->glyphs, &font->recs, font->glyphCount, font->baseSize, font->glyphPadding, 1);
            UnloadTexture(font->texture);
            font->texture=LoadTextureFromImage(atlas);
//            for(int i=0; i<font->glyphCount; i++){
//                UnloadImage(font->glyphs[i].image);
//                font->glyphs[i].image=ImageFromImage(atlas,font->recs[i]);
//            }
            UnloadImage(atlas);
        }
    }
}



#endif
