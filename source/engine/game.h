#ifndef GAME_H
#define GAME_H 1

namespace engine {

	// !!! move this to level class
	bool has_extension(const char * name, const char * extension)
	{
		size_t name_length = lib::strlen(name);
		size_t extension_length = lib::strlen(extension);
		return
			name_length > extension_length &&
			strcmp(
				name + (name_length - extension_length) * sizeof(char),
				extension
			) == 0;
	}

	// Describes current game
	struct Game {

		//logic::GAME_KIND game_kind;
		bool paused;

		//LevelListIterator current_level;
		//LevelList levels;
		//LevelMapping levels;

		FieldMapping      fields;
		ViewMapping       views;
		ColorMapping      colors;
		ShapeMapping      shapes;
		ObjectKindMapping object_kinds;
		ObjectMapping     objects;
		graphics::AnimationMapping animations;
		Mapping<ControlHandler> controls;
		std::list<ControlHandler> actions;

		InteractionMap interactions;

		//Game() {}

		Game(bool _paused = false):
			paused(_paused)
		{}
		//Game(){};

		/*Game(logic::GAME_KIND _game_kind):
			game_kind(_game_kind), paused(false)
		{
			//current_level = levels.begin();
		}*/

		void print() {
			std::cout << "Object kinds:\n" << object_kinds << std::endl;
			std::cout << "Interactions:\n";
			for(InteractionMapIterator i = interactions.begin(); i != interactions.end(); ++i) {
				std::cout << i->first.first << " can " << i->second << " " << i->first.second << std::endl;
			}
			std::cout << std::endl;
			std::cout << "Objects:\n" << objects << std::endl;
			std::cout << "Fields:\n" << fields << std::endl;
			std::cout << "Views:\n" << views << std::endl;
			std::cout << "Colors:\n" << colors << std::endl;
			std::cout << "Shapes:\n" << shapes << std::endl;
			std::cout << "Animations:\n" << animations << std::endl;
			std::cout << "Controls:\n" << controls << std::endl;

		}

		/*void load_interactions(const YAML::Node &);
		void load_objects(const YAML::Node &);
		void load_default_colors();
		void load_default_shapes();*/

		// !!! move this functions to loader file and to level class

		void load_interactions(const YAML::Node & level) {
			const YAML::Node & interactions_node = level["interactions"];
			if(interactions_node) {
				if(interactions_node.IsMap()) {
					for(
						YAML::const_iterator
						interaction = interactions_node.begin();
						interaction != interactions_node.end();
						++interaction
					) {
						std::string first_object_kind_name = interaction->first.as<std::string>();
						//std::cout << "* " << first_object_kind_name << std::endl;
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
									//std::cout << "** " << action_name << std::endl;
									INTERACTION_TYPE interaction_type = get_interaction_type(action_name);
									if(interaction_type != NO_INTERACTION) {
										const YAML::Node& second_object_kinds = action->second;
										if(second_object_kinds.IsScalar()) {
											//std::cout << "Scalar!!!" << std::endl;
											std::string second_object_kind_name = second_object_kinds.as<std::string>();
											//std::cout << second_object_kind_name << std::endl;
											if(object_kinds.has(second_object_kind_name)) {
												ObjectKindPointer second_object_kind = object_kinds.get(second_object_kind_name);
												interactions[engine::PairOfKinds(first_object_kind, second_object_kind)] = interaction_type;
											} else {
												std::cout << "Can not find object kind `" << second_object_kind_name << "`" << std::endl;
											}
										}
										if(second_object_kinds.IsSequence()) {
											//std::cout << "Sequence!!!" << std::endl;
											for(
												YAML::const_iterator
												second_object_kind_iterator = second_object_kinds.begin();
												second_object_kind_iterator != second_object_kinds.end();
												++second_object_kind_iterator
											) {
												std::string second_object_kind_name = second_object_kind_iterator->as<std::string>();
												//std::cout << second_object_kind_name << std::endl;
												if(object_kinds.has(second_object_kind_name)) {
													ObjectKindPointer second_object_kind = object_kinds.get(second_object_kind_name);
													interactions[engine::PairOfKinds(first_object_kind, second_object_kind)] = interaction_type;
												} else {
													std::cout << "Can not find object kind `" << second_object_kind_name << "`" << std::endl;
												}
											}
										}
									} else {
										std::cout << "No interaction" << std::endl;
									}
								}
							} else {
								std::cout << "Actions should be a map" << std::endl;
							}
						} else {
							std::cout << "Can not find object kind `" << first_object_kind_name << "`" << std::endl;
						}
					}
				} else {
					std::cout << "Interaction should be a map" << std::endl;
				}
			}
		}

		// (!!!) use specialization for mapping operator >> and put this code there
		// drop this function and use load_attribute instead
		void load_objects(const YAML::Node & level) {
			const YAML::Node & objects_node = level["objects"];
			if(objects_node) {
				if(objects_node.IsMap()) {
					for(
						YAML::const_iterator
						object_kind_iterator = objects_node.begin();
						object_kind_iterator != objects_node.end();
						++object_kind_iterator
					) {
						std::string object_kind_name = object_kind_iterator->first.as<std::string>();
						if(object_kinds.has(object_kind_name)) {
							ObjectKindPointer object_kind = object_kinds.get(object_kind_name);
							const YAML::Node & object_names_node = object_kind_iterator->second;
							if(object_names_node.IsScalar()) {
								std::string object_name = object_names_node.as<std::string>();
								ObjectPointer object = objects.add(object_name);
								if(object != NULL) {
									object->kind = object_kind;
								}
								// use >> operator here
							}
							if(object_names_node.IsSequence()) {
								for(
									YAML::const_iterator
									object_iterator = object_names_node.begin();
									object_iterator != object_names_node.end();
									++object_iterator
								) {
									std::string object_name = object_iterator->as<std::string>();
									ObjectPointer object = objects.add(object_name);
									if(object != NULL) {
										object->kind = object_kind;
										//object->color
									}
								}
							}
						} else {
							std::cout << "No object kind" << std::endl;
						}
					}
				} else {
					std::cout << "Objects node should be a map" << std::endl;
				}
			}
		}

		template<typename Type> void load_attribute(Type & attribute, const YAML::Node & level, const char * key) {
			if(level[key]) {
				const YAML::Node & node = level[key];
				if(node.IsMap()) {
					for(YAML::const_iterator iterator = node.begin(); iterator != node.end(); ++iterator) {
						iterator >> attribute;
					}
				} else {
					std::cout << key << " should me a map" << std::endl;
				}
			} else {
				std::cout << "no " << key << " found" << std::endl;
			}
		}

		void load_default_colors() {
			colors.add(std::string("white"),  new graphics::Color(WHITE));
			colors.add(std::string("black"),  new graphics::Color(BLACK));
			colors.add(std::string("blue"),   new graphics::Color(BLUE));
			colors.add(std::string("yellow"), new graphics::Color(YELLOW));
			colors.add(std::string("green"),  new graphics::Color(GREEN));
			colors.add(std::string("red"),    new graphics::Color(RED));
			colors.add(std::string("azure"),  new graphics::Color(AZURE));
			colors.add(std::string("violet"), new graphics::Color(VIOLET));
			colors.add(std::string("gray"),   new graphics::Color(GRAY));
			colors.add(std::string("orange"), new graphics::Color(ORANGE));
		}

		void load_default_shapes() {
			shapes.add(std::string("square"), new graphics::Square());
			shapes.add(std::string("circle"), new graphics::Circle());
			shapes.add(std::string("david"),  new graphics::David());
			shapes.add(std::string("star"),   new graphics::Star());
			shapes.add(std::string("ring"),   new graphics::Ring());
			shapes.add(std::string("retro"),  new graphics::Retro());
		}

		bool load() {

			lib::stage("GAME LOADING\n");

			std::cout << "Searching for levels\n" << std::endl;
			DIR *dir;
			struct dirent * entry;
			if ((dir = opendir ("./levels/")) != NULL) {
				// print all the files and directories within directory
				while ((entry = readdir (dir)) != NULL) {
					if (entry->d_type == DT_REG && has_extension(entry->d_name, ".yaml")) { // DT DIR
						std::cout << "File: " << std::ends;
						/*printf("%zu - %s [%d] %d\n", entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen );*/
						printf("%s\n", entry->d_name);
					}
				}
				closedir(dir);
			} else {
				// could not open directory
				perror("");
				//return EXIT_FAILURE;
			}

			try {
				YAML::Node level = YAML::LoadFile("levels/level_1.yaml");
				if(level.IsMap()) {
					std::cout << "\nLoading level data\n" << std::endl;
					for(YAML::const_iterator block = level.begin(); block != level.end(); ++block) {
						std::cout << block->first.as<std::string>() << std::endl;
					}
					std::cout << std::endl;

					load_default_colors();
					load_attribute(colors, level, "colors");

					load_default_shapes();
					//load_attribute(shapes, level, "shapes");

					load_attribute(object_kinds, level, "object_kinds");

					// !!! refactor it too
					load_interactions(level);
					load_objects(level);

					load_attribute(fields, level, "fields");
					load_attribute(views, level, "views");
					load_attribute(controls, level, "controls");

				} else {
					std::cout << "Configuration file should contain mapping" << std::endl;
				}
			} catch (YAML::ParserException & exception) {
				std::cout << "I can not load level" << std::endl;
				return false;
			} catch (YAML::BadFile) {
				std::cout << "There is no level" << std::endl;
				return false;
			}

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
			lib::stage("GAME IS LOADED\n");
			print();

			/*if(current_level == levels.begin()) ++current_level;
			if(current_level != levels.end()) {
				current_level->load();
			} else {
				// game is over
			}*/
		}

		void display() {
			/*for(graphics::AnimationMapping::Iterator i = game.animations.begin(); i != game.animations.end(); ++i) {
				i->second->next();
			}*/

			glPushMatrix();
				for(ViewMapping::Iterator view = views.begin(); view != views.end(); ++view) {
					view->second->display();
				}
			glPopMatrix();
		}

	};


}

#endif
