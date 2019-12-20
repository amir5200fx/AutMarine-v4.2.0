#pragma once
#ifndef _SizeMap3d_BoundarySizeMapTool_Header
#define _SizeMap3d_BoundarySizeMapTool_Header

#include <SizeMap3d_SizeMapTool.hxx>
#include <TColStd_BasicQueueOfString.hxx>
#include <TColStd_Ary1dOfString.hxx>
#include <TColCad3d_HAry1dOfEntityOnSolid.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap3d_BoundarySizeMapTool : public SizeMap3d_SizeMapTool
		{

		protected:

			TColStd_BasicQueueOfString theEntityPatches_;

		public:

			virtual ~SizeMap3d_BoundarySizeMapTool();

			Standard_Integer NbEntityPatches() const;

			Standard_Boolean RemoveEntityPatch(const Standard_String PatchName);

			void ImportEntityPatch(const Standard_String PatchName);

			void RetrieveEntityPatchesTo(TColStd_Ary1dOfString& Patches) const;

			virtual void RetrieveEntitiesTo(TColCad3d_HAry1dOfEntityOnSolid& theEntities) const;

		protected:

			SizeMap3d_BoundarySizeMapTool(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad3d_Solid) theSolid);
		};
	}
}

#include <SizeMap3d_BoundarySizeMapToolI.hxx>

#endif // !_SizeMap3d_BoundarySizeMapTool_Header
