#pragma once
#ifndef _Prop_UnWrappedSection_Header
#define _Prop_UnWrappedSection_Header

#include <Prop_ListOfOffsetPnt3d.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Prop_UnWrappedSection
		{

		private:

			Prop_ListOfOffsetPnt3d theFace_;
			Prop_ListOfOffsetPnt3d theBack_;

		public:

			Prop_UnWrappedSection(const Standard_Integer theNbPts);

			const Prop_ListOfOffsetPnt3d& FaceOffsets() const;

			const Prop_ListOfOffsetPnt3d& BackOffsets() const;

			const Geom_Pnt3d& FaceOffset(const Standard_Integer theIndex) const;

			const Geom_Pnt3d& BackOffset(const Standard_Integer theIndex) const;

			void SetFaceOffset(const Standard_Integer theIndex, const Geom_Pnt3d& theCoord);

			void SetBackOffset(const Standard_Integer theIndex, const Geom_Pnt3d& theCoord);

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <Prop_UnWrappedSectionI.hxx>

#endif // !_Prop_UnWrappedSection_Header
