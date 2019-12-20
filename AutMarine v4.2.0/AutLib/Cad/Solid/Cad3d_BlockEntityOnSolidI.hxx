#pragma once
inline
Standard_String AutLib::CadLib::Cad3d_BlockEntityOnSolid::Name() const
{
	return theName_;
}

inline
Standard_Integer AutLib::CadLib::Cad3d_BlockEntityOnSolid::Size() const
{
	return (Standard_Integer)theEntities_.size();
}

inline
void AutLib::CadLib::Cad3d_BlockEntityOnSolid::UnSelectAll() const
{
	theSelected_.Clear();
}

inline
void AutLib::CadLib::Cad3d_BlockEntityOnSolid::RetrieveTo(TColCad3d_HAry1dOfEntityOnSolid & Entities) const
{
	TColCad3d_HBasicQueueOfEntityOnSolid QEntity;
	RetrieveTo(QEntity);

	QEntity.RetrieveTo(Entities);
}