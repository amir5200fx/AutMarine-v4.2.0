#pragma once
#ifndef _FvEntity_Face2dTools_Header
#define _FvEntity_Face2dTools_Header

#include <FvEntity_Face2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvEntity_Face2dTools
		{

		public:

			static const Geom_Pnt2d& GetCoordOf(Global_Handle(FvEntity_Face2d) theFace);
		};
	}
}

#include <FvEntity_Face2dToolsI.hxx>

#endif // !_FvEntity_Face2dTools_Header
