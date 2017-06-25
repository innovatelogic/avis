#include "cie_plot.h"
#include <iostream>
#include <string>

#if (defined(ES_WINDOWS))
#include <windows.h>
#endif

int main()
{
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
    std::wstring filename = path + std::wstring(TEXT("\\out.ppm"));
	
	std::unique_ptr<cie::cie_plot::CiePlot> convertor(new cie::cie_plot::CiePlot());

    convertor->Plot();

    if (convertor->Save(filename))
    {
        std::wcout << "File saved " << filename.c_str() << std::endl;
    }
    else
    {
        std::wcout << "Failed save file :" << filename.c_str() << std::endl;
    }

    return 0;
}

