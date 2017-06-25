#pragma once

#include "defexport.h"
#include "common.h"
#include <string>
#include <memory>

namespace cie
{
	namespace cie_plot
	{
		class CiePlotImpl
		{
			public:
                CiePlotImpl();
				~CiePlotImpl();

                bool Plot();
                bool Save(const std::wstring &filename);
			
            protected:
			private:
                static const size_t SIZE_ROWS = 1024;
                static const size_t SIZE_COLS = 1024;

                std::unique_ptr<class Canvas> m_canvas;
        };
	}
}