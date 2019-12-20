#pragma once
#ifndef _FvEntity_Node2d_Header
#define _FvEntity_Node2d_Header

#include <Geom_Pnt2d.hxx>
#include <FvPrimitives_Label.hxx>
#include <FvQueue_Element2d.hxx>
#include <FvList_Element2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvEntity_Node2d
		{

		private:

			Label theIndex_;

			Geom_Pnt2d theCoord_;

			FvQueue_Element2d theElements_;

		public:

			FvEntity_Node2d();

			FvEntity_Node2d(const Label theIndex, const Geom_Pnt2d& theCoord);

			void SetCoord(const Geom_Pnt2d& theCoord);

			void SetIndex(const Label theIndex);

			void ImportElement(const Global_Handle(FvEntity_Element2d) theElement);

			void RetrieveElementsTo(FvList_Element2d& theElements) const;

			Label Index() const;

			const Geom_Pnt2d& Coord() const;
		};
	}
}

#include <FvEntity_Node2dI.hxx>

using AutLib::FvLib::FvEntity_Node2d;

#endif // !_FvEntity_Node2d_Header
