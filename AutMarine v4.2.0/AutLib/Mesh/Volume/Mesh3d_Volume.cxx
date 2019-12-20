#include <Mesh3d_Volume.hxx>

#include <QualityMap2d_Vlrms2Ratio.hxx>
#include <Mesh3d_SolidMesher.hxx>
#include <Mesh3d_TMesh.hxx>

AutLib::MeshLib::Mesh3d_Volume::Mesh3d_Volume()
	: theCurrent_(0)
{
}

AutLib::MeshLib::Mesh3d_Volume::~Mesh3d_Volume()
{
}

void AutLib::MeshLib::Mesh3d_Volume::AllocateMemory(const Standard_Integer N)
{
	theMeshes_.Resize(N);
	theDomains_.Resize(N);

	theMeshes_.Init(0);
	theDomains_.Init(0);

	/*forThose(Index, 0, MaxIndexOf(theDomains_))
		theDomains_[Index] = new Mesh3d_SolidMesher;*/

	forThose(Index, 0, MaxIndexOf(theMeshes_))
		theMeshes_[Index] = new Mesh3d_TMesh;
}

void AutLib::MeshLib::Mesh3d_Volume::ExportCavitiesToPlt(fstream & File) const
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theMeshes_)
	)
	{
		Debug_Null_Pointer(theMeshes_[Index]);

		TColMesh3d_HAry1dOfFacet Facets;
		theMeshes_[Index]->RetrieveFrontsTo(Facets);

		if (Facets.IsEmpty()) continue;

		theMeshes_[Index]->ExportFacetsToPlt(Facets, File);
	}
}

void AutLib::MeshLib::Mesh3d_Volume::ExportToPlt(fstream & File) const
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theMeshes_)
	)
	{
		Debug_Null_Pointer(theMeshes_[Index]);

		Try_Exception_Handle_Exit(theMeshes_[Index]->ExportElementsToPlt(File));
	}
}

void AutLib::MeshLib::Mesh3d_Volume::ExportDomainToPlt(fstream & File) const
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theDomains_)
	)
	{
		if (theDomains_[Index])
		{
			theDomains_[Index]->ExportMergedMeshToPlt(File);
		}
	}
}

void AutLib::MeshLib::Mesh3d_Volume::ExportIndependentPatchesToPlt(fstream & File) const
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theDomains_)
	)
	{
		if (theDomains_[Index])
		{
			theDomains_[Index]->ExportMeshToPlt(File);
		}
	}
}

void AutLib::MeshLib::Mesh3d_Volume::ExportQualityToPlt(fstream & File, const QualityMap3d_TypesInfo theQualityType) const
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theMeshes_)
	)
	{
		Debug_Null_Pointer(theMeshes_[Index]);

		theMeshes_[Index]->ExportQualityToPlt(File, theQualityType);
	}
}

void AutLib::MeshLib::Mesh3d_Volume::ExportBoundaryQualityMeshToPlt(fstream & File) const
{
	QualityMap2d_Vlrms2Ratio QualityMap;
	forThose
	(
		Index,
		0,
		MaxIndexOf(theDomains_)
	)
	{
		if (theDomains_[Index])
		{
			theDomains_[Index]->ExportQualityMeshToPlt(File, QualityMap);
		}
	}
}

void AutLib::MeshLib::Mesh3d_Volume::ReportQuality
( 
	const QualityMap3d_TypesInfo theQualityType,
	Standard_OStream & Ostream
) const
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theMeshes_)
	)
	{
		Debug_Null_Pointer(theMeshes_[Index]);

		theMeshes_[Index]->ReportQuality(Ostream, theQualityType);
	}
}

void AutLib::MeshLib::Mesh3d_Volume::ReleaseMemory()
{
	forThose
	(
		Index,
		0, 
		MaxIndexOf(theMeshes_)
	)
	{
		theMeshes_[Index]->ReleaseMemory();
		FreePointer(theMeshes_[Index]);

		FreePointer(theDomains_[Index]);
	}
}