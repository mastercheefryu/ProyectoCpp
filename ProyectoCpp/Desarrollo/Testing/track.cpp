/*-------------------------------------------------------------
Simple Hand Tracking with Kinect, OpenCV, and Cinder on OS X
By Andrew Berg
andrew@andrewberg.com

Description
This program uses Cinder(http://libcinder.org/) and its Open Computer Vision (http://opencv.willowgarage.com/) cinder block to track a users motions. A red ball will follow a region specified by a few simple parameters.

There is no actual recognition of the hands per say, the program is simply using the kinect's depth image to identify shapes of a certain size at a certain distance from the camera. Exploiting the fact that people stand with hands outstretched when gesturing at the sensor.

Software and Libraries used
libfreenect - http://openkinect.org/
X-Code https://developer.apple.com/xcode/
Cinder https://github.com/cinder/Cinder
Kinect Cinder Block https://github.com/cinder/Cinder-Kinect
OpenCV Cinder Block https://github.com/cinder/Cinder-OpenCV

Setup
1) Make sure you have xcode and it's command line tools installed
2) Install the libfreenect driver http://openkinect.org/wiki/Getting_Started
3) Install Cinder from github http://libcinder.org/docs/welcome/GitSetup.html
4) Clone the Kinect and OpenCV blocks listed above into the Cinder/blocks folder
5) Create a new project with TinderBox http://libcinder.org/docs/welcome/MacNewProject.html
6) Add OpenCV block to the project http://forum.libcinder.org/topic/how-to-use-cinderblocks-in-xcode
	for this project we need the libopencv_core.a and libopencv_imgproc.a
7) Add the Kinect block in the same way. In addition we need to add the Kinect.cpp in the src folder of the block to our project's source files.
8) Add the OS X native IOKit.framework in Target -> Build Phases -> Link Binary With Libraries
    https://developer.apple.com/library/ios/#recipes/xcode_help-project_editor/Articles/AddingaLibrarytoaTarget.html#//apple_ref/doc/uid/TP40010155-CH17-SW1
9) switch your compiler to LLVM/GCC
10) Pray ;)
---------------------------------------------------------------*/

// includes from cinder for a basic app
// OpenGL, textures and tweaking settings
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/params/Params.h"
// the open cv and kinect blocks to include
#include "CinderOpenCV.h"
#include "Kinect.h"

// convienence namespacing
// so we don't have to prepend function calls
using namespace ci;
using namespace ci::app;
using namespace std;


// Constructor function
// define properties and methods for the app
class TestApp : public AppBasic {

	// cinder apps automatically call
	// prepare and setup during startup
	// then update and draw every frame
    void prepareSettings( Settings* settings );
    void setup();
    void update();
    void draw();
    
    // the stettings for the app
    // that define what to track
    float mThreshold, mBlobMin, mBlobMax;
    float mKinectTilt;
    
    // kinect instance
    Kinect mKinect;

    // textures to display what the program is seeing
    gl::Texture mColorTexture, mDepthTexture, mCvTexture;
    // a surface to store the depth image 
    // that gets passed to open cv
    Surface mDepthSurface;
    
    // the position being tracked
    Vec3f mTargetPosition;
    
    // a parameters pane so settings can be adjusted
    params::InterfaceGl mParams;
    
};

void TestApp::prepareSettings( Settings* settings )
{
    settings->setWindowSize( 640, 720 );
}


void TestApp::setup()
{
    // define the default settings values
    mThreshold 	= 70.0f;
    mBlobMin	= 20.0f;
    mBlobMax 	= 80.0f;
    mKinectTilt = 10;
    
    // add them to our parameters pane for tweaking
    mParams = params::InterfaceGl( "Hand Tracking", Vec2i( 250, 100 ) );
    mParams.addParam( "Threshold", &mThreshold, "min=0.0 max=255.0 step=1.0 keyIncr=s keyDecr=w" );
    mParams.addParam( "Blob Minimum Radius", &mBlobMin, "min=1.0 max=200.0 step=1.0 keyIncr=e keyDecr=d" );
    mParams.addParam( "Blob Maximum Radius", &mBlobMax, "min=1.0 max=200.0 step=1.0 keyIncr=r keyDecr=f" );
    mParams.addParam( "Kinect Tilt", &mKinectTilt, "min=-31 max=31 keyIncr=T keyDecr=t" );
    
    // get the Kinect 
    mKinect = Kinect( Kinect::Device() );
    // set the target to 0
    mTargetPosition = Vec3f::zero();
    
}

// image processing takes place every frame via the update method
void TestApp::update()
{
    // if the app has recieved a depth frame from the kinect
    if( mKinect.checkNewDepthFrame() ){
        
        // get the current depth image from the kinect
        ImageSourceRef depthImage = mKinect.getDepthImage();
        
        // make a texture to use for display
        mDepthTexture = depthImage;
        // make a surface for opencv
        mDepthSurface = depthImage;
        
        if(mDepthSurface){
            
            // once the surface is avalable pass it to opencv
            
            // even though the depth image is grayscale it still
            // has a 16bit depth which is too high for open cv.
            // here the image surface is converted to an 8bit channel
            // and then to an opencv image.
            
            //in additon three other empty images are allocated for the processing and output
            cv::Mat input( toOcv( Channel8u( mDepthSurface )  ) ), blurred, thresholded, thresholded2, output;

            // first the depth image is blurred
            // to minimize noise
            cv::blur(input, blurred, cv::Size(10,10));
            
            // make two thresholded images from the blurred image, 
            // one to display and one to pass to find contours function
            // since its process alters the image.
            // by thresholding the depth image the program is 
            // isolating a slice of space to look for contours in.
            // Adjusting the threshold value in the parameters pane will 
            // alter that slices depth.
            cv::threshold( blurred, thresholded, mThreshold, 255,  CV_8U );
            cv::threshold( blurred, thresholded2, mThreshold, 255,  CV_8U );
            
            // 2d vector to store the found contours
            vector<vector<cv::Point> > contours;
            // pass the thresholded image to OpenCV's find contours function 
            // the two constants passed as the third and fourth arguments 
            // ask the function to only look for outer contours that have been simplified  
            // http://opencv.willowgarage.com/documentation/structural_analysis_and_shape_descriptors.html?highlight=findcontours#cvFindContours
            cv::findContours(thresholded, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
            
            // convert theshold image to color for output
            // so we can draw blobs on it
            cv::cvtColor( thresholded2, output, CV_GRAY2RGB );
            
            // loop the stored contours
            for (vector<vector<cv::Point> >::iterator it=contours.begin() ; it < contours.end(); it++ ){
                
                // center and radius for current blob
                cv::Point2f center;
                float radius;
                // convert the contour points to a matrix 
                vector<cv::Point> pts = *it;
                cv::Mat pointsMatrix = cv::Mat(pts);
                // Pass the matrix to min enclosing circle to make the blob.
                // This function looks at the current contours set of points
                // and returns the radius of the minimum enclosing circle
                // http://opencv.willowgarage.com/documentation/structural_analysis_and_shape_descriptors.html?highlight=findcontours#minenclosingcircle 
                cv::minEnclosingCircle(pointsMatrix, center, radius);
                
                cv::Scalar color( 0, 255, 0 );
                // if the radius is within the specified range
                if (radius > mBlobMin && radius < mBlobMax) {
                    // draw the circle
                    cv::circle(output, center, radius, color);
                    
                    // update the target position    
                    mTargetPosition.x = 640 - center.x;
                    mTargetPosition.y = center.y;
                    mTargetPosition.z = 0;
                }
                
                
            }
            
            mCvTexture = gl::Texture( fromOcv( output ) );
            
        }
          
    }
    if( mKinect.checkNewVideoFrame() )
		mColorTexture = mKinect.getVideoImage();
    
    if( mKinectTilt != mKinect.getTilt() )
        mKinect.setTilt( mKinectTilt );
    
}

// the draw method uses fixed function
// OpenGL to draw the program output
void TestApp::draw()
{
    // clear the last frame
    gl::clear( Color( 0.5f, 0.5f, 0.5f ) );
    
    // disable depth for drawing video frames
    gl::disableDepthWrite();
    gl::disableDepthRead();
    
    // push a new mataix to the top of the stack
    // mirror by inverting x and draw the color video frame
    glPushMatrix();
    gl::scale(Vec3f(-1, 1, 1));
    if( mColorTexture )
        gl::draw( mColorTexture, Vec2i( -640, 0));
    glPopMatrix();
    
    // push a new matrix
    // scale down and mirror to draw the depth image 
    // and the result of open cv processing below the main image.
    //
    // the image on the right will reflect the changes made to the settings,
    // try adjusting the threshold and min and max blob size to see the results
    glPushMatrix();
    gl::scale(Vec3f(-0.5, 0.5, 1));
    if( mDepthTexture )
        gl::draw( mDepthTexture,Vec2i( -640, 960 ));
    if ( mCvTexture )
        gl::draw( mCvTexture,Vec2i( -1280, 960 ));
    glPopMatrix();
    
    // reenable depth
    gl::enableDepthWrite();
    gl::enableDepthRead();
    // draw the red dot at the target position
    gl::color(Colorf(1.0f, 0.0f, 0.0f));
    gl::drawSphere(mTargetPosition, 10.0f);
    gl::color(Colorf(1.0f, 1.0f, 1.0f));
    // update the parameters pane
    params::InterfaceGl::draw();
    
}
