#pragma once
template<typename T>
inline AutLib::GeoLib::Geom_ADTree2dNode<T>::Geom_ADTree2dNode
(
	const T & Item,
	const Entity_Box2d & Region,
	const Standard_Integer Level,
	Geom_ADTree2dNode<T>* Left,
	Geom_ADTree2dNode<T>* Right
)
	: Data_(Item)
	, Region_(Region)
	, Level_(Level)
	, Left_(Left)
	, Right_(Right)
{
}