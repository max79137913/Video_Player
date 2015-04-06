//*****************************************************************************
//
// Image.cpp : Defines the class operations on images
//
// Author - Parag Havaldar
// Code used by students as starter code to display and modify images
//
//*****************************************************************************

#include "Image.h"

#include <iostream>
using namespace std;

// Constructor and Desctructors
MyImage::MyImage() 
{
	Data = NULL;
	Width = -1;
	Height = -1;
	ImagePath[0] = 0;

}

MyImage::~MyImage()
{
	if ( Data )
		delete Data;
}


// Copy constructor
MyImage::MyImage( MyImage *otherImage)
{
	Height = otherImage->Height;
	Width  = otherImage->Width;
	Data   = new char[Width*Height*3];
	//strcpy(otherImage->ImagePath, ImagePath );
	strcpy( (char *)ImagePath, otherImage->ImagePath );
	for ( int i=0; i<(Height*Width*3); i++ )
	{
		Data[i]	= otherImage->Data[i];
	}


}



// = operator overload
MyImage & MyImage::operator= (const MyImage &otherImage)
{
	Height = otherImage.Height;
	Width  = otherImage.Width;
	oldHeight = otherImage.oldHeight;
	oldWidth  = otherImage.oldWidth;
	Data   = new char[Width*Height*3];
	strcpy( (char *)ImagePath, otherImage.ImagePath );
	
	for ( int i=0; i<(Height*Width*3); i++ )
	{
		Data[i]	= otherImage.Data[i];
	}
	
	return *this;

}


// MyImage::ReadImage
// Function to read the image given a path
bool MyImage::ReadImage()
{

	// Verify ImagePath
	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		fprintf(stderr, "Usage is `Image.exe Imagefile w h`");
		return false;
	}
	
	// Create a valid output file pointer
	FILE *IN_FILE;
	IN_FILE = fopen(ImagePath, "rb");
	if ( IN_FILE == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Reading");
		return false;
	}

	// Create and populate RGB buffers
	int i;
	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width]; 

	for (i = 0; i < Width*Height; i ++)
	{
		Rbuf[i] = fgetc(IN_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		Gbuf[i] = fgetc(IN_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		Bbuf[i] = fgetc(IN_FILE);
	}
	
	// Allocate Data structure and copy
	Data = new char[Width*Height*3];
	for (i = 0; i < Height*Width; i++)
	{
		Data[3*i]	= Bbuf[i];
		Data[3*i+1]	= Gbuf[i];
		Data[3*i+2]	= Rbuf[i];
	}

	// Clean up and return
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	fclose(IN_FILE);

	return true;

}



// MyImage functions defined here
bool MyImage::WriteImage()
{
	// Verify ImagePath
	// Verify ImagePath
	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		return false;
	}
	
	// Create a valid output file pointer
	FILE *OUT_FILE;
	OUT_FILE = fopen(ImagePath, "wb");
	if ( OUT_FILE == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Writing");
		return false;
	}

	// Create and populate RGB buffers
	int i;
	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width]; 

	for (i = 0; i < Height*Width; i++)
	{
		Bbuf[i] = Data[3*i];
		Gbuf[i] = Data[3*i+1];
		Rbuf[i] = Data[3*i+2];
	}

	
	// Write data to file
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Rbuf[i], OUT_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Gbuf[i], OUT_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Bbuf[i], OUT_FILE);
	}
	
	// Clean up and return
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	fclose(OUT_FILE);

	return true;

}




// Here is where you would place your code to modify an image
// eg Filtering, Transformation, Cropping, etc.
bool MyImage::Modify()
{

	// TO DO by student
	// sample operation
//	for ( int i=0; i<Width*Height; i++ ){Data[3*i] = 0;Data[3*i+1] = 0;}

	AntiAlias();
//	DisplayVideo(3);
//	Rescale(2,2);
	return false;
}

int MyImage::numofFrame()
{
	int totallengths=0;
	int numFrame=0;

	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		fprintf(stderr, "Usage is `Image.exe Imagefile w h`");
		
	}
	
	// Create a valid output file pointer
	FILE *IN_FILE;
	IN_FILE = fopen(ImagePath, "rb");
	// Create and populate RGB buffers
/*	char c=0;

	
	while(c!= EOF)
	{
		c= fgetc(IN_FILE);
		totallengths++;
	}*/
	fseek(IN_FILE,0L,SEEK_END);
	totallengths=ftell(IN_FILE);
	numFrame=(totallengths)/(Width*Height*3);


	rewind(IN_FILE);
    fclose (IN_FILE);
	return numFrame;
}
int MyImage::TotalLength()
{
	int totallengths=0;

	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		fprintf(stderr, "Usage is `Image.exe Imagefile w h`");
		
	}
	
	// Create a valid output file pointer
	FILE *IN_FILE;
	IN_FILE = fopen(ImagePath, "rb");
	// Create and populate RGB buffers


	fseek(IN_FILE,0L,SEEK_END);
	totallengths=ftell(IN_FILE);

	rewind(IN_FILE);
    fclose (IN_FILE);


	return totallengths;

}

void MyImage::SetupVideo()
{


	long int length;
	length=TotalLength();

	setupData   = new char[length];



	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		fprintf(stderr, "Usage is `Image.exe Imagefile w h`");
		
	}
	// Create a valid output file pointer
	FILE *IN_FILE;
	IN_FILE = fopen(ImagePath, "rb");
	if ( IN_FILE == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Reading");
		
	}
	int count;
	
		
	
	
	for (count = 0; count < length; count ++)
	{
		setupData[count]=fgetc(IN_FILE);
	}

	numberframe=numofFrame();

	
	fclose(IN_FILE);

}
void MyImage::DisplayVideo(int startframe)
{

	// TO DO by student
	

	// Create and populate RGB buffers
	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width];


	int i;

	for (i = 0; i < Width*Height; i ++)
	{
		Rbuf[i] = finalData[(i)+(startframe*Width*Height*3)];
	}
	for (i = 0; i < Width*Height; i ++)
	{
		int j=Width*Height;

		Gbuf[i] = finalData[(j+i)+(startframe*Width*Height*3)];
	}
	for (i = 0; i < Width*Height; i ++)
	{
		int j=Width*Height*2;
		Bbuf[i] = finalData[(j+i)+(startframe*Width*Height*3)];
	}
	
	// Allocate Data structure and copy
	Data = new char[Width*Height*3];
	for (i = 0; i < Height*Width; i++)
	{
		Data[3*i]	= Bbuf[i];
		Data[3*i+1]	= Gbuf[i];
		Data[3*i+2]	= Rbuf[i];
	}
	
	// Clean up and return
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	

	
}
void MyImage::AntiAlias()
{

	int i;

	int startframe=0;
	int maxframe=numberframe;

	for(startframe=0;startframe<maxframe;startframe++){


	int *Rbuf = new int[Height*Width]; 
	int *Gbuf = new int[Height*Width]; 
	int *Bbuf = new int[Height*Width];

	int *tmpRbuf = new int[Height*Width]; 
	int *tmpGbuf = new int[Height*Width]; 
	int *tmpBbuf = new int[Height*Width];


		for (i = 0; i < Width*Height; i ++)
	{
		tmpBbuf[i]=int(finalData[(i)+(startframe*Width*Height*3)])    ;
	}
	for (i = 0; i < Width*Height; i ++)
	{
		int j=Width*Height;

		tmpGbuf[i]=int(finalData[(j+i)+(startframe*Width*Height*3)])  ;
	}
	for (i = 0; i < Width*Height; i ++)
	{
		int j=Width*Height*2;
		tmpRbuf[i]=int(finalData[(j+i)+(startframe*Width*Height*3)])  ;
	}
	
		for (i = 0; i < Width*Height; i ++)/// init the RGB buf
	{
		Bbuf[i]=tmpBbuf[i]  ;
		Gbuf[i]=tmpGbuf[i]  ;
		Rbuf[i]=tmpRbuf[i]  ;
		
	}

	for (i = 0; i < Width*Height; i ++)/// convert to unsigned
	{
		tmpBbuf[i]=tmpBbuf[i] &0xff;
		tmpGbuf[i]=tmpGbuf[i] &0xff ;
		tmpRbuf[i]=tmpRbuf[i] &0xff ;
		
	}
	
	

	int j=0;
	
//	for(i=1+(Width*j);i<((Width-1)*(Height-1)+(Height-2));i++)
	

	for(i=1;i<Height-1;i++)
	{
		for(j=1;j<Width-1;j++)
		{
			Rbuf[j+(i*Width)]=(tmpRbuf[(j-1)+(i-1)*Width]+tmpRbuf[j+(i-1)*Width]+tmpRbuf[(j+1)+(i-1)*Width]+tmpRbuf[(j-1)+(i)*Width]+tmpRbuf[(j)+(i)*Width]+tmpRbuf[(j+1)+(i)*Width]+tmpRbuf[(j-1)+(i+1)*Width]+tmpRbuf[(j)+(i+1)*Width]+tmpRbuf[(j+1)+(i+1)*Width]) /9;
			Gbuf[j+(i*Width)]=(tmpGbuf[(j-1)+(i-1)*Width]+tmpGbuf[j+(i-1)*Width]+tmpGbuf[(j+1)+(i-1)*Width]+tmpGbuf[(j-1)+(i)*Width]+tmpGbuf[(j)+(i)*Width]+tmpGbuf[(j+1)+(i)*Width]+tmpGbuf[(j-1)+(i+1)*Width]+tmpGbuf[(j)+(i+1)*Width]+tmpGbuf[(j+1)+(i+1)*Width]) /9;
			Bbuf[j+(i*Width)]=(tmpBbuf[(j-1)+(i-1)*Width]+tmpBbuf[j+(i-1)*Width]+tmpBbuf[(j+1)+(i-1)*Width]+tmpBbuf[(j-1)+(i)*Width]+tmpBbuf[(j)+(i)*Width]+tmpBbuf[(j+1)+(i)*Width]+tmpBbuf[(j-1)+(i+1)*Width]+tmpBbuf[(j)+(i+1)*Width]+tmpBbuf[(j+1)+(i+1)*Width]) /9;
		}
		
	}

	for (i = 0; i < Width*Height; i ++)
	{
		finalData[(i)+(startframe*Width*Height*3)]=char(Bbuf[i]) ;
	}
	for (i = 0; i < Width*Height; i ++)
	{
		int j=Width*Height;

		finalData[(j+i)+(startframe*Width*Height*3)]=char(Gbuf[i]) ;
	}
	for (i = 0; i < Width*Height; i ++)
	{
		int j=Width*Height*2;
		finalData[(j+i)+(startframe*Width*Height*3)]=char(Rbuf[i]);
	}
	
	
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	delete tmpRbuf;
	delete tmpGbuf;
	delete tmpBbuf;


	} //for startframe loop
}
int round(float num)
{
	int newnum;
	newnum=int(num+0.5);
	return newnum;
}
void MyImage::Rescale(float sw, float sh)
{
	int startframe=0;
	int maxframe=numberframe;

	int newWidth=int(sw*oldWidth);
	int newHeight=int(sh*oldHeight);

	newWidth=(newWidth/4)*4;
	
		setWidth(newWidth);//make Width,Height new
		setHeight(newHeight);//make Width,Height new
	
	

	//Data = new char[Width*Height*3];// new Data
	finalData= new char[maxframe*Width*Height*3];


	for(startframe=0;startframe<maxframe;startframe++){


	char *tmpRbuf = new char[oldHeight*oldWidth]; ///
	char *tmpGbuf = new char[oldHeight*oldWidth]; ///
	char *tmpBbuf = new char[oldHeight*oldWidth];///

	int i;

		for (i = 0; i < oldWidth*oldHeight; i ++)
	{
		tmpBbuf[i] = setupData[(i)+(startframe*oldWidth*oldHeight*3)];
	}
	for (i = 0; i < oldWidth*oldHeight; i ++)
	{
		int j=oldWidth*oldHeight;

		tmpGbuf[i] = setupData[(j+i)+(startframe*oldWidth*oldHeight*3)];
	}
	for (i = 0; i < oldWidth*oldHeight; i ++)
	{
		int j=oldWidth*oldHeight*2;
		tmpRbuf[i] = setupData[(j+i)+(startframe*oldWidth*oldHeight*3)];
	}


	

/*	int count;
	for (count = 0; count < Height*Width; count++)
	{
		 tmpBbuf[count]=Data[3*count];
		 tmpGbuf[count]=Data[3*count+1];
		 tmpRbuf[count]=Data[3*count+2];
	}
*/
	

/*	int newWidth=int(sw*oldWidth);
//	int newHeight=int(sh*oldHeight);

	if(startframe==0)//make Width,Height new
    {  
		setWidth(newWidth);
		setHeight(newHeight);
	}
*/	
	
	


	//delete Data;
	//Data = new char[Width*Height*3];// new Data
	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width];
	
	int j;

	for(i=0;i<Height;i++)
	{
		for(j=0;j<Width;j++)
		{
			int _i;
			int _j;
			_i=round(i/sh);
			_j=round(j/sw);


			Rbuf[j+i*Width]=tmpRbuf[_j+_i*oldWidth];
			Gbuf[j+i*Width]=tmpGbuf[_j+_i*oldWidth];
			Bbuf[j+i*Width]=tmpBbuf[_j+_i*oldWidth];
			
		}

	}
	
/*	for (i = 0; i < Height*Width; i++)
	{
		Data[3*i]	= Bbuf[i];
		Data[3*i+1]	= Gbuf[i];
		Data[3*i+2]	= Rbuf[i];
	}
*/
	for (i = 0; i < Width*Height; i ++)
	{
		finalData[(i)+(startframe*Width*Height*3)]=Bbuf[i];
	}
	for (i = 0; i < Width*Height; i ++)
	{
		int j=Width*Height;

		finalData[(j+i)+(startframe*Width*Height*3)]=Gbuf[i];
	}
	for (i = 0; i < Width*Height; i ++)
	{
		int j=Width*Height*2;
		finalData[(j+i)+(startframe*Width*Height*3)]=Rbuf[i];
	}




	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	delete tmpRbuf;
	delete tmpGbuf;
	delete tmpBbuf;
	
	
	}////for frame loop
	
}
void MyImage::AspectRatio(float sw, float sh)
{

	float originalscale;
	float afterscale;
	float ratio;

	originalscale=float(oldWidth)/float(oldHeight);
	afterscale=(sw*float(oldWidth))/(sh*float(oldHeight));


	ratio= originalscale/afterscale;

	int newWidth=int(sw*oldWidth);
	int newHeight=int(sh*oldHeight);

	newWidth=(newWidth/4)*4;
	
		setWidth(newWidth);//make Width,Height new
		setHeight(newHeight);//make Width,Height new


	int maxframe=numberframe;
	finalData= new char[maxframe*Width*Height*3];

	

	int startframe;

	for(startframe=0;startframe<maxframe;startframe++){



	if(ratio>=1)
	{
		
	


		int holdInterval=oldHeight/4;
		int hInterval=newHeight/4;

	char *tmpRbuf = new char[oldHeight*oldWidth]; ///
	char *tmpGbuf = new char[oldHeight*oldWidth]; ///
	char *tmpBbuf = new char[oldHeight*oldWidth];///

	


	int i;

	


	for (i = 0; i < oldWidth*oldHeight; i ++)
	{
		tmpBbuf[i] = setupData[(i)+(startframe*oldWidth*oldHeight*3)];
	}
	for (i = 0; i < oldWidth*oldHeight; i ++)
	{
		int j=oldWidth*oldHeight;

		tmpGbuf[i] = setupData[(j+i)+(startframe*oldWidth*oldHeight*3)];
	}
	for (i = 0; i < oldWidth*oldHeight; i ++)
	{
		int j=oldWidth*oldHeight*2;
		tmpRbuf[i] = setupData[(j+i)+(startframe*oldWidth*oldHeight*3)];
	}


	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width];



		int j;

		int x=0;
	for(i=hInterval;i<3*hInterval;i++)
	{
	
		
		int _i;
		int _j;

		for(j=0;j<Width;j++)
		{
			


	/*		if(sh>1){
				int bigthen=hInterval/sh; // change 50%w->x old
				_i=(2*holdInterval-bigthen)+(i/sh);
			}
			else{_i=(2*holdInterval-hInterval);}
	*/

			
			_i=(2*holdInterval-(hInterval))+x;



			_j=round(j/sw);                                                                                                                                                                           


			


			Rbuf[j+i*Width]=tmpRbuf[_j+_i*oldWidth];
			Gbuf[j+i*Width]=tmpGbuf[_j+_i*oldWidth];
			Bbuf[j+i*Width]=tmpBbuf[_j+_i*oldWidth];

			
			
		}
		x++;
	//	
	}

	x=0;
	for(i=0;i<hInterval;i++)
	{
		for(j=0;j<Width;j++)
		{
			int _i;
			int _j;
			float shnew;

			shnew=float(hInterval)/float((holdInterval+holdInterval-hInterval));
			_i=x/shnew;
			_j=round(j/sw);



			Rbuf[j+i*Width]=tmpRbuf[_j+_i*oldWidth];
			Gbuf[j+i*Width]=tmpGbuf[_j+_i*oldWidth];
			Bbuf[j+i*Width]=tmpBbuf[_j+_i*oldWidth];
			
		}
	x++;
	}

	x=0;
		for(i=hInterval*3;i<Height;i++)
	{
		for(j=0;j<Width;j++)
		{
			int _i;
			int _j;
			float shnew;
			shnew=float(Height-3*hInterval)/float(oldHeight-(2*holdInterval+hInterval));
			
			_i=2*holdInterval+hInterval+x/(shnew);
			_j=round(j/sw);


			Rbuf[j+i*Width]=tmpRbuf[_j+_i*oldWidth];
			Gbuf[j+i*Width]=tmpGbuf[_j+_i*oldWidth];
			Bbuf[j+i*Width]=tmpBbuf[_j+_i*oldWidth];
			
		}
		x++;
	}






	

		for (i = 0; i < Width*Height; i ++)
	{
		finalData[(i)+(startframe*Width*Height*3)]=Bbuf[i];
	}
	for (i = 0; i < Width*Height; i ++)
	{
		int j=Width*Height;

		finalData[(j+i)+(startframe*Width*Height*3)]=Gbuf[i];
	}
	for (i = 0; i < Width*Height; i ++)
	{
		int j=Width*Height*2;
		finalData[(j+i)+(startframe*Width*Height*3)]=Rbuf[i];
	}


	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	delete tmpRbuf;
	delete tmpGbuf;
	delete tmpBbuf;
	
	
	
	}
	else if(ratio<1)
	{

		

		int woldInterval=oldWidth/4;
		int wInterval=newWidth/4;

	char *tmpRbuf = new char[oldHeight*oldWidth]; ///
	char *tmpGbuf = new char[oldHeight*oldWidth]; ///
	char *tmpBbuf = new char[oldHeight*oldWidth];///

	

	int i;

	for (i = 0; i < oldWidth*oldHeight; i ++)
	{
		tmpBbuf[i] = setupData[(i)+(startframe*oldWidth*oldHeight*3)];
	}
	for (i = 0; i < oldWidth*oldHeight; i ++)
	{
		int j=oldWidth*oldHeight;

		tmpGbuf[i] = setupData[(j+i)+(startframe*oldWidth*oldHeight*3)];
	}
	for (i = 0; i < oldWidth*oldHeight; i ++)
	{
		int j=oldWidth*oldHeight*2;
		tmpRbuf[i] = setupData[(j+i)+(startframe*oldWidth*oldHeight*3)];
	}


	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width];



		int j;
		int x=0;

	for(j=wInterval;j<3*wInterval;j++)
	{
		int _i;
		int _j;


		for(i=0;i<Height;i++)
		{
			

			
			_i=round(i/sh);
		//	_j=round(j/sw);

					
	
			_j=2*woldInterval-(wInterval)+x;
		

			

			Rbuf[j+i*Width]=tmpRbuf[_j+_i*oldWidth];
			Gbuf[j+i*Width]=tmpGbuf[_j+_i*oldWidth];
			Bbuf[j+i*Width]=tmpBbuf[_j+_i*oldWidth];
			
		}
		x++;
	}

	x=0;
	for(j=0;j<wInterval;j++)
	{
		for(i=0;i<Height;i++)
		{


			int _i;
			int _j;

		
			
			float swnew;


			swnew=float(wInterval)/float((woldInterval+woldInterval-wInterval));
			_i=round(i/sh);
			_j=round(x/swnew);

			Rbuf[j+i*Width]=tmpRbuf[_j+_i*oldWidth];
			Gbuf[j+i*Width]=tmpGbuf[_j+_i*oldWidth];
			Bbuf[j+i*Width]=tmpBbuf[_j+_i*oldWidth];
			
		}
		x++;

	}

	x=0;
		for(j=wInterval*3;j<Width;j++)
	{

		
		for(i=0;i<Height;i++)
		{


			int _i;
			int _j;
			float swnew;
			
			swnew=float(Width-3*wInterval)/float(oldWidth-(2*woldInterval+wInterval));
			
			_j=2*woldInterval+wInterval+x/swnew;
			_i=round(i/sh);
			
			


			Rbuf[j+i*Width]=tmpRbuf[_j+_i*oldWidth];
			Gbuf[j+i*Width]=tmpGbuf[_j+_i*oldWidth];
			Bbuf[j+i*Width]=tmpBbuf[_j+_i*oldWidth];

			
			
		}
		x++;
	}





		for (i = 0; i < Width*Height; i ++)
	{
		finalData[(i)+(startframe*Width*Height*3)]=Bbuf[i];
	}
	for (i = 0; i < Width*Height; i ++)
	{
		int j=Width*Height;

		finalData[(j+i)+(startframe*Width*Height*3)]=Gbuf[i];
	}
	for (i = 0; i < Width*Height; i ++)
	{
		int j=Width*Height*2;
		finalData[(j+i)+(startframe*Width*Height*3)]=Rbuf[i];
	}


	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	delete tmpRbuf;
	delete tmpGbuf;
	delete tmpBbuf;
	
	
	
	
	
	
	
	
	}//elseif

	}//for frame


}