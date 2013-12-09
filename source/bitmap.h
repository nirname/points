#ifndef WIN32

#define BYTE    unsigned char
#define WORD    unsigned short
#define DWORD   unsigned long

#define BF_TYPE 0x4D42 // "MB"

#pragma pack(push, 1)

struct BITMAPFILEHEADER // BMP file header structure
{

	unsigned short bfType;           // Magic number for file
	unsigned int   bfSize;           // Size of file
	unsigned short bfReserved1;      // Reserved
	unsigned short bfReserved2;      // ...
	unsigned int   bfOffBits;        // Offset to bitmap data

};

struct BITMAPINFOHEADER                       // BMP file info structure
{
	unsigned int   biSize;           // Size of info header
	int            biWidth;          // Width of image
	int            biHeight;         // Height of image
	unsigned short biPlanes;         // Number of color planes
	unsigned short biBitCount;       // Number of bits per pixel
	unsigned int   biCompression;    // Type of compression to use
	unsigned int   biSizeImage;      // Size of image data
	int            biXPelsPerMeter;  // X pixels per meter
	int            biYPelsPerMeter;  // Y pixels per meter
	unsigned int   biClrUsed;        // Number of colors used
	unsigned int   biClrImportant;   // Number of important colors*/
};

struct RGBQUAD                    // Colormap entry structure
{
	unsigned char  rgbBlue;          // Blue value
	unsigned char  rgbGreen;         // Green value
	unsigned char  rgbRed;           // Red value
	unsigned char  rgbReserved;      // Reserved
};

struct BITMAPINFO                      // Bitmap information structure
{
	BITMAPINFOHEADER bmiHeader;      // Image header
	RGBQUAD          bmiColors[256]; // Image colormap
};

#pragma pack(pop)

// Constants for the biCompression field...

#define BI_RGB       0             // No compression - straight BGR data
#define BI_RLE8      1             // 8-bit run-length compression
#define BI_RLE4      2             // 4-bit run-length compression
#define BI_BITFIELDS 3             // RGB bitmap with RGB masks

#endif // !WIN32

typedef unsigned char UINT8;

UINT8 * load_bmp() {

	std::cout << "bmp loading ..." << std::endl;

	BITMAPFILEHEADER bmp_header; // Header
	BITMAPINFOHEADER bmp_info;   // Info

	UINT8 * pixels = NULL; // Pixels

	std::ifstream file("../images/patterns/ornament/test.bmp", std::ios::binary);
	if(!file.is_open()) {
		return NULL;
	}

	file.read((char *)&bmp_header, sizeof(BITMAPFILEHEADER));
	file.read((char *)&bmp_info, sizeof(BITMAPINFOHEADER));

	// Check if the file is an actual BMP file
	if(bmp_header.bfType != BF_TYPE) {
		return NULL;
	}

	int width  = bmp_info.biWidth;
	int height = bmp_info.biHeight;
	//unsigned int size = bmp_info.biSizeImage;
	int size   = width * height * 3;

	std::cout << "BMP width: " << width << ", height: " << height << ", size: " << size << std::endl;
	std::cout << "bfOffBits: " << bmp_header.bfOffBits << std::endl;

	pixels = new UINT8[size];

	// Go to where image data starts, then read in image data
	//file.seekg(bmp_header.bfOffBits);
	file.read((char *)pixels, size);

	/*UINT8 tmpRGB = 0; // Swap buffer
	for (int i = 0; i < size; i += 3)
	{
		tmpRGB        = pixels[i];
		pixels[i]     = pixels[i + 2];
		pixels[i + 2] = tmpRGB;
	}*/

	int c = 0;
	for(int i = c; i < size; i++) {
		std::cout << "("
			<< (int)pixels[i*3] << ", "
			<< (int)pixels[i*3 + 1] << ", "
			<< (int)pixels[i*3 + 2] << ") ";
	}
	// Set width and height to the values loaded from the file

	/*for(int j = 0; j < height; j++) {
		//int j = 8;
		for(int i = 0; i < width; i++) {
			glPushAttrib(GL_CURRENT_BIT);
				glColor3ub((GLubyte)pixels[j * width + i], (GLubyte)pixels[j * width + i + 1], (GLubyte)pixels[j * width + i + 2]);
				glPushMatrix();
					glTranslatef(i, j, 0);
					graphics::square();
				glPopMatrix();
			glPopAttrib();
		}
	}*/

	delete [] pixels;

	return NULL;



}

#pragma pack(push, 2)

void readBMP()
{
	FILE * f = fopen((char *)"../images/patterns/ornament/test.bmp", "rb");

	if(f == 0) {
		std::cout << "can't open file '" << std::endl;
		return;
	}

	const int header_size = 54;
	unsigned char info[header_size];
	fread(info, sizeof(unsigned char), header_size, f); // read the 54-byte header

	// extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];

	const int q = 3;
	int size = width * height * q;

	unsigned char * data = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	for(int i = 0; i < size; i += q) {
		unsigned char tmp = data[i];
		data[i] = data[i+2];
		data[i+2] = tmp;
	}

	for(int j = 0; j < height; j++) {
		for(int i = 0; i < width; i++) {
			std::cout << "("
				<< (int)data[j * width + i] << ", "
				<< (int)data[j * width + i + 1] << ", "
				<< (int)data[j * width + i + 2] << ") ";
			/*glPushAttrib(GL_CURRENT_BIT);
				glColor3ub((GLubyte)data[j * width + i], (GLubyte)data[j * width + i + 1], (GLubyte)data[j * width + i + 2]);
				glPushMatrix();
					glTranslatef(i, j, 0);
					graphics::square();
				glPopMatrix();
			glPopAttrib();*/
		}
	}/**/
	std::cout << std::endl;

	delete [] data;
	//return data;
	//return NULL;
}

#pragma pack(pop)
