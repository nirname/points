void data_test() {

	engine::Object o0, o1, o2, o3, o4;

	o0.mask.insert(engine::Point(0, 1));
	o0.mask.insert(engine::Point(0, 2));
	o0.mask.insert(engine::Point(1, 2));

	o2.mask.insert(engine::Point(1, 0));
	o2.mask.insert(engine::Point(0, 1));
	o2.mask.insert(engine::Point(1, 1));

	test::Data d;

	d.add_object(&o0, engine::Point(1, 1));
	d.add_object(&o1, engine::Point(0, 3));
	d.add_object(&o1, engine::Point(4, 4));
	d.add_object(&o2, engine::Point(7, 5));
	d.add_object(&o3, engine::Point(1, 3));
	d.remove_object(&o1);
	d.add_object(&o4, engine::Point(4, 4));
	d.add_object(&o4, engine::Point(8, 9));
	d.add_object(&o2, engine::Point(0, 3));
	std::cout << d << std::endl;

}
