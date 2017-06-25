#pragma once

#include "defexport.h"
#include "common.h"

namespace cie
{
    namespace cie_plot
    {
        class CIE_EXPORT Canvas
        {
            Canvas(const Canvas&) = delete;
            Canvas& operator =(const Canvas&) = delete;

        public:
            Canvas(size_t rows, size_t cols)
                : m_rows(rows)
                , m_cols(cols)
                , m_pixels(nullptr) {
                Allocate();
            }

            ~Canvas() { Free(); }

            void FillColor(pixel color);

            pixel** data() const { return m_pixels; }

            size_t rows() const { return m_rows; }
            size_t cols() const { return m_cols; }

            // CIE plot helper functions
            void DrawCIEPlotOutline();
            void DrawPlackanLocus(int t0, int t1);
            void PlotCIESpace();

            // draw line. not check bounds
            void line(const pos_point &p0, const pos_point &p1, const pixel &color);

        private:
            void Allocate();
            void Free();

            void FillCIE();

        private:
            const size_t m_rows;
            const size_t m_cols;
            pixel **m_pixels;
        };
    }
}