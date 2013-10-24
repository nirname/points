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
