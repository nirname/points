#ifndef DECLARATIONS_H
#define DECLARATIONS_H 1


//#define MAPPING(_ValueType) std::map<KeyType, _ValueType>

namespace lib {
	//template <typename Type> class List;
}

template<typename Type> class Mapping;

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
	typedef Mapping< Animation > AnimationMapping;
	//typedef std::map< KeyType, AnimationPointer > AnimationMap;
	//typedef AnimationMap::iterator AnimationMapIterator;
}

typedef graphics::Color Color;

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
	struct ControlHandler;

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
	typedef Mapping< ControlHandler  >   ControlsMapping;

	typedef std::map< Object *, Point > ObjectInformation;
	typedef std::map< Point, Object * > PointInformation;

	typedef ObjectInformation::iterator ObjectInformationIterator;
	typedef PointInformation::iterator PointInformationIterator;

	enum INTERACTION_TYPE {
		NO_INTERACTION,
		PUSH_INTERACTION,
		PULL_INTERACTION,
		DESTROY_INTERACTION,
		CREATE_INTERACTION
	};

	INTERACTION_TYPE get_interaction_type(std::string const & interaction_type_name) {
		if(interaction_type_name == "push") return PUSH_INTERACTION;
		if(interaction_type_name == "pull") return PULL_INTERACTION;
		if(interaction_type_name == "destroy") return DESTROY_INTERACTION;
		if(interaction_type_name == "create") return CREATE_INTERACTION;
		return NO_INTERACTION;
	}

	std::ostream & operator << (std::ostream & _ostream, const INTERACTION_TYPE & interaction) {
		std::string interaction_name;
		switch(interaction) {
			case NO_INTERACTION:      interaction_name = "no interaction"; break;
			case PUSH_INTERACTION:    interaction_name = "push";           break;
			case PULL_INTERACTION:    interaction_name = "pull";           break;
			case DESTROY_INTERACTION: interaction_name = "destroy";        break;
			case CREATE_INTERACTION:  interaction_name = "create";         break;
		}
		_ostream << interaction_name;
		return _ostream;
	}

	typedef std::pair< ObjectKindPointer, ObjectKindPointer > PairOfKinds;
	typedef std::map< PairOfKinds, INTERACTION_TYPE > InteractionMap;
	typedef InteractionMap::iterator InteractionMapIterator;

	typedef std::list <Level> LevelList;
	typedef LevelList::iterator LevelListIterator;


	void operator >> (const YAML::Node & options, ObjectKind &);

}

extern engine::Screen screen;
extern engine::Game game;

#endif
