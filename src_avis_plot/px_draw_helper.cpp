#include "px_draw_helper.h"
#include <math.h>

namespace cie
{
    namespace cie_plot
    {
        //----------------------------------------------------------------------------------------------
        void drawPoint(
            pixel** const pixels,
            const pos_point &p,
            const pixel &color)
        {
            pixels[p.y][p.x] = color;
        }

        //----------------------------------------------------------------------------------------------
        void drawShallowLine(
            pixel ** const pixels,
            const pos_point &p0,
            const pos_point &p1,
            const pixel &color)
        {
            
            // Loop over X domain
            long dy, srow;
            int dx, col, row, prevrow;

            if (p1.x > p0.x) {
                dx = 1;
            }
            else {
                dx = -1;
            }
            dy = (p1.y - p0.y) * DDA_SCALE / abs(p1.x - p0.x);
            
            prevrow = row = p0.y;
            
            srow = row * DDA_SCALE + DDA_SCALE / 2;

            col = p0.x;
            for (; ; ) 
            {
                if (row != prevrow) {
                    drawPoint(pixels,  { col, prevrow }, color);
                    prevrow = row;
                }

                drawPoint(pixels, { col, row }, color);
                if (col == p1.x) {
                    break;
                }
                srow += dy;
                row = srow / DDA_SCALE;
                col += dx;
            }
        }

        //----------------------------------------------------------------------------------------------
        void drawSteepLine(
            pixel ** const pixels,
            const pos_point &p0,
            const pos_point &p1,
            const pixel &color)
        {
            // Loop over Y 

            long dx, scol;
            int dy, col, row, prevcol;

            if (p1.y > p0.y) {
                dy = 1;
            }
            else {
                dy = -1;
            }
            dx = (p1.x - p0.x) * DDA_SCALE / abs(p1.y - p0.y);
            row = p0.y;
            prevcol = col = p0.x;
            scol = col * DDA_SCALE + DDA_SCALE / 2;
            for (;;) 
            {
                if (col != prevcol) 
                {
                    drawPoint(pixels, { prevcol, row }, color);
                    prevcol = col;
                }
                drawPoint(pixels, { col, row }, color);
                if (row == p1.y) {
                    break;
                }
                row += dy;
                scol += dx;
                col = scol / DDA_SCALE;
            }
        }
    }
}