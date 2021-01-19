
#include "mylib.h"


using namespace cv;

std::string gstreamer_pipeline (int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) {
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
           std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
           std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}


int main(int, char**)

{ 

    int capture_width = 1280 ;
    int capture_height = 720 ;
    int display_width = 1280 ;
    int display_height = 720 ;
    int framerate = 60 ;
    int flip_method = 0 ;

    std::string pipeline = gstreamer_pipeline(capture_width,
	capture_height,
	display_width,
	display_height,
	framerate,
	flip_method);
    std::cout << "Using pipeline: \n\t" << pipeline << "\n";

cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER); // open the default camera
	
        if(!cap.isOpened())                        // check if we succeeded
		return -1;



	while(1){

	    Mat frame;
	    Mat output;
	    // Capture frame-by-frame
	    cap >> frame;
	  
	    // If the frame is empty, break immediately
	    if (frame.empty())
	      break;

		char c=(char)waitKey(25);// détection appui touche clavier


		if      ( c == 'a')      //seuillage rouge -> jaune 

			{
			 output = seuillage_cv(frame);
			}

		else if ( c == 'b')      //filtre gauss
			{
			 GaussianBlur( frame, output, Size( 9, 9 ),10.0); // peut précis, afin de créer un effet de flou	
			}

		else if ( c == 'c')      //filtre gauss+contour (débruitage)
			{
		         Mat tempim;               // création d'une image temporaire 
			 tempim = bandw_cv(frame); // detection de contour -> stockage dans tempim
			 GaussianBlur( tempim, output, Size( 3, 3 ), 10.0); // débruitage avec un filtre gaussien 	
			}

		else if ( c == 'd')      //filtre contour sans débruitage
			{
			 output = bandw_cv(frame);	
			}

		else if ( c == 27)       // si on appuie echap, frame se ferme
			{
			 break;
		         }

		else                     // si aucune touche est appuyée -> pas de traitement -> image vierge
			{
			 output = frame;
			}


	    // affichage image filtrée

	    imshow( "Frame", output);
		
	    // Appuyez sur echap pour quitter
	    
	    
	  }

	  // When everything done, release the video capture object
	  cap.release();

	  // Closes all the frames
	  destroyAllWindows();

	  return 0;
}

