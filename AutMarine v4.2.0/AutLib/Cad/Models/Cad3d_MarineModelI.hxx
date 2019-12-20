#pragma once
inline
Standard_Boolean AutLib::CadLib::Cad3d_MarineModel::IsDone() const
{
	return IsDone_;
}

inline 
const M_GEO Entity_Box3d & AutLib::CadLib::Cad3d_MarineModel::BoundingBox() const
{
	return theBox_;
}

inline 
const gp_Ax2 & AutLib::CadLib::Cad3d_MarineModel::CoordinateSystem() const
{
	return theSystem_;
}

inline 
const TopoDS_Shape & AutLib::CadLib::Cad3d_MarineModel::Shape() const
{
	return myModel_;
}

inline
const Standard_String & AutLib::CadLib::Cad3d_MarineModel::Name() const
{
	return theName_;
}

inline 
const Standard_String & AutLib::CadLib::Cad3d_MarineModel::IGESFileName() const
{
	return theIgesFileName_;
}