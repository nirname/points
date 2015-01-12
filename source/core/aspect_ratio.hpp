#pragma once

/// Relation between screen sides
///
struct AspectRatio {

	/// Long side
	unsigned int width;
	/// Short size
	unsigned int height;

	/// Default constructor
	AspectRatio();
	/// Creating aspect ratio by long and short sides
	AspectRatio(unsigned int _width, unsigned int _height);

	/// Relation between long side and short side
	float aspect() const;
};
