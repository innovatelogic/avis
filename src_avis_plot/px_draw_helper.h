#pragma once

#include "common.h"

namespace cie
{
    namespace cie_plot
    {
        void drawPoint(
            pixel** const pixels,
            const pos_point &p,
            const pixel &color);

        /*!
        Draw a line that is more horizontal than vertical.
        Don't clip.
        */
        void drawShallowLine(
            pixel** const pixels,
            const pos_point     &p0,
            const pos_point     &p1,
            const pixel &color);

        /*!
        Draw a line that is more vertical than horizontal.
        Don't clip.
        */
        void drawSteepLine(
                pixel** const pixels,
                const pos_point &p0,
                const pos_point &p1,
                const pixel &color);
    }
}