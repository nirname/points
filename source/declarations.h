#ifndef DECLARATIONS_H
#define DECLARATIONS_H 1


// make types.h without namespace
typedef unsigned int positive;
typedef std::string KeyType;

template<typename Type> struct Mapping {

	typedef Type * TypePointer;
	typedef std::map<KeyType, TypePointer> Container;

	Container container;

	Mapping() {}

	~Mapping() {
		for(typename Container::iterator i = container.begin(); i != container.end(); ++i) {
			delete i->second;
		}
	}

	TypePointer get(std::string _name) {
		TypePointer result = NULL;
		if(container.find(_name) != container.end()) {
			result = container[_name];
		}
		return result;
	}

	TypePointer add(std::string _name) {
		TypePointer result = get(_name);
		if(result == NULL) {
			result = new Type();
			container[_name] = result;
		}
		return result;
	}

};

#define MAPPING(_ValueType) std::map<KeyType, _ValueType>

//typename std::map Mapping;
/*template<typename T>
struct At
{
	typedef typename A<T, true> Type;
};

template<typename T>
struct Af
{
	typedef typename A<T, false> Type;
};

Af<int>::Type foo;
At<float>::Type bar;*/


namespace lib {
	//template <typename Type> class List;
}

namespace image {
	void redisplay(int);
}

namespace graphics {
	void square();
	struct Color;
	struct Shape;

	typedef Color * ColorPointer;
	typedef Shape * ShapePointer;

	struct Animation;
	typedef Animation * AnimationPointer;
	typedef std::map< KeyType, AnimationPointer > AnimationMap;
	typedef AnimationMap::iterator AnimationMapIterator;
}

namespace engine {

	struct Screen;
	struct Level;
	struct Game;
	struct Field;
	struct View;
	struct Object;
	struct Point;
	struct Size;
	struct ObjectKind;

	typedef Field  * FieldPointer;
	typedef View   * ViewPointer;
	typedef Object * ObjectPointer;
	typedef Point  * PointPointer;
	typedef ObjectKind * ObjectKindPointer;

	typedef Mapping< Field           >      FieldMapping;
	typedef Mapping< View            >       ViewMapping;
	typedef Mapping< ObjectKind      > ObjectKindMapping;
	typedef Mapping< Object          >     ObjectMapping;
	typedef Mapping< graphics::Color >      ColorMapping;
	typedef Mapping< graphics::Shape >      ShapeMapping;

	typedef MAPPING( FieldPointer           ) FieldMap;
	typedef MAPPING( ViewPointer            ) ViewMap;
	typedef MAPPING( ObjectKindPointer      ) ObjectKindMap;
	typedef MAPPING( ObjectPointer          ) ObjectMap;
	typedef MAPPING( graphics::ColorPointer ) ColorMap;
	typedef MAPPING( graphics::ShapePointer ) ShapeMap;

	typedef      FieldMap *      FieldMapPointer;
	typedef       ViewMap *       ViewMapPointer;
	typedef ObjectKindMap * ObjectKindMapPointer;
	typedef     ObjectMap *     ObjectMapPointer;
	typedef      ColorMap *      ColorMapPointer;
	typedef      ShapeMap *      ShapeMapPointer;

	/*typedef Mapping< graphics::ColorPointer >::Type ColorMap;
	typedef Mapping< graphics::ShapePointer >::Type ShapeMap;*/

	typedef std::map< Object *, Point > ObjectInformation;
	typedef std::map< Point, Object * > PointInformation;

	typedef ObjectInformation::iterator ObjectInformationIterator;
	typedef PointInformation::iterator PointInformationIterator;

	enum INTERACTION_TYPE {
		PUSH_INTERACTION,
		PULL_INTERACTION,
		DESTROY_INTERACTION,
		CREATE_INTERACTION
	};

	typedef std::pair< ObjectKindPointer, ObjectKindPointer > PairOfKinds;
	typedef std::map< PairOfKinds, INTERACTION_TYPE > InteractionMap;
	typedef InteractionMap::iterator InteractionMapIterator;

	typedef std::list <Level> LevelList;
	typedef LevelList::iterator LevelListIterator;

}

extern engine::Screen screen;
extern engine::Game game;

#endif
