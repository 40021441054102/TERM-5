# ifndef AI_BABAK_KARASFI_CHESS
    //-- Include Header File
    # include "Chess.hpp"
    //-- Piece Class Constructor
    Piece::Piece(
        std::int8_t &_color,
        std::int8_t &_id,
        bool &_status
    ) {
        onboard_status = _status;
        color = _color;
        id = _id;
    }
    //-- Chess Class Constructor
    Chess::Chess(
        int &_size
    ) {
        home.resize(0);
        board.size = _size;
        board.window = cv::Mat(
            board.size,
            board.size,
            CV_8UC3,
            cv::Scalar(10, 5, 0)
        );
        //-- Find Center Pixel
        Display* disp = XOpenDisplay(NULL);
        Screen* scrn = DefaultScreenOfDisplay(disp);
        cv::imshow("Chess Board", board.window);
        cv::moveWindow(
            "Chess Board",
            scrn->width / 2 - board.size / 2,
            scrn->height / 2 - board.size / 2
        );
        XCloseDisplay(disp);
        // board.pieces.resize(0);
        board.piecesImages.resize(0);
        //-- Set Mouse Callback
        cv::setMouseCallback("Chess Board", onMouseCallback, this);
        //-- Initialize Mouse Section to Default in Pieces Section
        section = SEC_PIECES;
    }
    //-- OnMouseCallback Method
    void Chess::onMouseCallback(int event, int x, int y, int flags, void* userdata) {
        static_cast<Chess*>(userdata)->onMouse(event, x, y, flags);
    }
    //-- Mouse Callbacks Handling
    void Chess::onMouse(int event, int x, int y, int flags) {
        switch (event) {
            //-- Left Button Down
            case cv::EVENT_LBUTTONDOWN: {
                if (section == SEC_PIECES) {
                    std::cout << TAB LOG "Selected" ENDL;
                }
                break;
            };
            //-- Left Button Up
            case cv::EVENT_LBUTTONUP: {
                if (section == SEC_PIECES) {
                    std::cout << TAB LOG "Free" ENDL;
                }
                break;
            };
            case cv::EVENT_MOUSEMOVE: {
                if (x > board.size) {
                    if (section == SEC_GAME) {
                        std::cout << LOG "Choose Piece" ENDL;
                    }
                    section = SEC_PIECES;
                } else {
                    if (section == SEC_PIECES) {
                        std::cout << LOG "Select and Move Piece" ENDL;
                    }
                    section = SEC_GAME;
                }
                break;
            }
        };
    }
    //-- Generate Chess Board
    void Chess::generateChessBoard() {
        ChessHome new_home;
        new_home.size = board.size / 8;
        std::cout << LOG "Generating Chess Homes" ENDL;
        char row;
        for (int i = 0; i < 8; i++) {
            row = char(65 + i);
            for (int j = 0; j < 8; j++) {
                new_home.x = board.size * i / 8;
                new_home.y = board.size * j / 8;
                new_home.center_x = (new_home.x) + new_home.size / 2;
                new_home.center_y = (new_home.y) + new_home.size / 2;
                new_home.name.erase();
                new_home.name.resize(0);
                new_home.name.push_back(row);
                new_home.name.push_back(char(49 + j));
                std::cout << TAB LOG "Home " << new_home.name <<" has been Generated at " << new_home.center_x << " x " << new_home.center_y << ENDL;
                home.push_back(new_home);
                cv::circle(
                    board.window,
                    cv::Point(
                        new_home.center_x,
                        new_home.center_y
                    ),
                    5,
                    cv::Scalar(255, 255, 0),
                    -1,
                    cv::LINE_AA,
                    0
                );
                cv::imshow("Chess Board", board.window);
                cv::waitKey(SPEED * 2);
            }
        }
        for (int i = 0; i < 64; i++) {
            cv::rectangle(
                board.window,
                cv::Point(
                    home.at(i).x,
                    home.at(i).y
                ),
                cv::Point(
                    home.at(i).x + home.at(i).size,
                    home.at(i).y + home.at(i).size
                ),
                cv::Scalar(55, 55, 0),
                2,
                cv::LINE_AA,
                0
            );
            cv::imshow("Chess Board", board.window);
            cv::waitKey(SPEED);
        }
        for (int i = 0; i < 64; i++) {
            cv::putText(
                board.window,
                home.at(i).name,
                cv::Point(
                    home.at(i).center_x - 37,
                    home.at(i).center_y + 85
                ),
                cv::FONT_HERSHEY_SIMPLEX,
                2,
                cv::Scalar(240, 150, 150)
            );
            cv::imshow("Chess Board", board.window);
            cv::waitKey(SPEED);
        }
        int sign = 1;
        int color = 0;
        for (int i = 0; i < 64; i++) {
            if (i % 8 != 0) {
                sign *= -1;
            }
            if (sign == -1) {
                color = 0;
            } else {
                color = 255;
            }
            cv::rectangle(
                board.window,
                cv::Point(
                    home.at(i).x,
                    home.at(i).y
                ),
                cv::Point(
                    home.at(i).x + home.at(i).size,
                    home.at(i).y + home.at(i).size
                ),
                cv::Scalar(color, color, color),
                -1,
                cv::LINE_AA,
                0
            );
            cv::imshow("Chess Board", board.window);
            cv::waitKey(SPEED);
        }
        sign = 1;
        cv::Scalar rgbColor;
        for (int i = 0; i < 64; i++) {
            if (i % 8 != 0) {
                sign *= -1;
            }
            if (sign == -1) {
                rgbColor = cv::Scalar(46, 58, 87);
            } else {
                rgbColor = cv::Scalar(93, 120, 138);
            }
            cv::rectangle(
                board.window,
                cv::Point(
                    home.at(i).x,
                    home.at(i).y
                ),
                cv::Point(
                    home.at(i).x + home.at(i).size,
                    home.at(i).y + home.at(i).size
                ),
                rgbColor,
                -1,
                cv::LINE_AA,
                0
            );
            cv::imshow("Chess Board", board.window);
            cv::waitKey(SPEED);
        }
    }
    //-- Load Chess Pieces
    void Chess::loadChessPieces() {
        DIR *file;
        std::string address;
        struct dirent *action;
        file = opendir(PATH);
        std::cout << LOG "Loading Chess Pieces" ENDL;
        if (file) {
            Display* disp = XOpenDisplay(NULL);
            Screen* scrn = DefaultScreenOfDisplay(disp);
            cv::imshow("Chess Board", board.window);
            std::cout << TAB SUCCESS << PATH << " Directory has been Opened" ENDL;
            cv::Mat chessboard;
            board.window.copyTo(chessboard);
            int panel_width = board.size * 0.313;
            int addition = 2;
            while (true) {
                cv::resize(
                    board.window,
                    board.window,
                    cv::Size(board.size + addition, board.size),
                    cv::INTER_LINEAR
                );
                cv::rectangle(
                    board.window,
                    cv::Point(0, 0),
                    cv::Point(board.window.cols, board.window.rows),
                    cv::Scalar(120, 120, 120),
                    -1,
                    cv::LINE_AA,
                    0
                );
                for (int i = 0; i < chessboard.rows; i++) {
                    for (int j = 0; j < chessboard.cols; j++) {
                        board.window.at<cv::Vec3b>(i, j)[0] = chessboard.at<cv::Vec3b>(i, j)[0];
                        board.window.at<cv::Vec3b>(i, j)[1] = chessboard.at<cv::Vec3b>(i, j)[1];
                        board.window.at<cv::Vec3b>(i, j)[2] = chessboard.at<cv::Vec3b>(i, j)[2];
                    }
                }
                cv::imshow("Chess Board", board.window);
                cv::moveWindow(
                    "Chess Board",
                    scrn->width / 2 - board.window.cols / 2,
                    scrn->height / 2 - board.size / 2
                );
                cv::waitKey(1);
                addition += 16;
                if (addition > panel_width) {
                    break;
                }
            }
            XCloseDisplay(disp);
            for (int i = 0; i < 64; i++) {
                cv::putText(
                    board.window,
                    home.at(i).name,
                    cv::Point(
                        home.at(i).center_x + 50,
                        home.at(i).center_y + 92
                    ),
                    cv::FONT_HERSHEY_SIMPLEX,
                    1,
                    cv::Scalar(0, 0, 0),
                    2
                );
                cv::imshow("Chess Board", board.window);
                cv::waitKey(SPEED);
            }
            //-- Load Pieces Images
            while ((action = readdir(file)) != NULL) {
                address = action->d_name;
                std::cout << TAB LOG "File " << address << " has been Loaded" << ENDL;
                if (
                    address[address.size() - 1] == 'g',
                    address[address.size() - 2] == 'n',
                    address[address.size() - 3] == 'p'
                ) {
                    Board::PieceImage tmpPiece;
                    cv::Mat input;
                    input = cv::imread(PATH + address, cv::IMREAD_COLOR);
                    cv::resize(
                        input, tmpPiece.image,
                        cv::Size(home.at(0).size * 3 / 4, home.at(0).size * 3 / 4),
                        cv::INTER_LINEAR
                    );
                    // cv::cvtColor(input, tmpPiece.image, cv::COLOR_BGR2Luv);
                    board.piecesImages.push_back(tmpPiece);
                    if (address[0] == 'b' && address[1] == 'd') {
                        std::cout << TAB TAB SUCCESS "Black Bishop Detected" ENDL;
                    } else if (address[0] == 'k' && address[1] == 'd') {
                        std::cout << TAB TAB SUCCESS "Black King Detected" ENDL;
                    } else if (address[0] == 'n' && address[1] == 'd') {
                        std::cout << TAB TAB SUCCESS "Black Knight Detected" ENDL;
                    } else if (address[0] == 'p' && address[1] == 'd') {
                        std::cout << TAB TAB SUCCESS "Black Pawn Detected" ENDL;
                    } else if (address[0] == 'q' && address[1] == 'd') {
                        std::cout << TAB TAB SUCCESS "Black Queen Detected" ENDL;
                    } else if (address[0] == 'r' && address[1] == 'd') {
                        std::cout << TAB TAB SUCCESS "Black Castle Detected" ENDL;
                    } else if (address[0] == 'b' && address[1] == 'l') {
                        std::cout << TAB TAB SUCCESS "White Bishop Detected" ENDL;
                    } else if (address[0] == 'k' && address[1] == 'l') {
                        std::cout << TAB TAB SUCCESS "White King Detected" ENDL;
                    } else if (address[0] == 'n' && address[1] == 'l') {
                        std::cout << TAB TAB SUCCESS "White Knight Detected" ENDL;
                    } else if (address[0] == 'p' && address[1] == 'l') {
                        std::cout << TAB TAB SUCCESS "White Pawn Detected" ENDL;
                    } else if (address[0] == 'q' && address[1] == 'l') {
                        std::cout << TAB TAB SUCCESS "White Queen Detected" ENDL;
                    } else if (address[0] == 'r' && address[1] == 'l') {
                        std::cout << TAB TAB SUCCESS "White Castle Detected" ENDL;
                    }
                    std::cout << TAB TAB SUCCESS "Imported" ENDL;
                } else {
                    std::cout << TAB TAB FAILED "Can Not Import Because It is Not PNG" ENDL;
                }
            }
            // int padding = panel_width - (2 * home.at(0).size); 
            int padding = board.window.cols - board.size;
            cv::Point startPoint(board.size + 50, 40);
            cv::imshow("Chess Board", board.window);
            // std::cout << padding << ENDL;
            int startposx = 0, startposy = 0;
            cv::Mat tmp;
            board.window.copyTo(tmp);
            //-- Draw Pieces Sections
            for (int i = 0; i < board.piecesImages.size(); i++) {
                if (i <= 5) {
                    startposx = home.at(i).x + startPoint.x;
                    startposy = home.at(i).y + startPoint.y;
                } else {
                    startposx = home.at(i + 2).x + startPoint.x + 40;
                    startposy = home.at(i + 2).y + startPoint.y;
                }
                for (
                    int x = startposx;
                    x < startposx + home.at(i).size * 3 / 4;
                    x++
                ) {
                    for (
                        int y = startposy;
                        y < startposy + home.at(i).size * 3 / 4;
                        y++
                    ) {
                        int height = 0;
                        if (i <= 5) {
                            height = y + i * 10;
                        } else {
                            height = y + (i - 5) * 10 - 10;
                        }
                        if (x == startposx && y == startposy) {
                            board.piecesImages.at(i).size = board.piecesImages.at(i).image.cols;
                            board.piecesImages.at(i).y = height;
                            board.piecesImages.at(i).x = x;
                        }
                        if (x % 8 == 0 && y % 8 == 0) {
                            cv::circle(
                                board.window,
                                cv::Point(x, height),
                                2,
                                cv::Scalar(200, 0, 0),
                                -1,
                                cv::LINE_AA,
                                0
                            );
                            if (x % 40 == 0 && y % 32 == 0) {
                                cv::waitKey(1);
                                cv::imshow("Chess Board", board.window);
                            }
                        }
                    }
                }
                cv::imshow("Chess Board", board.window);
                cv::waitKey(50);
            }
            cv::imshow("Chess Board", board.window);
            //-- Draw Pieces Box
            for (int i = 0; i < board.piecesImages.size(); i++) {
                for (
                    int x = board.piecesImages.at(i).x, x1 = 0;
                    x < board.piecesImages.at(i).x + board.piecesImages.at(i).size;
                    x++, x1++
                ) {
                    for (
                        int y = board.piecesImages.at(i).y, y1 = 0;
                        y < board.piecesImages.at(i).y + board.piecesImages.at(i).size;
                        y++, y1++
                    ) {
                        cv::circle(
                            board.window,
                            cv::Point(x, y),
                            2,
                            cv::Scalar(100, 100, 100),
                            -0,
                            cv::LINE_4,
                            0
                        );
                    }
                }
                cv::waitKey(50);
                cv::imshow("Chess Board", board.window);
            }
            //-- Add Pieces to Board
            int r, g, b;
            cv::Vec3b pixel;
            for (int i = 0; i < board.piecesImages.size(); i++) {
                for (
                    int x = board.piecesImages.at(i).x, x1 = 0;
                    x < board.piecesImages.at(i).x + board.piecesImages.at(i).size;
                    x++, x1++
                ) {
                    for (
                        int y = board.piecesImages.at(i).y, y1 = 0;
                        y < board.piecesImages.at(i).y + board.piecesImages.at(i).size;
                        y++, y1++
                    ) {
                        pixel = board.piecesImages.at(i).image.at<cv::Vec3b>(y1, x1);
                        r = static_cast<int>(pixel[0]);
                        g = static_cast<int>(pixel[1]);
                        b = static_cast<int>(pixel[2]);
                        board.window.at<cv::Vec3b>(y, x)[0] = b;
                        board.window.at<cv::Vec3b>(y, x)[1] = g;
                        board.window.at<cv::Vec3b>(y, x)[2] = r;
                    }
                }
                cv::waitKey(50);
                cv::imshow("Chess Board", board.window);
            }
        } else {
            std::cout << TAB FAILED << "Can Not Open Path " << PATH << ENDL;
        }
    }
    //-- Main
    int main() {
        int size = 1600;
        Chess chess(size);
        cv::waitKey(0);
        chess.generateChessBoard();
        // cv::waitKey(0);
        chess.loadChessPieces();
        cv::waitKey(0);
    }

# endif // AI_BABAK_KARASFI_CHESS