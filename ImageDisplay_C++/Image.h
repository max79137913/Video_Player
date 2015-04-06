//*****************************************************************************
//
// Image.h : Defines the class operations on images
//
// Author - Parag Havaldar
// Main Image class structure 
//
//*****************************************************************************

#ifndef IMAGE_DISPLAY
#define IMAGE_DISPLAY

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "afxwin.h"

// C RunTime Header Files
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>



int round(float num);

// Class structure of Image 
// Use to encapsulate an RGB image
class MyImage 
{

private:
	int		Width;					// Width of Image
	int		Height;					// Height of Image
	int     numberframe;


	int	    oldWidth;
	int		oldHeight;

	char	ImagePath[_MAX_PATH];	// Image location
	char*	Data;					// RGB data of the image

	char*   setupData;
	char*   finalData;      //after rescale


public:
	// Constructor
	MyImage();
	// Copy Constructor
	MyImage::MyImage( MyImage *otherImage);
	// Destructor
	~MyImage();

	// operator overload
	MyImage & operator= (const MyImage & otherImage);

	// Reader & Writer functions
	void	setWidth( const int w)  { Width = w; }; 
	void	setHeight(const int h) { Height = h; };
	void	setoldWidth( const int oldw)  { oldWidth = oldw; }; 
	void	setoldHeight(const int oldh) { oldHeight = oldh; }; 
	void	setImageData( const char *img ) { Data = (char *)img; };
	void	setImagePath( const char *path) { strcpy(ImagePath, path); }
	int		getWidth() { return Width; };
	int		getHeight() { return Height; };
	char*	getImageData() { return Data; };
	char*	getImagePath() { return ImagePath; }

	// Input Output operations
	bool	ReadImage();
	bool	WriteImage();

	// Modifications
	bool	Modify();
	int     numofFrame(); // return how much frames
	int     TotalLength();//return how much pixels
	void    SetupVideo();// fill all the data
	void	DisplayVideo(int startframe);
	//////////////////////////////////////
	void	AntiAlias();
	void	Rescale(float sw, float sh);

	void    AspectRatio(float sw, float sh);


};

#endif //IMAGE_DISPLAY
