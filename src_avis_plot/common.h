
#pragma once

#include <math.h>

namespace cie
{
    namespace cie_plot
    {
        static long int const DDA_SCALE = 8192;

        typedef unsigned char pixval;
        struct pixel 
        {
            pixval r, g, b;
        };

        struct pos_point 
        {
            int x;
            int y;

            bool operator==(const pos_point &right) const
            {
                return x == right.x && y == right.y;
            }
        };

        #define Maxval  255                   /* Maxval to use in generated pixmaps */

        struct colorSystem
        {
            double xRed, yRed,     /* Red xy */
                xGreen, yGreen,    /* Green xy */
                xBlue, yBlue,      /* Blue xy */
                xWhite, yWhite,    /* White point */
                gamma;             /* gamma of nonlinear correction */
        };

        // Primary Color Chromatics
        //// https://books.google.com.ua/books?id=SKT8BAAAQBAJ&pg=PA148&lpg=PA148&dq=Red+primary+illuminant+CIE+0.670&source=bl&ots=N5k9TX508W&sig=NpuCICrSQ_Oy0X8q7Ar08_CwKec&hl=en&sa=X&ved=0ahUKEwjt76HJrv7TAhUjDZoKHVoQCXkQ6AEIPTAF#v=onepage&q=Red%20primary%20illuminant%20CIE%200.670&f=false

        #define IlluminantC     0.3101, 0.3162  /* White point Chromaticities */
        #define IlluminantD65   0.3127, 0.3291 

        #define GAMMA_REC709    0.      /* Rec. 709 */

        static struct colorSystem const
        CIEsystem = {
            0.670, 0.330, 0.210, 0.710, 0.150, 0.060,
            IlluminantD65,  GAMMA_REC709
        };

        /* CIE x-y space x(\lambda) and y(\lambda) 
        5 nm increments
        from 380 nm through  780  nm. */

        static double spectral_chromaticity[81][3] = {
            { 0.1741, 0.0050 },               /* 380 nm */
            { 0.1740, 0.0050 },
            { 0.1738, 0.0049 },
            { 0.1736, 0.0049 },
            { 0.1733, 0.0048 },
            { 0.1730, 0.0048 },
            { 0.1726, 0.0048 },
            { 0.1721, 0.0048 },
            { 0.1714, 0.0051 },
            { 0.1703, 0.0058 },
            { 0.1689, 0.0069 },
            { 0.1669, 0.0086 },
            { 0.1644, 0.0109 },
            { 0.1611, 0.0138 },
            { 0.1566, 0.0177 },
            { 0.1510, 0.0227 },
            { 0.1440, 0.0297 },
            { 0.1355, 0.0399 },
            { 0.1241, 0.0578 },
            { 0.1096, 0.0868 },
            { 0.0913, 0.1327 },
            { 0.0687, 0.2007 },
            { 0.0454, 0.2950 },
            { 0.0235, 0.4127 },
            { 0.0082, 0.5384 },
            { 0.0039, 0.6548 },
            { 0.0139, 0.7502 },
            { 0.0389, 0.8120 },
            { 0.0743, 0.8338 },
            { 0.1142, 0.8262 },
            { 0.1547, 0.8059 },
            { 0.1929, 0.7816 },
            { 0.2296, 0.7543 },
            { 0.2658, 0.7243 },
            { 0.3016, 0.6923 },
            { 0.3373, 0.6589 },
            { 0.3731, 0.6245 },
            { 0.4087, 0.5896 },
            { 0.4441, 0.5547 },
            { 0.4788, 0.5202 },
            { 0.5125, 0.4866 },
            { 0.5448, 0.4544 },
            { 0.5752, 0.4242 },
            { 0.6029, 0.3965 },
            { 0.6270, 0.3725 },
            { 0.6482, 0.3514 },
            { 0.6658, 0.3340 },
            { 0.6801, 0.3197 },
            { 0.6915, 0.3083 },
            { 0.7006, 0.2993 },
            { 0.7079, 0.2920 },
            { 0.7140, 0.2859 },
            { 0.7190, 0.2809 },
            { 0.7230, 0.2770 },
            { 0.7260, 0.2740 },
            { 0.7283, 0.2717 },
            { 0.7300, 0.2700 },
            { 0.7311, 0.2689 },
            { 0.7320, 0.2680 },
            { 0.7327, 0.2673 },
            { 0.7334, 0.2666 },
            { 0.7340, 0.2660 },
            { 0.7344, 0.2656 },
            { 0.7346, 0.2654 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 },
            { 0.7347, 0.2653 }                /* 780 nm */
        };

        // Plackan locus cubic spline x-y coef
        static double pl_x_temperature[2][4] = {
            { -0.2661, -0.2343, 0.8776, 0.1799 }, // T <= 4000
            { -3.0258, 2.1070, 0.2226, 0.2403 },
        };

        static double pl_y_temperature[3][4] = {
            { -1.1063, -1.3481, 2.1855, -0.2021 }, // T <= 2222
            { -0.9549, -1.3741, 2.0913, -0.1674 }, // T > 2222 && T <= 4000
            { 3.0817, -5.8733, 3.7511, -0.3700 },
        };
    }
}