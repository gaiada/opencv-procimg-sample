//we include High level GUI and Media I/O
#include "opencv2/highgui/highgui.hpp"

//Including Image processing capabilities
#include "opencv2/imgproc/imgproc.hpp"

//OpenCV core module is implicitly included

//we are using both standard and OpenCV namespaces
using namespace std;
using namespace cv;



int main(int argc, char **argv) {

  //Initiate video capture device on cap
  VideoCapture cap(0);

  //If could not open capture device, program die
  if(!cap.isOpened()){return -1;} 
  
  //Here is our frame
  Mat frame;

  //We will display our frames here
  namedWindow("display", CV_WINDOW_AUTOSIZE);

  //This window hold trackbars to change the program behaviour
  namedWindow("config", CV_WINDOW_AUTOSIZE);

  //by default we will not invert out frame
  bool invertimg = false;

  //we will draw Linoxide logo sketch 
  bool draw = true;
  
  // create a holder for our frame flip mode
  int flipmode = 0;
  // create a trackbar to change the flip mode
  cvCreateTrackbar("Flip Mode:", "config", &flipmode, 3);

  //width and height value holders for image resizing
  int screen_width = 640;
  int screen_height = 480;
  
  //create trackbars the config window to change the size properties
  cvCreateTrackbar("Width:", "config", &screen_width, 1024); 
  cvCreateTrackbar("Height:", "config", &screen_height, 768); 

 //create a vector of compression parameters that will be used to take a snapshot
  vector<int> compression_pars;
  compression_pars.push_back(CV_IMWRITE_PNG_COMPRESSION);
  compression_pars.push_back(9);
  
  
  while(true){

    if(!cap.read(frame)){return -1;} // could not read frame, program die
      
      //if invertimg is true, invert each of the matrix elements by reducing it	s value from the maximum possible
      if(invertimg == true){ frame =  Scalar::all(255) - frame; }

      //flip the frame according to the values on the flip mode trackbar
      if(flipmode > 0){flip(frame,frame,1);} //flip horizontal
      if(flipmode > 1){flip(frame,frame,0);} //flip vertical, now is fliped on both directions
      if(flipmode > 2){flip(frame,frame,1);} //flip horizontal, now only fliped vertically
      
      //resize the frame according to the values on the trackbars
      resize(frame,frame, Size(screen_width,screen_height) );
      
      if (draw == true){

	//draw a white rectangle to use as background, the color is Scalar(B,G,R)
	rectangle(frame, Point(5,25), Point(140,70), Scalar(255,255,255), -1, 8, 0);
	
	//dark-yellow rectangle, note that alpha value can be used
	rectangle(frame, Point(5,25), Point(54,55), Scalar(00,225,255,0), -1, 8, 0);

	//bright-blue rectangle, the thickness is negative, so it will be completly filled
	rectangle(frame, Point(57,25), Point(140,55), Scalar(255,225,100), -1, 8, 0);

	//black rectangle, start at point x5,y57, ends at x140,y70
	rectangle(frame, Point(5,57), Point(140,70), Scalar(0,0,0), -1, 8, 0);


	//write the text on the frame, separate by font characteristcs and position
	putText(frame, "L       ", Point(10,50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,0),2,0);
	putText(frame, " IN     ", Point(14,50), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,0,0),2,0);
	putText(frame, "   O    ", Point(10,50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255,255,255),2,0);
	putText(frame, "     XIDE", Point(14,50), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255,255,255),2,0);
	putText(frame, "Linux Freedom Thoughts", Point(10,65), FONT_HERSHEY_PLAIN, 0.6, Scalar(255,255,255),0,0);

	
      }
      //show our frame on the display window
      cvtColor(frame,frame,COLOR_RGB2HSV);

      imshow("display",frame);

      switch(waitKey(10)){
	case 27:  //[esc], finish program with success
	  return 0;
	case 'i': //invert image toggle
	  if (invertimg == false){invertimg = true;}else {invertimg = false;}
	case 'd': //draw Linoxide toggle
	  if (draw == false){draw = true;}else {draw = false;}
	case 's': //take a snapshot, save into snapshot.png
	  imwrite("snapshot.png", frame, compression_pars);

      }
      
  }
  //finish with success
  return 0;
}
