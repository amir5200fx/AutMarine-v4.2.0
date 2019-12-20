#pragma once
#ifndef _FvEntity_Element2d_Header
#define _FvEntity_Element2d_Header

#include <Global_Memory.hxx>
#include <Standard_TypeDef.hxx>
#include <Geom_Pnt2d.hxx>
#include <FvBC_Physics.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvEntity_Node2d;
		class FvEntity_Face2d;

		class FvEntity_Element2d
		{

		private:

			Standard_Integer theIndex_;

			Standard_Real theVolume_;

			FvBC_Physics thePhysics_;

			Geom_Pnt2d theCentre_;

		public:

			void SetIndex(const Standard_Integer theValue);

			void SetVolume(const Standard_Real theValue);

			void SetPhysics(const FvBC_Physics thePhysics);

			void SetCentre(const Geom_Pnt2d& theCentre);

			Standard_Integer Index() const;

			Standard_Real Volume() const;

			FvBC_Physics Physics() const;

			const Geom_Pnt2d& Centre() const;

			virtual Standard_Integer NbNodes() const = 0;

			virtual Standard_Integer NbFaces() const = 0;

			virtual void SetFace(const Standard_Integer theIndex, const Global_Handle(FvEntity_Face2d) theFace) = 0;

			virtual const Global_Handle(FvEntity_Node2d) Node(const Standard_Integer theIndex) const = 0;

			virtual const Global_Handle(FvEntity_Face2d) Face(const Standard_Integer theIndex) const = 0;

			virtual const Global_Handle(FvEntity_Element2d) Neighbor(const Standard_Integer theIndex) const = 0;

		protected:

			FvEntity_Element2d();

			FvEntity_Element2d(const Standard_Integer theIndex);
		};
	}
}

#include <FvEntity_Element2dI.hxx>

#endif // !_FvEntity_Element2d_Header
