#pragma once

#include <string>

#include "knapsack/render.h"
#include "knapsack/alignment.h"

struct Text : public Renderable {
private:
    int w, h;
    std::string text;
    int size;
    Vector4 color;
    bool u_flag = false;
    void* texture = nullptr;
    void refresh();
public:

    /**
     * initializes a renderable which draws text to the screen
     * 
     * string text      -   the text to draw
     * int size         -   the font size for the text
     * SDL_Color color  -   the {r, g, b} color of the text
     */ 
    Text(std::string text, int size, Vector4 color);

    ~Text();

    /**
     * updates the text for this renderable. Calling this every frame
     * will have a strong performance impact and it should be avoided
     * 
     * string text  -   the new texxt
     */ 
    void update(std::string text);

    /**
     * updates the font size for this text. Calling this every frame
     * will have a strong performance impact and it should be avoided
     * 
     * int size  -   the font size for this text
     */ 
    void update(int size);

    /**
     * updates the color which this text should be drawn as. Calling
     * this every frame will have a strong performance impact and it
     * should be avoided
     * 
     * SDL_Color color  -   the {r, g, b} color to draw the text as
     */ 
    void update(Vector4 color);

     /**
     * Draws the given text at the specified x and y coordinates,
     * with the given z sorting
     * 
     * int x    -   x position to draw at
     * int y    -   y position to draw at
     * int z    -   z layer for sorting
     */ 
    void render(Vector3 pos, float scalex = TEXTSCALE_X, float scaley = TEXTSCALE_Y);

    /**
     * Draws the given text using the information contained in
     * an alignment, with the given z sorting
     * 
     * Alignment* align -   a pointer to the alignment to reference
     * int z            -   z layer for sorting
     */ 
    void render(Alignment* align, float scalex = TEXTSCALE_X, float scaley = TEXTSCALE_Y);

    /**
     * Draws the given text using the information contained in
     * an alignment, subtracting the provided x and y offsets,
     * with the given z sorting
     * 
     * Alignment* align -   a pointer to the alignment to reference
     * int xoff         -   an x offset which is subtracted from the
     *                      alignment x
     * int yoff         -   a y offset which is subtracted from the
     *                      alignment y
     * int z            -   z layer for sorting
     */ 
    void render(Alignment* align, int xoff, int yoff, float scalex = TEXTSCALE_X, float scaley = TEXTSCALE_Y);
}; 