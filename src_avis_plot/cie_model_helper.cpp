
#include "common.h"
#include "cie_model_helper.h"
#include <algorithm>

namespace cie
{
    namespace cie_plot
    {
        //----------------------------------------------------------------------------------------------
        void xyz_to_rgb(const struct colorSystem * const cs,
                double                      const xc,
                double                      const yc,
                double                      const zc,
                double *                    const r,
                double *                    const g,
                double *                    const b) 
        {
            double xr, yr, zr, xg, yg, zg, xb, yb, zb;
            double xw, yw, zw;
            double rx, ry, rz, gx, gy, gz, bx, by, bz;
            double rw, gw, bw;

            xr = cs->xRed;    yr = cs->yRed;    zr = 1 - (xr + yr);
            xg = cs->xGreen;  yg = cs->yGreen;  zg = 1 - (xg + yg);
            xb = cs->xBlue;   yb = cs->yBlue;   zb = 1 - (xb + yb);

            xw = cs->xWhite;  yw = cs->yWhite;  zw = 1 - (xw + yw);

            // xyz -> rgb matrix, before scaling to white.
            rx = yg*zb - yb*zg;  ry = xb*zg - xg*zb;  rz = xg*yb - xb*yg;
            gx = yb*zr - yr*zb;  gy = xr*zb - xb*zr;  gz = xb*yr - xr*yb;
            bx = yr*zg - yg*zr;  by = xg*zr - xr*zg;  bz = xr*yg - xg*yr;

            // White scaling factors.
            // Dividing by yw scales the white luminance to unity, as conventional.
            rw = (rx*xw + ry*yw + rz*zw) / yw;
            gw = (gx*xw + gy*yw + gz*zw) / yw;
            bw = (bx*xw + by*yw + bz*zw) / yw;

            // xyz -> rgb matrix, correctly scaled to white
            rx = rx / rw;  ry = ry / rw;  rz = rz / rw;
            gx = gx / gw;  gy = gy / gw;  gz = gz / gw;
            bx = bx / bw;  by = by / bw;  bz = bz / bw;

            // rgb of the desired point
            *r = rx*xc + ry*yc + rz*zc;
            *g = gx*xc + gy*yc + gz*zc;
            *b = bx*xc + by*yc + bz*zc;
        }

        //----------------------------------------------------------------------------------------------
        void upvp_to_xy(double   const up,
                double   const vp,
                double * const xc,
                double * const yc) 
        {
            // u,v -> x,y
            *xc = 9 * up / (6 * up - 16 * vp + 12);
            *yc = 4 * vp / (6 * up - 16 * vp + 12);
        }

        //----------------------------------------------------------------------------------------------
        void computeMonochromeColorLocation(
            double                     const waveLength,
            int                        const pxcols,
            int                        const pxrows,
            int *                      const xP,
            int *                      const yP) 
        {

            int const ix = (int)((waveLength - 380) / 5);
            double const px = spectral_chromaticity[ix][0];
            double const py = spectral_chromaticity[ix][1];

            *xP = (int)(px * (pxcols - 1));
            *yP = (int)((pxrows - 1) - py * (pxrows - 1));
        }

        //----------------------------------------------------------------------------------------------
        int constrain_rgb(double * const r, double * const g, double * const b)
        {
            double w;

            // amount of white needed is w = - min(0, *r, *g, *b)
            w = (0 < *r) ? 0 : *r;
            w = (w < *g) ? w : *g;
            w = (w < *b) ? w : *b;
            w = -w;

            // add just enough white to make r, g, b all positive
            if (w > 0) {
                *r += w;
                *g += w;
                *b += w;

                return 1; // Color modified to fit RGB 
            }

            return 0; // Color within RGB gamut 
        }

        //----------------------------------------------------------------------------------------------
        bool findCIERowRange(pixel ** const pixels,
            int      const pxcols,
            int      const row,
            int *    const leftEdgeP,
            int *    const rightEdgeP) 
        {
            int i;

            // scan row
            for (i = 0; i < pxcols && pixels[row][i].r == 0; ++i);

            if (i >= pxcols)
            {
                return false;
            }
            else 
            {
                int j;
                int const leftEdge = i;

                for (j = pxcols - 1; j >= leftEdge && pixels[row][j].r == 0; --j);

                *rightEdgeP = j;
                *leftEdgeP = leftEdge;
            }
            return true;
        }
    }
}