/* Class CreateShapes by Liam Lawrence on 11.28.16
 * Sets up constructor for the CreateShapes class
 */

#include "opencv2/videoio.hpp"
#ifndef INC_2017_PRESEASON_CODE_CREATESSHAPES_HPP
#define INC_2017_PRESEASON_CODE_CREATESSHAPES_HPP

using namespace std;

class CreateShapes {
public:
    static vector<cv::Point> shapes(cv::Mat &frame, int idx, vector<vector<cv::Point>> contours);
private:
    static string ld;
};


#endif //INC_2017_PRESEASON_CODE_CREATESSHAPES_HPP
