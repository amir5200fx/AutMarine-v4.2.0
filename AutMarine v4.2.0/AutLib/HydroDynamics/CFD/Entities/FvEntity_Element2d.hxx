#pragma once
#ifndef _FvEntity_Element2d_Header
#define _FvEntity_Element2d_Header

#include <Global_Memory.hxx>
#include <FvPrimitives_Label.hxx>
#include <FvPrimitives_Scalar.hxx>
#include <Geom_Pnt2d.hxx>
#include <FvBC_Physics.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvEntity_Node2d;
		class FvEntity_Face2d;
		class FvEntity_Element2d;

		class FvEntity_Element2d
		{

		private:

			Label theIndex_;

			Scalar theVolume_;

			FvBC_Physics thePhysics_;

			Geom_Pnt2d theCentre_;

		public:

			void SetIndex(const Label theIndex);

			void SetVolume(const Scalar theValue);

			void SetPhysics(const FvBC_Physics thePhysics);

			void SetCentre(const Geom_Pnt2d& theCoord);

			Label Index() const;

			Scalar Volume() const;

			FvBC_Physics Physics() const;

			const Geom_Pnt2d& Centre() const;

			virtual Label NbNodes() const = 0;

			virtual Label NbFaces() const = 0;

			virtual void SetFace(const Label theIndex, const Global_Handle(FvEntity_Face2d) theFace) = 0;

			virtual const Global_Handle(FvEntity_Node2d) Node(const Label theIndex) const = 0;

			virtual const Global_Handle(FvEntity_Face2d) Face(const Label theIndex) const = 0;

			virtual const Global_Handle(FvEntity_Element2d) Neighbor(const Label theIndex) const = 0;

			
		protected:

			FvEntity_Element2d();

			FvEntity_Element2d(const Label theIndex);
		};

		typedef FvEntity_Element2d FvEntity_Element2d;
	}
}

#include <FvEntity_Element2dI.hxx>

using AutLib::FvLib::FvEntity_Element2d;

#endif // !_FvEntity_Element2d_Header
