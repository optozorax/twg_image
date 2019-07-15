#include <EasyBMP.h>
#include <twg/image.h>
#include <twg/color.h>

#include <stb_image.h>
#include <stb_image_write.h>

#include <gif.h>

#include <cassert>

namespace twg
{

//-----------------------------------------------------------------------------
ImageBase::ImageBase(Point_i sz) {
	m_assigned = nullptr;
	m_buf = nullptr;
	resize(sz);
}

//-----------------------------------------------------------------------------
ImageBase::ImageBase(const ImageBase& img) {
	m_assigned = nullptr;
	m_buf = nullptr;
	resize(img.size());
	img.copyTo(this, Point_i(0, 0), Point_i(0, 0), img.size());
}

//-----------------------------------------------------------------------------
ImageBase::~ImageBase() {
	if (m_assigned == nullptr)
		delete[] m_buf;
}

//-----------------------------------------------------------------------------
void ImageBase::assign(ImageBase* img) {
    if (m_assigned == nullptr)
        delete[] m_buf;

	m_assigned = img;
	m_buf = img->m_buf;
	m_width = img->m_width;
	m_height = img->m_height;
}

//-----------------------------------------------------------------------------
void ImageBase::resize(Point_i newSize) {
	if (m_assigned != nullptr) {
		m_assigned->resize(newSize);
		m_buf = m_assigned->m_buf;
		m_width = m_assigned->m_width;
		m_height = m_assigned->m_height;
	} else {
        m_width = newSize.x;
        m_height = newSize.y;

        if (m_buf != nullptr) {
            delete[] m_buf;
            m_buf = nullptr;
        }
		m_buf = new Color[newSize.x * newSize.y];
	}
}

//-----------------------------------------------------------------------------
void ImageBase::clear(Color bk) {
	for (int32u i = 0; i < m_width*m_height; ++i)
		m_buf[i] = bk;
}

//-----------------------------------------------------------------------------
void ImageBase::copyTo(ImageBase *dst, 
                     Point_i dstStart,  
                     Point_i srcStart,
                     Point_i srcSize) const {
	assert(dst->width() == width());
	assert(dst->height() == height());
	assert(dstStart.x == 0 && dstStart.y == 0);
	assert(srcStart.x == 0 && srcStart.y == 0);
	assert(srcSize.x == width() && srcSize.y == height());
	for (int32u i = 0; i < m_width*m_height; ++i)
		dst->m_buf[i] = m_buf[i];
}

//-----------------------------------------------------------------------------
void ImageBase::drawTo(ImageBase* dst, 
                     Point_i dstStart,
                     Point_i srcStart,
                     Point_i srcSize,
                     Point_i dstSize) const {
	assert(dst->width() == width());
	assert(dst->height() == height());
	assert(dstStart.x == 0 && dstStart.y == 0);
	assert(srcStart.x == 0 && srcStart.y == 0);
	assert(srcSize.x == width() && srcSize.y == height());
	for (int32u i = 0; i < m_width*m_height; ++i)
		dst->m_buf[i] = computeOverlay(m_buf[i], dst->m_buf[i]);
}

//-----------------------------------------------------------------------------
void loadFromBmp(ImageBase* img, std::string fileName) {
	BMP AnImage;
	AnImage.ReadFromFile(wstr2str(fileName).c_str());

	img->resize(Point_i(AnImage.TellWidth(), AnImage.TellHeight()));

	if (AnImage.TellBitDepth() <= 24) {
		AnImage.SetBitDepth(32);
		for (size_t i = 0; i < AnImage.TellWidth(); i++) {
			for (size_t j = 0; j < AnImage.TellHeight(); j++) {
				RGBApixel pix = AnImage.GetPixel(i, j);
				pix.Alpha = 255;

				(*img)[Point_i(i, j)] = rgb(pix.Red, pix.Green, pix.Blue);
			}
		}
	} else {
		for (size_t i = 0; i < AnImage.TellWidth(); i++) {
			for (size_t j = 0; j < AnImage.TellHeight(); j++) {
				RGBApixel pix = AnImage.GetPixel(i, j);

				(*img)[Point_i(i, j)] = rgba(pix.Red, pix.Green, pix.Blue, pix.Alpha);
			}
		}
	}
}

//-----------------------------------------------------------------------------
void saveToBmp(ImageBase* img, std::string fileName, bool is32bitBmp) {
	if (is32bitBmp) {
		BMP AnImage;
		AnImage.SetBitDepth(32);
		AnImage.SetSize(img->width(), img->height());

		RGBApixel pix;
		for (size_t i = 0; i < AnImage.TellWidth(); i++) {
			for (size_t j = 0; j < AnImage.TellHeight(); j++) {
				Color mypix = (*img)[Point_i(i,j)];

				pix.Alpha = getAlpha(mypix);
				pix.Blue = getBlue(mypix);
				pix.Red = getRed(mypix);
				pix.Green = getGreen(mypix);

				AnImage.SetPixel(i, j, pix);
			}
		}

		AnImage.WriteToFile(wstr2str(fileName).c_str());
	} else {
		BMP AnImage;
		AnImage.SetSize(img->width(), img->height());

		RGBApixel pix;
		for (size_t i = 0; i < AnImage.TellWidth(); i++) {
			for (size_t j = 0; j < AnImage.TellHeight(); j++) {
				Color mypix = (*img)[Point_i(i,j)];

				pix.Blue = getBlue(mypix);
				pix.Red = getRed(mypix);
				pix.Green = getGreen(mypix);

				AnImage.SetPixel(i, j, pix);
			}
		}

		AnImage.WriteToFile(wstr2str(fileName).c_str());
	}
}

//-----------------------------------------------------------------------------
void loadFromPngJpg(ImageBase* img, std::string fileName) {
	unsigned char *data;
	int width, height, n;
	data = stbi_load(wstr2str(fileName).c_str(), &width, &height, &n, 4);
	img->resize({width, height});
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			(*img)[Point_i(j, i)] = rgba(
				data[4*(i * width + j)+0],
				data[4*(i * width + j)+1], 
				data[4*(i * width + j)+2],
				data[4*(i * width + j)+3]
			);
		}
	}
	free(data);
}

//-----------------------------------------------------------------------------
void saveToPng(ImageBase* img, std::string fileName, bool is32bitPng) {
	unsigned char *data = new unsigned char[img->width() * img->height() * 4];
	for (int i = 0; i < img->height(); i++) {
		for (int j = 0; j < img->width(); j++) {
			int offset = 4*(i * img->width() + j);
			auto clr = (*img)[Point_i(j, i)];
			data[offset + 0] = getRed(clr);
			data[offset + 1] = getGreen(clr);
			data[offset + 2] = getBlue(clr);
			data[offset + 3] = getAlpha(clr);
		}
	}
	stbi_write_png_compression_level = 1;
	stbi_write_png(wstr2str(fileName).c_str(), img->width(), img->height(), 4, data, img->width() * 4);
	delete[] data;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void ImageGif::start(Point_i size, const std::string& filename) {
	writer = new GifWriter;
	img2 = new uint32_t[size.x * size.y];
	GifBegin((GifWriter*)(writer), filename.c_str(), size.x, size.y, 3);
	width = size.x;
	height = size.y;
}

//-----------------------------------------------------------------------------
void ImageGif::process(const ImageBase& img, int delay_ms) {
	if (img.width() != width || img.height() != height)
		throw std::exception();

	for (uint32_t x = 0; x < width * height; ++x) {
		Color color = img.buf()[x];
		img2[x] = rgb(getBlue(color), getGreen(color), getRed(color));
	}

	GifWriteFrame((GifWriter*)(writer), (uint8_t*)img2, width, height, delay_ms, 8);
}

//-----------------------------------------------------------------------------
void ImageGif::end(void) {
	GifEnd((GifWriter*)(writer));
	delete writer;
	delete[] img2;
}

}