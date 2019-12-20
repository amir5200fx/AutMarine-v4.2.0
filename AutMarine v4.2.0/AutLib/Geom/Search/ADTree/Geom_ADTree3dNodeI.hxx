#pragma once
template<typename T>
inline AutLib::GeoLib::Geom_ADTree3dNode<T>::Geom_ADTree3dNode
(
	const T & Item,
	const Entity_Box3d & Region, 
	const Standard_Integer Level,
	Geom_ADTree3dNode<T>* Left, 
	Geom_ADTree3dNode<T>* Right
)
	: Data_(Item)
	, Region_(Region)
	, Level_(Level)
	, Left_(Left)
	, Right_(Right)
{
}