#pragma once
#ifndef _Prop_BladeSection_Header
#define _Prop_BladeSection_Header

#include <Standard_Handle.hxx>
#include <Standard_Stream.hxx>

class Geom2d_Curve;

namespace AutLib
{
	namespace CadLib
	{

		class Prop_BladeSection
		{

		private:

			Handle(Geom2d_Curve) theFace_;
			Handle(Geom2d_Curve) theBack_;

		public:

			Prop_BladeSection();

			Prop_BladeSection(const Handle(Geom2d_Curve)& theFace, const Handle(Geom2d_Curve)& theBack);

			void Init(const Handle(Geom2d_Curve)& theFace, const Handle(Geom2d_Curve)& theBack);

			void SetFace(const Handle(Geom2d_Curve)& theFace);

			void SetBack(const Handle(Geom2d_Curve)& theBack);

			const Handle(Geom2d_Curve)& Face() const;

			const Handle(Geom2d_Curve)& Back() const;

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <Prop_BladeSectionI.hxx>

#endif // !_Prop_BladeSection_Header
