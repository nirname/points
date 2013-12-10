#ifndef GAME_H
#define GAME_H 1

namespace engine {

	// Describes current game
	struct Game {

		//logic::GAME_KIND game_kind;
		bool paused;
		bool loaded;

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

		Game() : paused(false), loaded(false) {}

		/*Game(bool _paused = false):
			paused(_paused)
		{
			loaded = false;
		}*/
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

		// TODO move this functions to loader file and to level class

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
									INTERACTION_TYPE interaction_type = get_interaction_type(action_name);
									if(interaction_type != NO_INTERACTION) {
										const YAML::Node& second_object_kinds = action->second;
										if(second_object_kinds.IsScalar()) {
											std::string second_object_kind_name = second_object_kinds.as<std::string>();
											if(object_kinds.has(second_object_kind_name)) {
												ObjectKindPointer second_object_kind = object_kinds.get(second_object_kind_name);
												interactions[engine::PairOfKinds(first_object_kind, second_object_kind)] = interaction_type;
											} else {
												std::cout << "Can not find object kind `" << second_object_kind_name << "`" << std::endl;
											}
										}
										if(second_object_kinds.IsSequence()) {
											for(
												YAML::const_iterator
												second_object_kind_iterator = second_object_kinds.begin();
												second_object_kind_iterator != second_object_kinds.end();
												++second_object_kind_iterator
											) {
												std::string second_object_kind_name = second_object_kind_iterator->as<std::string>();
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

		// (TODO) use specialization for mapping operator >> and put this code there
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

			// TODO: load list of levels here

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

					// TODO refactor it too
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

			lib::stage("GAME IS LOADED\n");
			print();

			/*if(current_level == levels.begin()) ++current_level;
			if(current_level != levels.end()) {
				current_level->load();
			} else {
				// game is over
			}*/
			loaded = true;

		}

		void pause() {
			paused = true;
		}

		void resume() {
			paused = false;
		}

		void process(unsigned char key) {
			/*if(key == 'p') {
				paused = !paused;
				if(paused) {
					std::cout << ": game is paused; press `p` to resume";
				}
				else {
					std::cout << ": game is resumed; press `p` to pause again";
					glutTimerFunc(0, image::redisplay, 0);
				}
			}*/
			if(!paused) {
				engine::Point position;
				engine::Point offset;
				std::string string_key = lib::to_string(key);
				if(controls.has(string_key)) {
					controls[string_key]->evaluate();
				} else {
					std::cout << ": free";
				}
				//graphics::ANIMATION_TYPE animation_type = graphics::NO_ANIMATION;
				//glutPostRedisplay();
			}
			//std::cout << std::endl;


			/*if(!paused) {
				engine::Field * field = fields[std::string("Field")];
				engine::Object * sokoban = objects[std::string("Sokoban")];
				switch(key)
				{
					case GLUT_KEY_UP:    step = engine::Point( 0,  1); break;
					case GLUT_KEY_DOWN:  step = engine::Point( 0, -1); break;
					case GLUT_KEY_LEFT:  step = engine::Point(-1,  0); break;
					case GLUT_KEY_RIGHT: step = engine::Point( 1,  0); break;
				}
				//animations["Scale"]->do_after = move_sokoban;
				//animations["Scale"]->start();
				//, animations[std::string("Scale")]
				//sokoban->move(field, step);
				//sokoban->move(field, step);
				//std::cout << "Key: " << key << std::endl;
				//glutPostRedisplay();
				printf("%i", key);
				std::cout << std::endl;
			}*/

		}

		void display() {
			/*for(graphics::AnimationMapping::Iterator i = animations.begin(); i != animations.end(); ++i) {
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
