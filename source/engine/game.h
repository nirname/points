#ifndef GAME_H
#define GAME_H 1

namespace engine {

	/*void check_node(YAML::Node * _node, const char _option[]) {
		std::cout << _option << ": ";
		if((*_node)[_option]) {
			std::cout << "true" << std::endl;
		} else {
			std::cout << "no" << std::endl;
		}
	}*/

	// Describes current game
	struct Game {

		logic::GAME_KIND game_kind;
		LevelListIterator current_level;
		//engine::Screen screen;
		bool paused;

		LevelList    levels;

		FieldMapping      fields;
		ViewMapping       views;
		ColorMapping      colors;
		ShapeMapping      shapes;
		ObjectKindMapping object_kinds;
		ObjectMapping     objects;
		graphics::AnimationMapping animations;


		//ViewMap       views;
		//ColorMap      colors; // !!! use opengl palette
		//ShapeMap      shapes;
		//ObjectKindMap object_kinds;
		//ObjectMap     objects;
		//graphics::AnimationMap animations;

		InteractionMap interactions;
		// Use unordered hash instead
		//PointMap points;

		Game(logic::GAME_KIND _game_kind):
			game_kind(_game_kind), paused(false)
		{
			current_level = levels.begin();
		}

		void print() {
			//std::cout << "----" << std::endl << "Game" << std::endl << "----" << std::endl;
			std::cout << "Object kinds:" << std::endl;
			for(ObjectKindMapping::Iterator i = object_kinds.begin(); i != object_kinds.end(); ++i) {
				std::cout << "  " << i->first << ": " << i->second << std::endl;
			}
			std::cout << "Objects:" << std::endl;
			for(ObjectMapping::Iterator i = objects.begin(); i != objects.end(); ++i) {
				std::cout << "  " << i->first << " (" << i->second->kind << "): " << *i->second << "(" << i->second << ")" << std::endl;
			}
			std::cout << "Fields:" << std::endl;
			for(FieldMapping::Iterator i = fields.begin(); i != fields.end(); ++i) {
				std::cout << "  " << i->first << ": " << i->second << std::endl;
			}
			std::cout << "Views:" << std::endl;
			for(ViewMapping::Iterator i = views.begin(); i != views.end(); ++i) {
				std::cout << "  " << i->first << ": " << i->second << std::endl;
			}
			std::cout << "Colors:" << std::endl;
			for(ColorMapping::Iterator i = colors.begin(); i != colors.end(); ++i) {
				std::cout << "  " << i->first << ": " << i->second << std::endl;
			}
			std::cout << "Shapes:" << std::endl;
			for(ShapeMapping::Iterator i = shapes.begin(); i != shapes.end(); ++i) {
				std::cout << "  " << i->first << ": " << i->second << std::endl;
			}
			/*for(graphics::AnimationMap::iterator i = animations.begin(); i != animations.end(); ++i) {
				std::cout << i->first << ": " << i->second << std::endl;
			}*/
		}
		/*std::ostream print << (std::ostream & _ostream, const Object & _object) {
			_ostream << "Object(" << _object.number << ")";
			return _ostream;
		}*/

		bool load() {

		lib::stage("GAME LOADING");
		/*if(config["lastLogin"])
		std::cout << "Last logged in: " << config["lastLogin"].as<DateTime>() << "\n";

		const std::string username = config["username"].as<std::string>();
		const std::string password = config["password"].as<std::string>();
		login(username, password);
		config["lastLogin"] = getCurrentDateTime();

		std::ofstream fout("config.yaml");
		fout << config;*/

			//std::ifstream level_data("levels/level_1.yaml");
			//YAML::Parser parser(level_data);

			/*std::string buffer;
			while(std::getline(level_data, buffer)) {
				std::cout << buffer << std::endl;
			}
			level_data.close();*/

			YAML::Node level = YAML::LoadFile("levels/level_1.yaml");
			if(level.IsMap()) {
				std::cout << "Loading level data\n" << std::endl;
				for(YAML::const_iterator block = level.begin(); block != level.end(); ++block) {
					std::cout << block->first.as<std::string>() << std::endl;
				}
				std::cout << "----------" << std::endl;
				const YAML::Node& object_kinds_node = level["object_kinds"];
				if(object_kinds_node) {
					if(object_kinds_node.IsMap()) {
						for(
							YAML::const_iterator
							object_kind = object_kinds_node.begin();
							object_kind != object_kinds_node.end();
							++object_kind
						) {
							//std::cout << object_kind->first.as<std::string>() << std::endl;
							object_kinds.add( object_kind->first.as<std::string>(), object_kind->second );
						}
					}
					//YAML::Node level_object_kinds = level["object_kinds"];
					/*for(YAML::const_iterator object_kind = level.begin(); block != level.end(); ++block) {
					std::cout << block->first.as<std::string>() << std::endl;*/
				}
				const YAML::Node& interactions_node = level["interactions"];
				if(interactions_node) {
					if(interactions_node.IsMap()) {
						for(
							YAML::const_iterator
							interaction = interactions_node.begin();
							interaction != interactions_node.end();
							++interaction
						) {
							std::string first_object_kind_name = interaction->first.as<std::string>();
							std::cout << "* " << first_object_kind_name << std::endl;
							if( object_kinds.has(first_object_kind_name) ) {
								ObjectKindPointer first_object_kind = object_kinds.get(first_object_kind_name);
								const YAML::Node& actions_node = interaction->second;
								if(actions_node.IsMap()) {
									for(
										YAML::const_iterator
										action = actions_node.begin();
										action != actions_node.end();
										++action
									) {
										std::string action_name = action->first.as<std::string>();
										std::cout << "** " << action_name << std::endl;
										INTERACTION_TYPE interaction_type = get_interaction_type(action_name);
										if(interaction_type != NO_INTERACTION) {
											const YAML::Node& second_object_kinds = action->second;
											if(second_object_kinds.IsScalar()) {
												std::cout << "Scalar!!!" << std::endl;
												std::string second_object_kind_name = second_object_kinds.as<std::string>();
												std::cout << second_object_kind_name << std::endl;
												if(object_kinds.has(second_object_kind_name)) {
													ObjectKindPointer second_object_kind = object_kinds.get(second_object_kind_name);

												}
											}
											if(second_object_kinds.IsSequence()) {
												std::cout << "Sequence!!!" << std::endl;
												for(
													YAML::const_iterator
													second_object_kind_name = second_object_kinds.begin();
													second_object_kind_name != second_object_kinds.end();
													++second_object_kind_name
												) {
													std::cout << second_object_kind_name->as<std::string>() << std::endl;
												}
											}
										}
									}
								} else {
									std::cout << "Actions should be a map" << std::endl;
								}
							} else {
									std::cout << "Can not find object kind" << std::endl;
							}
							/*if(interaction.IsMap()) {

							}*/

							//object_kinds.add( object_kind->first.as<std::string>(), object_kind->second );
							//interactions
						}
					} else {
						std::cout << "Interaction should be a map" << std::endl;
					}
					//YAML::Node level_object_kinds = level["object_kinds"];
					/*for(YAML::const_iterator object_kind = level.begin(); block != level.end(); ++block) {
					std::cout << block->first.as<std::string>() << std::endl;*/
				}

			} else {
				std::cout << "Configuration file should contain mapping" << std::endl;
			}
			//std::cout << level_config << std::endl;
			/*if(level.IsMap()) {
				check_node(&level, "kinds");
				check_node(&level, "objects");
				check_node(&level, "interactions");
				check_node(&level, "fields");
				check_node(&level, "views");
			} else {
				std::cout << "Configuration file should contain mapping" << std::endl;
			}*/



			//for(unsigned int i; i < _object_kinds.size(); i++) {
			//	std::cout << i << std::endl;
				//ObjectKindPointer object_kind = object_kinds.build();
				//std::string key, value;
				//object_kinds.add(lib::to_string(i), object_kind);
				//_object_kinds[i] >> *ok;
				//fields["Field"]->size = engine::Size(10, 10);
			//}
			//std::cout << (level_config["first"].as<std::string>()) << std::endl;

			/*YAML::Node node;
			while(parser.GetNextDocument(node)) {
			}*/

			/*DIR *dir;
			struct dirent *ent;
			if ((dir = opendir ("c:\\src\\")) != NULL) {
				// print all the files and directories within directory
				while ((ent = readdir (dir)) != NULL) {
					printf ("%s\n", ent->d_name);
				}
				closedir(dir);
			} else {
				// could not open directory
				perror("");
				return EXIT_FAILURE;
			}*/

			/*colors[std::string("Violet")] = new graphics::Color(VIOLET);
			colors[std::string("Blue")] = new graphics::Color(BLUE);
			colors[std::string("Green")] = new graphics::Color(GREEN);*/

			//graphics::Animation * animation = new graphics::Animation(graphics::SCALE_ANIMATION, graphics::DECREASE);
			//animation->do_after = move_up;
			//std::cout << "* progress: " << animation->progress << std::endl;
			//animations["Scale"] = animation;
			// move this logic to Level class
			//game.add_field("Field", 10, 10);
			//game.add_view("View", "Field");
			//std::cout << (engine::Point(0, 0) < engine::Point(0, 1)) << std::endl;
			//game.fields[std::string("Field")] = new engine::Field(10, 10);
			//fields["Field"] = new Field();
			//views["View"] = new engine::View(fields[std::string("Field")]);

			//const char * shape_names [2] = ["a", "b"];
			//engine::Object aaa();
			//engine::Object bbb(aaa);

			/*shapes[std::string("Square")] = new graphics::Square();
			shapes[std::string("Circle")] = new graphics::Circle();
			shapes[std::string("David")] = new graphics::David();/**/

			/*shapes[std::string("Star")] = new graphics::Star();
			shapes[std::string("Ring")] = new graphics::Ring();*/

			/*ObjectKind * sokoban = new ObjectKind();
			sokoban->shape = shapes[std::string("Star")];
			sokoban->color = colors[std::string("Violet")];
			object_kinds[std::string("Sokoban")] = sokoban;
			ObjectKind * box = new ObjectKind();
			box->color = colors[std::string("Green")];
			object_kinds[std::string("Box")] = box;
			ObjectKind * heavy = new ObjectKind();
			heavy->color = colors[std::string("Blue")];
			object_kinds[std::string("Heavy")] = heavy;*/

			/*interactions[engine::PairOfKinds(sokoban, box)]   = engine::PUSH_INTERACTION;
			interactions[engine::PairOfKinds(sokoban, heavy)] = engine::PUSH_INTERACTION;
			interactions[engine::PairOfKinds(heavy, box)]     = engine::PUSH_INTERACTION;*/

			//Object * box1 = new engine::Object(box);
			//box1->kind = object_kinds[std::string("Box")];
			//objects[std::string("Box1")] = box1;
			//engine::Object * heavy1 = new engine::Object(heavy);
			//heavy1->kind = object_kinds[std::string("Heavy")];
			//objects[std::string("Heavy")] = heavy1;
			//game.objects[std::string("Box2")] = new engine::Object();
			/*game.objects[std::string("Box1")]->type = std::string("Box");
			game.objects[std::string("Box2")]->type = std::string("Box");*/

			/*engine::Object * sokoban1 = new engine::Object();
			sokoban1->kind = object_kinds[std::string("Sokoban")];
			//sokoban->animations.push_back(animation);
			objects[std::string("Sokoban")] = sokoban1;

			fields[std::string("Field")]->data.add(objects[std::string("Sokoban")], engine::Point(1, 1));
			fields[std::string("Field")]->data.add(objects[std::string("Box1")], engine::Point(5, 5));
			//fields[std::string("Field")]->data.add(objects[std::string("Box2")], engine::Point(6, 5));
			fields[std::string("Field")]->data.add(objects[std::string("Heavy")], engine::Point(4, 3));*/

			/*---------------------------------------------------------------
			colors.add("Violet");
			colors["Violet"]->set(VIOLET);
			fields.add("Field");
			fields["Field"]->size = engine::Size(10, 10);

			views.add("View");
			views["View"]->field    = fields["Field"];
			views["View"]->size     = engine::Size(12, 12);
			views["View"]->offset   = engine::Point(-1, -1);
			views["View"]->position = engine::Point(3, 3);

			object_kinds.add("Sokoban");
			object_kinds["Sokoban"]->color = colors["Violet"];

			objects.add("Fred");
			objects["Fred"]->kind = object_kinds["Sokoban"];

			fields["Field"]->data.add(objects["Fred"], engine::Point(1, 1));
			------------------------------------------------------------------*/

			//std::cout << objects["Fred"] << std::endl;
			//->data.add(objects["Fred"], engine::Point(1, 1));

			//game.points[ engine::Placement(game.objects[std::string("Sokoban")], game.fields[std::string("Field")]) ] = new engine::Point(1, 1);
			//game.points[ engine::Placement(game.objects[std::string("Box1")], game.fields[std::string("Field")]) ] = new engine::Point(2, 2);
			//game.points[ engine::Placement(game.objects[std::string("Box2")], game.fields[std::string("Field")]) ] = new engine::Point(3, 3);

			/*for(engine::PointMap::iterator i = game.points.begin(); i != game.points.end(); ++i) {
				std::cout << *(i->first.object) << " at " << *(i->first.field) << " : ";
				if(i->second != NULL) {
					std::cout << *(i->second) << std::endl;
				} else {
					std::cout << "no position" << std::endl;
				}
			}
			std::cout << std::ends;*/
			std::cout << "\nGame data\n"<< std::endl;
			print();

			//std::count << (&(game.points[ engine::Placement(game.objects[std::string("Sokoban")], game.fields[std::string("Field")]) ]) == NULL);

			/*if(current_level == levels.begin()) ++current_level;
			if(current_level != levels.end()) {
				current_level->load();
			} else {
				// game is over
			}*/
		}

		/*#define GET_COMPONENT(_Type, _component)\
		_Type##Pointer get_##_component(std::string _name) {\
			_Type##Pointer result = NULL;\
			if(_component##s.find(_name) != _component##s.end()) {\
				result = _component##s[_name];\
			}\
			return result;\
		}

		#define ADD_COMPONENT(_Type, _component)\
		_Type##Pointer add_##_component(std::string _name) {\
			_Type##Pointer result = NULL;\
			if(_get_##_component != NULL) {\
				result = new _Type();\
				_component##s[_name] = result;\
			}\
			return result;\
		}

		GET_COMPONENT(Field,  field);
		GET_COMPONENT(View,   view);
		GET_COMPONENT(Object, object);

		GET_COMPONENT(graphics::Color, color);
		GET_COMPONENT(graphics::Shape, shape);
		*/

		/*FieldPointer get_field(std::string _name) {
			FieldPointer result = NULL;
			if(fields.find(_name) != fields.end()) {
				result = fields[_name];
			}
			return result;
		}

		FieldPointer add_field(std::string _name) {
			FieldPointer result = NULL;
			if(get_field(_name) != NULL) {
				result = new Field();
				fields[_name] = result;
			}
			return result;
		}*/

		//template<typename Type, Game::*component> get

		/*void remove_field(std::string _name) {
			FieldPointer field = get_field(_name);
			if(field != NULL) {
				delete field;
			}
			fields.erase(_name);
		}*/


//< KeyType, _ResultType >

		/*template<typename ResultType> ResultType get(std::string _name, typename Mapping<ResultType>::Pointer _component) {
			ResultType result;
			if(_component != NULL) { // make fetch
				if(_component->find(_name) != _component->end()) {
					result = (*_component)[_name];
				}
			}
			return result;
		}*/

		/*FieldPointer get_field(std::string _name) {
			return get<FieldPointer>(_name, &fields);
		}*/

		/*FieldPointer add_field(std::string _name) { }*/

		// make this one private
		//std::map<KeyType, ResultType> *
		//(typename Mapping<ResultType>::Pointer)
		/*template<typename ResultType> struct Component {
			typedef typename Mapping<ResultType>::Pointer ResultTypeMappingPointer;
			template<ResultType> static ResultTypeMappingPointer get() {
				// throw an exception here!!! unknown component!
				return NULL;
			}
		};*/

		/*template<typename ResultTypePointer>
		MAPPING(ResultTypePointer) * component_by_type() {
			// throw an exception here!!! unknown component!
			return NULL;
		}

		template<typename ResultTypePointer>
		ResultTypePointer fetch(std::string name, MAPPING(ResultTypePointer) * component) {
			ResultTypePointer result;
			if(component->find(name) != component->end()) {
				result = (*component)[name];
			}
			return result;
		}

		template<typename ResultTyper>
		ResultType * get(std::string name) {
			typedef ResultType * ResultTypePointer;
			MAPPING(ResultTypePointer) * component = component_by_type<ResultTypePointer>();
			ResultTypePointer result;
			if(component != NULL) {
				result = fetch<ResultTypePointer>(name, component);
			}
			return result;
		}

		template<typename ResultType>
		ResultType * add(std::string name) {
			typedef ResultType * ResultTypePointer;
			MAPPING(ResultTypePointer) * component = component_by_type<ResultTypePointer>();
			ResultTypePointer result;
			if(component != NULL) {
				result = fetch<ResultTypePointer>(name, component);
				if(result == NULL) {
					component[name] = new ResultType();
				}
			}
			//typename Mapping<ResultType>::Pointer component = component_by_type<ResultType>();
			return result;
		}*/

	};

	/*template<> FieldMapPointer Game::Component<FieldMapPointer>::get() {
		return & fields;
	}*/

	/*mplate<> FieldMapPointer Game::component_by_type () {
		return & fields;
	}
	template<> ViewMapPointer Game::component_by_type () {
		return & views;
	}
	template<> ObjectMapPointer Game::component_by_type () {
		return & objects;
	}
	template<> ColorMapPointer Game::component_by_type () {
		return & colors;
	}
	template<> ShapeMapPointer Game::component_by_type () {
		return & shapes;
	}
	template<> ObjectKindMapPointer Game::component_by_type() {
		return & object_kinds;
	}*/

	/*#
	define _FIELD_COMPONENT_ACCESSOR(TYPE) 1
	*/

}

#endif
