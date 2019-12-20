#include <Ship_XParameters.hxx>

#include <Ship_ConstParameters.hxx>
#include <IO_Tecplot.hxx>

#define Plot_XParameter_TecPlot(VariableName, XParameter, FileStream)  \
   IoLib::IO_TecPlot::Export_I_Ordered(XCoords(), XParameter, "X "##VariableName, VariableName, FileStream);

AutLib::CadLib::Ship_XParameters::Ship_XParameters()
{
}

void AutLib::CadLib::Ship_XParameters::ExportYCoordsToTecPlot(fstream & File) const
{
	Plot_XParameter_TecPlot
	(
		"YCoords",
		YCoords(),
		File
	);
}

void AutLib::CadLib::Ship_XParameters::ExportZCoordsToTecPlot(fstream & File) const
{
	Plot_XParameter_TecPlot
	(
		"ZCoords",
		ZCoords(),
		File
	);
}

void AutLib::CadLib::Ship_XParameters::ExportDepthToTecPlot(fstream & File) const
{
	Plot_XParameter_TecPlot
	(
		"Depth",
		Depth(),
		File
	);
}

void AutLib::CadLib::Ship_XParameters::ExportSheerToTecPlot(fstream & File) const
{
	Plot_XParameter_TecPlot
	(
		"Sheer",
		Sheer(),
		File
	);
}

void AutLib::CadLib::Ship_XParameters::ExportTightnessToTecPlot(fstream & File) const
{
	Plot_XParameter_TecPlot
	(
		"Tightness",
		Tightness(),
		File
	);
}

void AutLib::CadLib::Ship_XParameters::ExportFlareToTecPlot(fstream & File) const
{
	Plot_XParameter_TecPlot
	(
		"Flare",
		Flare(),
		File
	);
}

void AutLib::CadLib::Ship_XParameters::ExportDeadRiseToTecPlot(fstream & File) const
{
	Plot_XParameter_TecPlot
	(
		"DeadRise",
		DeadRise(),
		File
	);
}

void AutLib::CadLib::Ship_XParameters::ExportSideSlopeToTecPlot(fstream & File) const
{
	Plot_XParameter_TecPlot
	(
		"SideSlope",
		SideSlope(),
		File
	);
}

void AutLib::CadLib::Ship_XParameters::ExportSkegToTecPlot(fstream & File) const
{
	Plot_XParameter_TecPlot
	(
		"Skeg",
		Skeg(),
		File
	);
}

void AutLib::CadLib::Ship_XParameters::ExportRakeToTecPlot(fstream & File) const
{
	Plot_XParameter_TecPlot
	(
		"Rake",
		Rake(),
		File
	);
}

void AutLib::CadLib::Ship_XParameters::AllocateMemory(const Standard_Integer nbSections)
{
	IF_NOT_INSIDE
	(
		nbSections,
		Ship_ConstParameters::MinNbSections(),
		Ship_ConstParameters::MaxNbSections()
	)
	{
		THROW_STANDARD_EXCEPTION(" Invalid Nb of Sections");
	}

	xXCoords_.Resize(nbSections);
	xYCoords_.Resize(nbSections);
	xZCoords_.Resize(nbSections);

	xDepth_.Resize(nbSections);
	xSheer_.Resize(nbSections);

	xTightness_.Resize(nbSections);
	xFlare_.Resize(nbSections);
	xDeadRise_.Resize(nbSections);
	xSideSlope_.Resize(nbSections);
	xSideSlopeAngle_.Resize(nbSections);
	xSkeg_.Resize(nbSections);

	xRake_.Resize(nbSections);
}