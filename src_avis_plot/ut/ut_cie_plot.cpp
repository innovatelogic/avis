
#include "../cie_plot.h"
#include "../px_canvas.h"

#include <stdio.h>
#include <new>
#include <limits>
#include <gtest/gtest.h>

#if (defined(ES_WINDOWS))
#include <windows.h>
#pragma warning (disable : 4996) // fopen warn
#endif

namespace cie
{
    namespace cie_plot
    {
        bool FileExists(const std::wstring &path)
        {
            if (path.empty()) {
                return false;
            }

            FILE *file = _wfopen(path.c_str(), L"rb");

            if (file == nullptr) {
                return false;
            }
            fclose(file);
            return true;
        }

        //----------------------------------------------------------------------------------------------
        TEST(Cie_Plot, PlotSave)
        {
            std::unique_ptr<cie::cie_plot::CiePlot> convertor(new cie::cie_plot::CiePlot());

            convertor->Plot();

            std::wstring path;

#if (defined(ES_WINDOWS))
            wchar_t ownPth[MAX_PATH];
            HMODULE hModule = GetModuleHandle(NULL);
            if (hModule)
            {
                GetModuleFileName(hModule, ownPth, (sizeof(ownPth)));
                path = ownPth;
                path = path.substr(0, path.rfind('\\'));
            }
#else
            //path = ".";
#endif//ES_WINDOWS
            std::wstring filename = path + std::wstring(TEXT("\\1.ppm"));
            
            bool bRes = convertor->Save(filename);
            
            EXPECT_TRUE(bRes && FileExists(filename));
        }

        //----------------------------------------------------------------------------------------------
        TEST(Cie_Plot, BadMemAlloc_Zero)
        {
            bool bCatch = false;
            try
            {
                std::unique_ptr<cie::cie_plot::Canvas>(new Canvas(0, 0));
            }
            catch (std::bad_alloc&)
            {
                bCatch = true;
            }
            EXPECT_TRUE(bCatch);
        }

        //----------------------------------------------------------------------------------------------
        TEST(Cie_Plot, BadMemAlloc)
        {
            bool bCatch = false;
            try
            {
                const size_t MAX = UINT_MAX;
                std::unique_ptr<cie::cie_plot::Canvas>(new Canvas(MAX, MAX));
            }
            catch (std::bad_alloc&)
            {
                bCatch = true;
            }
            EXPECT_TRUE(bCatch);
        }
    }
}