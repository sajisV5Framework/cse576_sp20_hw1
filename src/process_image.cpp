#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>

#include "image.h"

using namespace std;

// HW0 #3
// const Image& im: input image
// return the corresponding grayscale image
Image rgb_to_grayscale(const Image& im)
  {
	  assert(im.c == 3); // only accept RGB images
	  Image gray(im.w,im.h,1); // create a new grayscale image (note: 1 channel)
  
	  // TODO: calculate the pixels of 'gray'
	  for (int q2 = 0; q2 < im.h; q2++)
		  for (int q1 = 0; q1 < im.w; q1++)
		  {
			  gray(q1, q2) = 0.299f * im(q1, q2, 0) + 0.587f * im(q1, q2, 1) + 0.114f * im(q1, q2, 2);
		  }
  
	  //NOT_IMPLEMENTED();
  
	  return gray;
  }



// Example function that changes the color of a grayscale image
Image grayscale_to_rgb(const Image& im, float r, float g, float b)
  {
	  assert(im.c == 1);
	  Image rgb(im.w,im.h,3);
  
	  for(int q2=0;q2<im.h;q2++)
		  for(int q1=0;q1<im.w;q1++)
			{
				rgb(q1,q2,0)=r*im(q1,q2);
				rgb(q1,q2,1)=g*im(q1,q2);
				rgb(q1,q2,2)=b*im(q1,q2);
			}
  
	  return rgb;
  }




// HW0 #4
// Image& im: input image to be modified in-place
// int c: which channel to shift
// float v: how much to shift
void shift_image(Image& im, int c, float v)
  {
	  assert(c>=0 && c<im.c); // needs to be a valid channel
  
	  // TODO: shift all the pixels at the specified channel
	  for (int q2 = 0; q2 < im.h; q2++)
		  for (int q1 = 0; q1 < im.w; q1++)
			  im(q1, q2,c) = im(q1, q2,c) + v;				  
		  
	  //NOT_IMPLEMENTED();  
  }

// HW0 #8
// Image& im: input image to be modified in-place
// int c: which channel to scale
// float v: how much to scale
void scale_image(Image& im, int c, float v)
  {
  assert(c>=0 && c<im.c); // needs to be a valid channel
  
  // TODO: scale all the pixels at the specified channel
  
  NOT_IMPLEMENTED();
  
  }


// HW0 #5
// Image& im: input image to be modified in-place
void clamp_image(Image& im)
  {
	// TODO: clamp all the pixels in all channel to be between 0 and 1
	for (int q2 = 0; q2 < im.h; q2++)
		for (int q1 = 0; q1 < im.w; q1++)
			for (int c = 0; c < im.c; c++)
			{
				if (im(q1, q2, c) > 1.f) im(q1, q2, c) = 1.f;
				if (im(q1, q2, c) < 0.f) im(q1, q2, c) = 0.f;
			}  
  //NOT_IMPLEMENTED();  
  }

// These might be handy
float max(float a, float b, float c)
  {
	return max({a,b,c});
  }

float min(float a, float b, float c)
  {
	return min({a,b,c});
  }


// HW0 #6
// Image& im: input image to be modified in-place
void rgb_to_hsv(Image& im)
  {
	assert(im.c==3 && "only works for 3-channels images");
  
	// TODO: Convert all pixels from RGB format to HSV format
	for (int q2 = 0; q2 < im.h; q2++)
		for (int q1 = 0; q1 < im.w; q1++)
		{
			float R = im(q1, q2, 0); // red channel
			float G = im(q1, q2, 1); // green channel
			float B = im(q1, q2, 2); // blue channel
			
			float H, S, V;

			// calculate the value
			V = max(R,G,B);

			// calculate the saturation
			float m = min(R,G,B);
			float C = V - m;

			if (V == 0.0f)
				S = 0.0f;
			else				
				S = (float)C / (float)V;

			// calculate the Hue
			if (C == 0.0f)
				H = 0.0f;
			else
			{
				float H_;

				if (within_eps(V, R))
					H_ = (float)(G - B) / (float)C;
				else if (within_eps(V, G))
					H_ = 2.f + (float)(B - R) / (float)C;
				else if(within_eps(V,B))
					H_ = 4.f + (float)(R - G) / (float)C;

				if (H_ < 0.0f)
					H = (float)H_ / (float)6 + 1.f;
				else
					H = (float)H_ / (float)6;

				assert(H >= 0.0f && H < 1.0f);
			}

			im(q1, q2, 0) = H;
			im(q1, q2, 1) = S;
			im(q1, q2, 2) = V;
		}
	//NOT_IMPLEMENTED();  
  }

// HW0 #7
// Image& im: input image to be modified in-place
void hsv_to_rgb(Image& im)
  {
	assert(im.c==3 && "only works for 3-channels images");
  
	// TODO: Convert all pixels from HSV format to RGB format
	for (int q2 = 0; q2 < im.h; q2++)
		for (int q1 = 0; q1 < im.w; q1++)
		{
			float H = im(q1, q2, 0); // Hue channel
			float S = im(q1, q2, 1); // Saturation channel
			float V = im(q1, q2, 2); // Value channel

			float C = V * S;
			float X = C * ( 1.f - fabs((6.f * fmod(H,2.f)) - 1.f));
			float m = V - C;

			float R_, G_, B_;

			if (H >= 0.0f && H < 1.0f / 6)
			{
				R_ = C;
				G_ = X;
				B_ = 0.f;
			}
			else if (H >= 1.0f / 6 && H < 2.f / 6)
			{
				R_ = X;
				G_ = C;
				B_ = 0.f;
			}
			else if (H >= 2.f / 6 && H < 3.f / 6)
			{
				R_ = 0;
				G_ = C;
				B_ = X;
			}
			else if (H >= 3.f / 6 && H < 4.f / 6)
			{
				R_ = 0;
				G_ = X;
				B_ = C;
			}
			else if (H >= 4.f / 6 && H < 5.f / 6)
			{
				R_ = X;
				G_ = 0.f;
				B_ = C;
			}
			else if(H >= 5.f / 6 && H < 1.f)
			{
				R_ = C;
				G_ = 0.f;
				B_ = X;
			}

			float R = R_ + m;
			if (R < 0.0f) R = 0.0f;
			if (R > 1.0f) R = 1.0f;

			float G = G_ + m;
			if (G < 0.0f) G = 0.0f;
			if (G > 1.0f) G = 1.0f;

			float B = B_ + m;
			if (B < 0.0f) B = 0.0f;
			if (B > 1.0f) B = 1.0f;

			im(q1, q2, 0) = R;
			im(q1, q2, 1) = G;
			im(q1, q2, 2) = B;
		}
	// NOT_IMPLEMENTED();  
  }

// HW0 #9
// Image& im: input image to be modified in-place
void rgb_to_lch(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from RGB format to LCH format
  
  
  NOT_IMPLEMENTED();
  
  }

// HW0 #9
// Image& im: input image to be modified in-place
void lch_to_rgb(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from LCH format to RGB format
  
  NOT_IMPLEMENTED();
  
  }



// Implementation of member functions
void Image::clamp(void) { clamp_image(*this); }
void Image::shift(int c, float v) { shift_image(*this,c,v); }
void Image::scale(int c, float v) { scale_image(*this,c,v); }

void Image::HSVtoRGB(void) { hsv_to_rgb(*this); }
void Image::RGBtoHSV(void) { rgb_to_hsv(*this); }
void Image::LCHtoRGB(void) { lch_to_rgb(*this); }
void Image::RGBtoLCH(void) { rgb_to_lch(*this); }
