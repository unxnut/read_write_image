#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

int main(int argc, const char** argv)
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "usage: " << argv[0] << " image_file" << std::endl;
			return (1);
		}

		// Read the image

		cv::Mat image = cv::imread(argv[1]);

		// Make sure that the image is read properly.

		if (image.empty())
			throw (std::string("Cannot open input image ") + argv[1]);

		// Image dimensions

		std::cout << "Image size is: " << image.cols << "x" << image.rows << std::endl;

		// Read the same image as grayscale image.

		cv::Mat img_gray = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

		// Display color image

		cv::imshow("Color Rendering", image);
		cv::waitKey();

		// Display grayscale image

		cv::imshow("Grayscale Rendering", img_gray);
		cv::waitKey();

		// Save a copy of grayscale image in a file on disk.

		std::string gray_pic_file = argv[1];
		gray_pic_file.insert(gray_pic_file.find_last_of('.'), "_gray");
		cv::imwrite(gray_pic_file, img_gray);

		// Display value at a random pixel

		srand(static_cast<uint>(time(NULL)));

		uint r = rand() % image.rows;
		uint c = rand() % image.cols;

		cv::Vec3b pxl_color = image.at<cv::Vec3b>(r, c);

		std::cout << "Color pixel at (" << r << "," << c << ") = (" << (int)pxl_color[0] << ","
			<< (int)pxl_color[1] << "," << (int)pxl_color[2] << ")" << std::endl;

		uchar pxl_gray = img_gray.at<uchar>(r, c );
		std::cout << "Gray scale pixel at (" << r << "," << c << ") = " << (int)pxl_gray << std::endl;
	}
	catch (std::string& str)
	{
		std::cerr << "Error: " << argv[0] << ": " << str << std::endl;
		return (1);
	}
	catch (cv::Exception& e)
	{
		std::cerr << "Error: " << argv[0] << ": " << e.msg << std::endl;
		return (1);
	}

	return (0);
}