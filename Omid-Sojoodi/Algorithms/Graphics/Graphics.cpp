// # ifndef ALGORITHMS_OMID_SOJOODI_GRAPHICS
# include "Graphics.hpp"
# include <iostream>
cv::Scalar WINDOW_BACKGROUND(20, 10, 2);
//-- Constructor
Point::Point() {
    x = 0;
    y = 0;
    theta = 0;
}
//-- Constructor
Graphics::Graphics() {
    window = cv::Mat(
        WINDOW_HEIGHT,
        WINDOW_WIDTH,
        CV_8UC3,
        WINDOW_BACKGROUND
    );
    int width, height;
    Display* disp = XOpenDisplay(NULL);
    Screen* scrn = DefaultScreenOfDisplay(disp);
    XCloseDisplay(disp);
    height = scrn->height;
    width = scrn->width;
    cv::imshow(WINDOW_NAME, window);
    cv::moveWindow(
        WINDOW_NAME,
        width / 2 - WINDOW_WIDTH / 2,
        height / 2 - WINDOW_HEIGHT / 2
    );
    //-- Print Welcome Message in the Middle
    cv::imshow(WINDOW_NAME, window);
    cv::waitKey(1);
}
// # endif // ALGORITHMS_OMID_SOJOODI_GRAPHICS