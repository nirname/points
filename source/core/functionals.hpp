#pragma once

template<typename ObjectType, typename FunctionType, typename ArgumentType>
struct binder {

	ObjectType object;
	FunctionType function;

	binder(ObjectType _object, FunctionType _function):
		object(_object), function(_function)
	{}

	int operator () (ArgumentType arg) {
		return (object->*function)(arg);
	}

};

template<typename ArgumentType, typename ObjectType, typename FunctionType>
binder<ObjectType, FunctionType, ArgumentType>
bind(ObjectType _object, FunctionType _function) {
	return binder<ObjectType, FunctionType, ArgumentType>(_object, _function);
}
