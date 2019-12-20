#include <Mesh2d_Plane.hxx>

#include <Mesh2d_SizeMap.hxx>
#include <Mesh2d_Domain.hxx>

AutLib::MeshLib::Mesh2d_Plane::Mesh2d_Plane()
	: theCurrent_(0)
	, AutomaticReleaseMemory_(Standard_True)
{
}

AutLib::MeshLib::Mesh2d_Plane::~Mesh2d_Plane()
{
	FreeMemory(theDomains_);
	if (AutomaticReleaseMemory_) { ReleaseMemory(); }
}

void AutLib::MeshLib::Mesh2d_Plane::LaplacianSmoothing
(
	Standard_Real(*Distance)(const Geom_Pnt2d &, const Geom_Pnt2d &, const Mesh2d_SizeMap&),
	const Mesh2d_SizeMap& Map,
	const Standard_Boolean Verbose
)
{
	Get_Object(Mesh) = *CurrentMesh();

	Mesh.LaplacianSmoothing
	(
		theSmoothing_.MaxLevels(),
		theSmoothing_.UnderRelaxation(),
		Distance,
		Map,
		Verbose
	);
}

void AutLib::MeshLib::Mesh2d_Plane::AllocateMemory(const Standard_Integer N)
{
	theMeshes_.Resize(N);
	theDomains_.Resize(N);

	forThose(Index, 0, MaxIndexOf(theDomains_))
		theDomains_[Index] = new Mesh2d_Domain;
}

void AutLib::MeshLib::Mesh2d_Plane::ReleaseMemory()
{
	forThose(Index, 0, MaxIndexOf(theMeshes_))
	{
		theMeshes_[Index]->ReleaseMemory();

		FreePointer(theMeshes_[Index]);
	}
}

void AutLib::MeshLib::Mesh2d_Plane::SetManualReleaseMemory()
{
	AutomaticReleaseMemory_ = Standard_False;
}

void AutLib::MeshLib::Mesh2d_Plane::ExportToPlt(fstream & File) const
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theMeshes_)
	)
	{
		Try_Exception_Handle_Exit(theMeshes_[Index]->ExportElementsToPlt(File));
	}
}

void AutLib::MeshLib::Mesh2d_Plane::ExportQualityToPlt
(
	fstream & File,
	const Mesh2d_SizeMap& theSizeMap
) const
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theMeshes_)
	)
	{
		theMeshes_[Index]->ExportQualityToPlt(File, theSizeMap);
	}
}

void AutLib::MeshLib::Mesh2d_Plane::ReportQualityTo
(
	Standard_OStream& Ostream,
	const Mesh2d_SizeMap& theSizeMap
) const
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theMeshes_)
	)
	{
		theMeshes_[Index]->ReportQualityTo(Ostream, theSizeMap);
	}
}