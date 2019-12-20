#pragma once
#ifndef _FvMesh2d_Header
#define _FvMesh2d_Header

//#include <FvGeom_Node2d.hxx>
//#include <FvGeom_Face2d.hxx>
//#include <FvGeom_Element2d.hxx>
#include <FvPrimitives_Label.hxx>
#include <FvList_Node2d.hxx>
#include <FvList_Face2d.hxx>
#include <FvList_Element2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvGeom_StaticMesh2d;

		class FvMesh2d
		{

		private:

			FvList_Node2d theNodes_;

			FvList_Element2d theElements_;

			FvList_Face2d theFaces_;
			FvList_Face2d theBoundaries_;

		public:

			FvMesh2d();

			Label NbNodes() const;

			Label NbFaces() const;

			Label NbElements() const;

			const Global_Handle(FvEntity_Node2d) Node(const Label theIndex) const;

			const Global_Handle(FvEntity_Face2d) Face(const Label theIndex) const;

			const Global_Handle(FvEntity_Element2d) Element(const Label theIndex) const;

			void ImportFrom(const FvGeom_StaticMesh2d& theStatic);
		};
	}
}

#include <FvMesh2dI.hxx>

#endif // !_FvMesh2d_Header
