#pragma once
#ifndef _Cad3d_PairedOnSolid_Header
#define _Cad3d_PairedOnSolid_Header

#include <Global_Memory.hxx>
#include <Standard_Stream.hxx>
#include <Cad3d_EntityOnSolid.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_PolyLine3d;
	}

	namespace CadLib
	{

		class Cad3d_EdgeOnSolid;

		class Cad3d_PairedOnSolid : public Cad3d_EntityOnSolid
		{

		private:

			const Global_Handle(Cad3d_EdgeOnSolid) theEdge0_;
			const Global_Handle(Cad3d_EdgeOnSolid) theEdge1_;

			Global_Handle(GeoLib::Entity_PolyLine3d) theDiscretized_;

		public:

			Cad3d_PairedOnSolid();

			Cad3d_PairedOnSolid(const Standard_Integer Index, const Global_Handle(Cad3d_EdgeOnSolid) Edge0, const Global_Handle(Cad3d_EdgeOnSolid) Edge1);

			virtual ~Cad3d_PairedOnSolid();

			void Init(const Standard_Integer Index, const Global_Handle(Cad3d_EdgeOnSolid) Edge0, const Global_Handle(Cad3d_EdgeOnSolid) Edge1);

			void SetEdge0(const Global_Handle(Cad3d_EdgeOnSolid) Edge);

			void SetEdge1(const Global_Handle(Cad3d_EdgeOnSolid) Edge);

			void Discrete(const Standard_Real Deflection);

			Standard_Boolean IsPaired() const;

			const Global_Handle(Cad3d_EdgeOnSolid) Edge0() const;

			const Global_Handle(Cad3d_EdgeOnSolid) Edge1() const;

			void ExportToPlt(fstream& File) const;

		private:

			void Clear();
		};
	}
}

#include <Cad3d_PairedOnSolidI.hxx>

#endif // !_Cad3d_PairedOnSolid_Header
