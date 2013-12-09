/*
 * Windows BMP file definitions for OpenGL.
 *
 * Written by Michael Sweet.
 */

#ifndef _BITMAP_H_
#  define _BITMAP_H_

/*
 * Include necessary headers.
 */

#  include <GL/glut.h>
#  ifdef WIN32
#    include <windows.h>
#    include <wingdi.h>
#  endif /* WIN32 */

/*
 * Make this header file work with C and C++ source code...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * Bitmap file data structures (these are defined in <wingdi.h> under
 * Windows...)
 *
 * Note that most Windows compilers will pack the following structures, so
 * when reading them under MacOS or UNIX we need to read individual fields
 * to avoid differences in alignment...
 */

#  ifndef WIN32
typedef struct                       /**** BMP file header structure ****/
    {
    unsigned short bfType;           /* Magic number for file */
    unsigned int   bfSize;           /* Size of file */
    unsigned short bfReserved1;      /* Reserved */
    unsigned short bfReserved2;      /* ... */
    unsigned int   bfOffBits;        /* Offset to bitmap data */
    } BITMAPFILEHEADER;

#  define BF_TYPE 0x4D42             /* "MB" */

typedef struct                       /**** BMP file info structure ****/
    {
    unsigned int   biSize;           /* Size of info header */
    int            biWidth;          /* Width of image */
    int            biHeight;         /* Height of image */
    unsigned short biPlanes;         /* Number of color planes */
    unsigned short biBitCount;       /* Number of bits per pixel */
    unsigned int   biCompression;    /* Type of compression to use */
    unsigned int   biSizeImage;      /* Size of image data */
    int            biXPelsPerMeter;  /* X pixels per meter */
    int            biYPelsPerMeter;  /* Y pixels per meter */
    unsigned int   biClrUsed;        /* Number of colors used */
    unsigned int   biClrImportant;   /* Number of important colors */
    } BITMAPINFOHEADER;

/*
 * Constants for the biCompression field...
 */

#  define BI_RGB       0             /* No compression - straight BGR data */
#  define BI_RLE8      1             /* 8-bit run-length compression */
#  define BI_RLE4      2             /* 4-bit run-length compression */
#  define BI_BITFIELDS 3             /* RGB bitmap with RGB masks */

typedef struct                       /**** Colormap entry structure ****/
    {
    unsigned char  rgbBlue;          /* Blue value */
    unsigned char  rgbGreen;         /* Green value */
    unsigned char  rgbRed;           /* Red value */
    unsigned char  rgbReserved;      /* Reserved */
    } RGBQUAD;

typedef struct                       /**** Bitmap information structure ****/
    {
    BITMAPINFOHEADER bmiHeader;      /* Image header */
    RGBQUAD          bmiColors[256]; /* Image colormap */
    } BITMAPINFO;
#  endif /* !WIN32 */

/*
 * Prototypes...
 */

extern GLubyte *LoadDIBitmap(const char *filename, BITMAPINFO **info);
extern int     SaveDIBitmap(const char *filename, BITMAPINFO *info,
                            GLubyte *bits);

#  ifdef __cplusplus
}
#  endif /* __cplusplus */


static unsigned short     /* O - 16-bit unsigned integer */
read_word(FILE *fp)       /* I - File to read from */
    {
    unsigned char b0, b1; /* Bytes from file */

    b0 = getc(fp);
    b1 = getc(fp);

    return ((b1 << 8) | b0);
    }


/*
 * 'read_dword()' - Read a 32-bit unsigned integer.
 */

static unsigned int               /* O - 32-bit unsigned integer */
read_dword(FILE *fp)              /* I - File to read from */
    {
    unsigned char b0, b1, b2, b3; /* Bytes from file */

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
    }


/*
 * 'read_long()' - Read a 32-bit signed integer.
 */

static int                        /* O - 32-bit signed integer */
read_long(FILE *fp)               /* I - File to read from */
    {
    unsigned char b0, b1, b2, b3; /* Bytes from file */

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}


	GLubyte *                          // O - Bitmap data
	LoadDIBitmap(const char *filename, // I - File to load
						BITMAPINFO *info)    // O - Bitmap information
	{
		FILE             *fp;          // Open file pointer
		GLubyte          *bits;        // Bitmap pixel bits
		GLubyte          *ptr;         // Pointer into bitmap
		GLubyte          temp;         // Temporary variable to swap red and blue
		int              x, y;         // X and Y position in image
		int              length;       // Line length
		int              bitsize;      // Size of bitmap
		int              infosize;     // Size of header information
		BITMAPFILEHEADER header;       // File header


		// Try opening the file; use "rb" mode to read this *binary* file.
		if ((fp = fopen(filename, "rb")) == NULL) {
			return NULL;
		}

		// Read the file header and any following bitmap information...
		header.bfType      = read_word(fp);
		header.bfSize      = read_dword(fp);
		header.bfReserved1 = read_word(fp);
		header.bfReserved2 = read_word(fp);
		header.bfOffBits   = read_dword(fp);


		if (header.bfType != BF_TYPE) // Check for BM reversed...
		{
			// Not a bitmap file - return NULL...
			fclose(fp);
			return (NULL);
		}

		infosize = header.bfOffBits - 18;
		info = new BITMAPINFO;
		//if ((*info = (BITMAPINFO *)malloc(sizeof(BITMAPINFO))) == NULL) {
		if (info == NULL) {
			// Couldn't allocate memory for bitmap info - return NULL...
			fclose(fp);
			return (NULL);
		}

    /*(*info)->bmiHeader.biSize          = read_dword(fp);
    (*info)->bmiHeader.biWidth         = read_long(fp);
    (*info)->bmiHeader.biHeight        = read_long(fp);
    (*info)->bmiHeader.biPlanes        = read_word(fp);
    (*info)->bmiHeader.biBitCount      = read_word(fp);
    (*info)->bmiHeader.biCompression   = read_dword(fp);
    (*info)->bmiHeader.biSizeImage     = read_dword(fp);
    (*info)->bmiHeader.biXPelsPerMeter = read_long(fp);
    (*info)->bmiHeader.biYPelsPerMeter = read_long(fp);
    (*info)->bmiHeader.biClrUsed       = read_dword(fp);
    (*info)->bmiHeader.biClrImportant  = read_dword(fp);

    if (infosize > 40)
	if (fread((*info)->bmiColors, infosize - 40, 1, fp) < 1)
            {
            // Couldn't read the bitmap header - return NULL...
            free(*info);
            fclose(fp);
            return (NULL);
            }

    // Now that we have all the header info read in, allocate memory for
    // the bitmap and read *it* in...
    if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
        bitsize = ((*info)->bmiHeader.biWidth *
                   (*info)->bmiHeader.biBitCount + 7) / 8 *
  	           abs((*info)->bmiHeader.biHeight);

    //if ((bits = malloc(bitsize)) == NULL)
     //   {
     //   // Couldn't allocate memory - return NULL!
     //   free(*info);
     //   fclose(fp);
     //   return (NULL);
     //   }

    if (fread(bits, 1, bitsize, fp) < bitsize)
        {
        // Couldn't read bitmap - free memory and return NULL!
        free(*info);
        free(bits);
        fclose(fp);
        return (NULL);
        }

    // Swap red and blue
    length = ((*info)->bmiHeader.biWidth * 3 + 3) & ~3;
    for (y = 0; y < (*info)->bmiHeader.biHeight; y ++)
        for (ptr = bits + y * length, x = (*info)->bmiHeader.biWidth;
             x > 0;
		   x --, ptr += 3)
		  {
		  temp   = ptr[0];
		  ptr[0] = ptr[2];
		  ptr[2] = temp;
		  }

    // OK, everything went fine - return the allocated bitmap...
    fclose(fp);
    return (bits);
    /**/
    return NULL;
}



unsigned char * readBMP(char * filename, int & _width, int & _height)
{
	FILE * f = fopen(filename, "rb");

	if(f == 0) {
		std::cout << "can't open file '" << filename << "'" << std::endl;
		return NULL;
	}

	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	// extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];

	_width = width;
	_height = height;

	int size = 3 * width * height;
	unsigned char * data = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	/*for(int i = 0; i < size; i += 3) {
		unsigned char tmp = data[i];
		data[i] = data[i+2];
		data[i+2] = tmp;
	}*/

	return data;
	//return NULL;
}

#endif /* !_BITMAP_H_ */
