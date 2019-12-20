#pragma once
#ifndef _FvEntity_Node2d_Header
#define _FvEntity_Node2d_Header

#include <Geom_Pnt2d.hxx>
#include <TColFvEntity_HBasicQueueOfElement2d.hxx>
#include <TColFvEntity_HAry1dOfElement2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvEntity_Node2d
		{

		private:

			Standard_Integer theIndex_;

			Geom_Pnt2d theCoord_;

			TColFvEntity_HBasicQueueOfElement2d theElements_;

		public:

			FvEntity_Node2d();

			FvEntity_Node2d(const Standard_Integer theIndex, const Geom_Pnt2d& theCoord);

			void SetCoord(const Geom_Pnt2d& theCoord);

			void SetIndex(const Standard_Integer theIndex);

			void ImportElement(const Global_Handle(FvEntity_Element2d) theElement);

			void RetrieveElementsTo(TColFvEntity_HAry1dOfElement2d& theElements) const;

			Standard_Integer Index() const;

			const Geom_Pnt2d& Coord() const;
		};
	}
}

#include <FvEntity_Node2dI.hxx>

#endif // !_FvEntity_Node2d_Header
