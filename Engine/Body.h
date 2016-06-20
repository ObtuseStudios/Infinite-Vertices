//Copyright 2016, Cameron bell, All rights reserved

#pragma once

namespace Penguin
{
	enum Type
	{
		Rigid, Static
	};
		
	enum Collider
	{
		Box, Circle, None
	};

	struct Body
	{
		Collider ObjCollider;
		Type ObjType;

		Body(Collider bod = Collider::Box, Type ty = Type::Static)
			: ObjCollider(bod), ObjType(ty) { }		
	};
}