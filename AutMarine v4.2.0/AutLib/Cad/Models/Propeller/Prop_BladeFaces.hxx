#pragma once
#ifndef _Prop_BladeFaces_Header
#define _Prop_BladeFaces_Header

#include <Standard_Handle.hxx>
#include <Standard_Stream.hxx>

class Geom_Surface;

namespace AutLib
{
	namespace CadLib
	{

		class Prop_BladeFaces
		{

		private:

			Handle(Geom_Surface) theFace_;
			Handle(Geom_Surface) theBack_;

		public:

			Prop_BladeFaces();

			Prop_BladeFaces(const Handle(Geom_Surface)& theFace, const Handle(Geom_Surface)& theBack);

			void Init(const Handle(Geom_Surface)& theFace, const Handle(Geom_Surface)& theBack);

			void SetFace(const Handle(Geom_Surface)& theFace);

			void SetBack(const Handle(Geom_Surface)& theBack);

			const Handle(Geom_Surface)& Face() const;

			const Handle(Geom_Surface)& Back() const;

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <Prop_BladeFacesI.hxx>

#endif // !_Prop_BladeFaces_Header
