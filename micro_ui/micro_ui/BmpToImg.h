#ifndef bmp_to_img_h__
#define bmp_to_img_h__

#include <vector>
#include "MicroUiTypes.h"
#include <string>
#include <stdio.h>
#include <wingdi.h>

namespace MicroUI {

	class Image16 {
	public:
		std::vector<Color16> pixels;
		size_t width;
		size_t height;
	};

	class BmpToImg {
	public:
		static Image16 load(const std::string& path) {
			Image16 result;
			FILE *filePtr; //our file pointer
			BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header
			BITMAPINFOHEADER bitmapInfoHeader;

			//open filename in read binary mode
			fopen_s(&filePtr, path.c_str(), "rb");
			if (filePtr == NULL)
				return result;

			//read the bitmap file header
			int read_cnt = fread(&bitmapFileHeader, 1, sizeof(BITMAPFILEHEADER), filePtr);

			printf("Size = %zi\n", sizeof(BITMAPFILEHEADER));

			//verify that this is a bmp file by check bitmap id
			if (bitmapFileHeader.bfType != 0x4D42) {
				fclose(filePtr);
				return result;
			}

			//read the bitmap info header
			fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

			//move file point to the begging of bitmap data
			fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

			auto pixel_data_size = bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight * (bitmapInfoHeader.biBitCount / 8);


			std::vector<uint8_t> data;
			data.resize(pixel_data_size);

			//read in the bitmap image data
			fread(&data[0], pixel_data_size, 1, filePtr);

		
			result.width = bitmapInfoHeader.biWidth;
			result.height = bitmapInfoHeader.biHeight;
			result.pixels.resize(result.width * result.height);

			auto bpp = bitmapInfoHeader.biBitCount / 8;

			for (int y = 0; y < result.height; ++y) {
				for (int x = 0; x < result.width; ++x) {


					uint8_t* ptr = &data[(y * result.width + x) * bpp];
					result.pixels[((result.height - 1 - y) * result.width + x)] = Color24(ptr[2], ptr[1], ptr[0]).asColor16();
				}
			}

			for (size_t i = 0; i < result.pixels.size(); ++i) {
				auto id = result.pixels.size() - 1 - i;
				
			}

			fclose(filePtr);
			return result;
		}
	};
}
#endif // bmp_to_img_h__
