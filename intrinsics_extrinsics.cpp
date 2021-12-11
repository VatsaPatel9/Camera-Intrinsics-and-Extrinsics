#include <iostream>
#define _USE_MATH_DEFINES
#include <opencv2/core/core.hpp> //include all the basic data types from opencv
#include <opencv2/highgui/highgui.hpp>//allow you to load image from computer or display image onto the screen
#include <opencv2/imgproc/imgproc.hpp> //provide functions to process an image
#include <cmath>
#include <math.h>
#include <fstream>
#include<sstream>
  

using namespace cv;
using namespace std;
int Cx = 316;
int Cy = 256;
int focal_length = 524;
Mat data3D;

Mat New_Data3D;
Mat Rotat_x;

Mat Trans;
Mat extrinstic;

void convert2D_to_3D(Mat img, Mat depth) {

    data3D.create(4, 640 * 480, CV_64FC1);
    int k = 0;

    //Generating X,Y,Z Coordinate in 3d plane from 2d plane
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {

            short int z = depth.ptr<short int>(y)[x];
            uchar pixel = img.ptr<uchar>(y)[x];
            double X;
            double Y;
            X = (double)((pixel / focal_length) * z - (Cx * z));
            Y = (double)((pixel / focal_length) * z - (Cy * z));
            data3D.ptr<double>(0)[k] = (double)X;
            data3D.ptr<double>(1)[k] = (double)Y;
            data3D.ptr<double>(2)[k] = (double)z;
            data3D.ptr<double>(3)[k] = 1;

            k++;
        }
        cout << "\n";
        cout << k;
    }
    cout << "Loop Ended";
    // cout<< data3D;
 //    imshow( "Display window", data3D );
 //      waitKey(0);
    cout << "\n";
    cout << data3D.rows;
    cout << "\n";
    cout << data3D.cols;

}
void extrinsics(Mat data3D) {
    cout << "This is extrinscis Matrix";
    //Defining all the Rotation nd Translation matrix
    int theta = 0;
    int t_x = 0;
    int t_y = 0;


    String a;
    cout << "Data 3D rows " << "\n" << data3D.rows;
    cout << "Data 3D cols " << "\n" << data3D.cols;
    while (true) {
        cout << "Enter the value of a";
        cin >> a;
        //A==1,2 Roation in x axis
            /*
             Press ‘1’ key to rotate the image about x-axis clockwise, e.g. increasing 5
             degrees.
             - Press ‘2’ key to rotate the image about x-axis anti-clockwise, e.g. decreasing 5
             degrees.
             - Press ‘a’ key to translate the camera along x-axis by 10 units.
             - Press ‘d’ key to translate the camera along x-axis by -10 units.
             - Press ‘w’ key to translate the camera along y-axis by 10 units.
             - Press ‘s’ key to translate the camera along y-axis by -10 units.
             - Press ‘z’ key to increase the focal length, e.g. +30 pixels.
             - Press ‘x’ key to decrease the focal length, e.g. -30 pixels.
             - Press ‘r’ key to restart the virtual camera extrinsics.
             - Press ‘o’ key to output the virtual image to a local file
             */
        if (a == "1") {
            theta = theta + 5;
            double radians = theta * M_PI / 180.0;
            double sin = abs(std::sin(radians));
            double cos = abs(std::cos(radians));
            Rotat_x = (Mat_<double>(4, 4) << 1, 0, 0, 0, 0, cos, -sin, 0, 0, sin, cos, 0, 0, 0, 0, 1);
            data3D = data3D.mul(Rotat_x);
            cout << Rotat_x;
            cout << "\n";
        }
        if (a == "2") {
            theta = theta - 5;
            double radians = theta * M_PI / 180.0;
            double sin = abs(std::sin(radians));
            double cos = abs(std::cos(radians));
            Rotat_x = (Mat_<double>(4, 4) << 1, 0, 0, 0, 0, cos, -sin, 0, 0, sin, cos, 0, 0, 0, 0, 1);
            data3D = data3D.mul(Rotat_x);
            cout << Rotat_x;
            cout << "\n";
        }
        if (a == "3") {
            theta = theta + 5;
            double radians = theta * M_PI / 180.0;
            double sin = abs(std::sin(radians));
            double cos = abs(std::cos(radians));
            Rotat_x = (Mat_<double>(4, 4) << cos, 0, sin, 0, 0, 1, 0, 0, -sin, 0, cos, 0, 0, 0, 0, 1);
            data3D = data3D.mul(Rotat_x);
            cout << Rotat_x;
            cout << "\n";
        }
        if (a == "4") {
            theta = theta + 5;
            double radians = theta * M_PI / 180.0;
            double sin = abs(std::sin(radians));
            double cos = abs(std::cos(radians));
            Rotat_x = (Mat_<double>(4, 4) << cos, 0, sin, 0, 0, 1, 0, 0, -sin, 0, cos, 0, 0, 0, 0, 1);
            data3D = data3D.mul(Rotat_x);
            cout << Rotat_x;
            cout << "\n";
        }
        if (a == "5") {
            theta = theta - 5;
            double radians = theta * M_PI / 180.0;
            double sin = abs(std::sin(radians));
            double cos = abs(std::cos(radians));
            Rotat_x = (Mat_<double>(3, 3) << cos, -sin, 0, sin, cos, 0, 0, 0, 1);
            data3D = data3D.mul(Rotat_x);
            cout << Rotat_x;
            cout << "\n";
        }
        if (a == "6") {
            theta = theta + 5;
            double radians = theta * M_PI / 180.0;
            double sin = abs(std::sin(radians));
            double cos = abs(std::cos(radians));
            Rotat_x = (Mat_<double>(3, 3) << cos, -sin, 0, sin, cos, 0, 0, 0, 1);
            data3D = data3D.mul(Rotat_x);
            cout << Rotat_x;
            cout << "\n";
        }

        if (a == "a") {
            t_x += 10;
            Trans = (Mat_<int>(3, 3) << 1, 0, t_x, 0, 1, t_y, 0, 0, 1);
            cout << Trans;
            data3D = data3D.mul(Trans);
            cout << "\n";
        }
        if (a == "d") {
            t_x -= 10;
            Trans = (Mat_<int>(3, 3) << 1, 0, t_x, 0, 1, t_y, 0, 0, 1);
            data3D = data3D.mul(Trans);

            cout << Trans;
            cout << "\n";
        }
        if (a == "w") {
            t_y += 10;
            Trans = (Mat_<int>(3, 3) << 1, 0, t_x, 0, 1, t_y, 0, 0, 1);
            data3D = data3D.mul(Trans);
            cout << Trans;
            cout << "\n";
        }
        if (a == "s") {
            t_y -= 10;
            Trans = (Mat_<int>(3, 3) << 1, 0, t_x, 0, 1, t_y, 0, 0, 1);
            data3D = data3D.mul(Trans);
            cout << Trans;
            cout << "\n";
        }
        if (a == "z") {

            focal_length += 30;

        }
        if (a == "x")
            focal_length -= 30;
        if (a == "r") {
            theta = 0;
            t_y = 0;
            t_x = 0;
            focal_length = 524;
        }

        if (a == "o")
            break;

    }
}
void render() {
    Mat img2;
    img2.create(480, 640, CV_16UC3);
    Mat intristic = (Mat_<double>(3, 4) << focal_length, 0, Cx, 0, 0, focal_length, Cy, 0, 0, 0, 1, 0);
    cout << intristic;
    New_Data3D = intristic * data3D;
    cout << "\n";
    cout << New_Data3D.rows;
    cout << "\n";
    cout << New_Data3D.cols;
    cout << "The value of new matrix are ";
    //cout << New_Data3D;
//converting this New_Data Matrix back to pixels


}


int main(int argc, const char* argv[]) {
    Mat img = imread("./color.jpeg");

    int rows = img.rows;
    int cols = img.cols;
    //cout << img;
    cout << "Reading the file \n";
    Mat depth;
    depth.create(rows, cols, CV_16UC1);
    FILE* fp = fopen("./depth.dat", "rb");
    fread(depth.data, 2, (rows * cols), fp);

    cout << "Printing the data\n";

    imshow("Original Image ", img);
    imshow("Depth Image", depth * 20);
    waitKey(0);
    cout << "\n";
    cout << rows;
    cout << "\n";
    cout << cols;
    cout << "\n";
    cout << "Distance Matrix is \n";
    //cout << depth;
    cout << depth.rows;
    cout << "\n";
    cout << depth.cols;
    cout << "\n";
    convert2D_to_3D(img, depth);


    extrinsics(data3D);
    render();
    //Printing all the data in data3d
// cout << data3D;
    cout << "Printing Data ";
    cout << "\n";

    cout << "\n";

    fclose(fp);

    return 0;
}
