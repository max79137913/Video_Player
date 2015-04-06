Kuo,PO-Ting.

Environment: VS 2010 

Language: C++ 

You can drag video1.rgb or video2.rgb under the ImageDisplay_C++ file then it can play video1 or video2 while type them in the command line.

After image or video produced, scale the window will make the original outimage disappear. Instead, the image produced 
by our commandline. 



Each image is different in the colors, frequency content etc. and should
serve as a good example for playing with subsampling, color space transformations,
quantization, compression etc.

The project includes the following important files.
1. Image.h	- header file for MyImage class
2. Image.cpp	- defines operations on an image such as read, write, modify
3. Main.cpp	- entry point of the application, takes care of the GUI and the 
		  image display operations

Some indicators have been placed in the code to guide you to develop your code. But you
you are free to modify the program in any way to get the desirable output.

- Unzip the folder in your desired location
- Launch Visual Studio and load the .dsw or .dsp project files
- If you use the .net compiler, you can still load the project file, just 
  follow the default prompts and it will create a solution .sln file for you
- Compile the program to produce a an executable Image.exe
- To run the program you need to provide the program with command line arguments, they can 
  be passed in Visual C++ using Project > Settings or just launch a .exe file from the command prompt
- Here is the usage (for the given example images)

Image.exe image1.rgb 640 480
Image.exe image2.rgb 640 480
Image.exe image3.rgb 640 480
Image.exe image4.rgb 352 288
Image.exe image5.rgb 480 360
Image.exe image6.rgb 320 240
Image.exe image7.rgb 512 512

video1.rgb 352 288 30
