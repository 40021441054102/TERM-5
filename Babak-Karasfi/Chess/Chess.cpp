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
    //-- Method to Set Color of Piece
    void Piece::setColor(int &_in) {
        color = _in;
        std::cout << TAB TAB TAB INFO "Color ID : " << color << std::endl;
    }
    //-- Method to Set ID of Piece
    void Piece::setID(int &_in) {
        id = _in;
        std::cout << TAB TAB TAB INFO "Piece ID : " << id << std::endl;
    }
    //-- Method to Set Home of Piece
    void Piece::setHome(int &_home) {
        home = _home;
        std::cout << TAB TAB TAB INFO "Home ID : " << home << std::endl;
    }
    //-- Method to Set On Board Status of Piece
    void Piece::setOnBoard(bool &_in) {
        onboard_status = _in;
    }
    //-- Method to Get Piece Information
    PieceInfo Piece::getInfo() {
        PieceInfo tmp;
        tmp.color = color;
        tmp.home = home;
        tmp.id = id;
        return tmp;
    }
    //-- Method to Find Piece Move Homes
    void Piece::findMoveHomes() {
        switch (id) {
            case CHESS_KING: {
                switch (home) {
                    //-- Handle Corner Homes
                    case CHESS_A1: {
                        moveHomes.push_back(home + 8);
                        moveHomes.push_back(home + 1);
                        moveHomes.push_back(home + 8 + 1);
                        break;
                    };
                    case CHESS_A8: {
                        moveHomes.push_back(home + 8);
                        moveHomes.push_back(home - 1);
                        moveHomes.push_back(home + 8 - 1);
                        break;
                    };
                    case CHESS_H1: {
                        moveHomes.push_back(home - 8);
                        moveHomes.push_back(home + 1);
                        moveHomes.push_back(home - 8 + 1);
                        break;
                    };
                    case CHESS_H8: {
                        moveHomes.push_back(home - 8);
                        moveHomes.push_back(home - 1);
                        moveHomes.push_back(home - 8 - 1);
                        break;
                    };
                    default: {
                        for (int i = 0; i < 8; i++) {
                            if (home == i * 8 + 8) {
                                moveHomes.push_back(home + 8);
                            } else if (home == i * 8 + 1) {
                                //
                            } else if (home == i + 8 - i) {

                            }
                        }
                    }
                };
                break;
            };
            case CHESS_PAWN: {
                break;
            };
            case CHESS_QUEEN: {
                break;
            };
            case CHESS_BISHOP: {
                break;
            };
            case CHESS_CASTLE: {
                break;
            };
            case CHESS_KNIGHT: {
                break;
            };
        };
    }
    //-- Method to Get Piece Move Homes
    std::vector<int> Piece::getMoveHomes() {
        findMoveHomes();
    }
    //-- Method to Get Piece Attack Homes
    std::vector<int> Piece::getAttackHomes() {

    }
    //-- Chess Class Constructor
    Chess::Chess(
        int &_size
    ) {
        total = 32;
        home.resize(0);
        programState = STATE_PLACE_PIECES;
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
        //-- Set Selected Piece Flag to False
        selected.flag = SELECT_NONE;
    }
    //-- Method to Check if Piece ID is Placeable or Not
    bool Chess::checkPlaceable(
        int _piece,
        int _color,
        int _home_color
    ) {
        // switch (_piece) {
        //     //-- Chess King
        //     case CHESS_KING: {
        //         break;
        //     };
        //     //-- Chess Queen
        //     case CHESS_QUEEN: {
        //         break;
        //     };
        //     //-- Chess Pawn
        //     case CHESS_PAWN: {
        //         break;
        //     };
        //     //-- Chess Bishop
        //     case CHESS_BISHOP: {
        //         if (_color == CHESS_DARK && _home_color == CHESS_LIGHT) {
                    
        //         } else if {

        //         }
        //         break;
        //     };
        //     //-- Chess Castle
        //     case CHESS_CASTLE: {
        //         break;
        //     };
        //     //-- Chess Knight
        //     case CHESS_KNIGHT: {
        //         break;
        //     };
        // }
    }
    //-- OnMouseCallback Method
    void Chess::onMouseCallback(int event, int x, int y, int flags, void* userdata) {
        static_cast<Chess*>(userdata)->onMouse(event, x, y, flags);
    }
    //-- Mouse Callbacks Handling
    void Chess::onMouse(int event, int x, int y, int flags) {
        // if (programState = STATE_PLACE_PIECES) {
        switch (event) {
            //-- Left Button Down
            case cv::EVENT_LBUTTONDOWN: {
                // std::cout << selected.flag << std::endl;
                // std::cout << "Needed " << SELECT_NONE << " or " << SELECT_PICK << std::endl;
                if (section == SEC_PIECES) {
                    for (int i = 0; i < board.piecesImages.size(); i++) {
                        if (
                            x >= board.piecesImages.at(i).x
                            &&
                            x < board.piecesImages.at(i).x + board.piecesImages.at(i).size
                        ) {
                            if (
                                y >= board.piecesImages.at(i).y
                                &&
                                y < board.piecesImages.at(i).y + board.piecesImages.at(i).size
                            ) {
                                std::cout << TAB SUCCESS "Piece (" << board.piecesImages.at(i).name << ", " << board.piecesImages.at(i).color << ") Selected" << ENDL;
                                cv::Mat tmp;
                                board.window.copyTo(tmp);
                                cv::rectangle(
                                    tmp,
                                    cv::Point(
                                        board.piecesImages.at(i).x,
                                        board.piecesImages.at(i).y
                                    ),
                                    cv::Point(
                                        board.piecesImages.at(i).x + board.piecesImages.at(i).size,
                                        board.piecesImages.at(i).y + board.piecesImages.at(i).size
                                    ),
                                    cv::Scalar(0, 100, 0),
                                    4,
                                    cv::LINE_AA,
                                    0
                                );
                                cv::rectangle(
                                    tmp,
                                    cv::Point(
                                        board.piecesImages.at(i).x - 2,
                                        board.piecesImages.at(i).y + board.piecesImages.at(i).size
                                    ),
                                    cv::Point(
                                        board.piecesImages.at(i).x + board.piecesImages.at(i).size + 2,
                                        board.piecesImages.at(i).y + board.piecesImages.at(i).size + 40
                                    ),
                                    cv::Scalar(0, 100, 0),
                                    -1,
                                    cv::LINE_AA,
                                    0
                                );
                                cv::putText(
                                    tmp,
                                    board.piecesImages.at(i).color + " " + board.piecesImages.at(i).name,
                                    cv::Point(
                                        board.piecesImages.at(i).x + 10,
                                        board.piecesImages.at(i).y + board.piecesImages.at(i).size + 25
                                    ),
                                    cv::FONT_HERSHEY_SIMPLEX,
                                    0.7,
                                    cv::Scalar(0, 255, 0),
                                    2
                                );
                                selected.flag = SELECT_PICK;
                                selected.x = board.piecesImages.at(i).x;
                                selected.y = board.piecesImages.at(i).y;
                                selected.size = board.piecesImages.at(i).size;
                                selected.id = i;
                                cv::imshow("Chess Board", tmp);
                                break;
                            }
                        }
                    }
                } else if (section == SEC_GAME) {
                    if (tobePlaced.flag == HOME_EMPTY) {
                        {
                    //     int r, g, b;
                    //     cv::Vec3b pixel;
                    //     cv::Mat tmp, piece;
                    //     board.window.copyTo(tmp);
                    //     board.piecesImages.at(tobePlaced.id).image.copyTo(piece);
                    //     int placedWidth = home.at(0).size * PIECE_PLACE_SIZE;
                    //     int placedHeight = home.at(0).size * PIECE_PLACE_SIZE;
                    //     cv::resize(piece, piece, cv::Size(
                    //         placedWidth,
                    //         placedHeight
                    //     ), cv::INTER_LINEAR);
                    //     std::cout << "debug1" << std::endl;
                    //     std::cout << "debug2" << std::endl;
                    //     for (int i = 0; i < tobePlaced.size; i++) {
                    //         for (int j = 0; j < tobePlaced.size; j++) {
                    //             pixel = piece.at<cv::Vec3b>(i, j);
                    //             r = static_cast<int>(pixel[0]);
                    //             g = static_cast<int>(pixel[1]);
                    //             b = static_cast<int>(pixel[2]);
                    //             if (
                    //                 (r < 95 || r > 105) &&
                    //                 (g < 95 || g > 105) &&
                    //                 (b < 95 || b > 105)
                    //             ){
                    //                 tmp.at<cv::Vec3b>(tobePlaced.y, tobePlaced.x)[0] = int(int(b) / 2);
                    //                 tmp.at<cv::Vec3b>(tobePlaced.y, tobePlaced.x)[1] = int(int(g) / 2);
                    //                 tmp.at<cv::Vec3b>(tobePlaced.y, tobePlaced.x)[2] = int(int(r) / 2);
                    //             }
                    //         }
                    //     }
                        }
                        cv::Mat tmp, fadePiece;
                        tempMat1.copyTo(tmp);
                        board.piecesImages.at(selected.id).image.copyTo(pieceImage);
                        pieceImage.copyTo(fadePiece);
                        int placedWidth = home.at(0).size * PIECE_PLACE_SIZE;
                        int placedHeight = home.at(0).size * PIECE_PLACE_SIZE;
                        int widthPadding = (home.at(0).size - placedWidth) / 2;
                        int heightPadding = (home.at(0).size - placedHeight) / 2;
                        cv::resize(fadePiece, fadePiece, cv::Size(
                            placedWidth,
                            placedHeight
                        ), cv::INTER_LINEAR);
                        int r, g, b;
                        cv::Vec3b pixel;
                        for (int i = 0; i < fadePiece.cols; i++) {
                            for (int j = 0; j < fadePiece.rows; j++) {
                                pixel = fadePiece.at<cv::Vec3b>(i, j);
                                r = static_cast<int>(pixel[0]);
                                g = static_cast<int>(pixel[1]);
                                b = static_cast<int>(pixel[2]);
                                if (
                                    (r < 95 || r > 105) &&
                                    (g < 95 || g > 105) &&
                                    (b < 95 || b > 105)
                                ){
                                    tmp.at<cv::Vec3b>(tobePlaced.y + i, tobePlaced.x + j)[0] = int(int(b));
                                    tmp.at<cv::Vec3b>(tobePlaced.y + i, tobePlaced.x + j)[1] = int(int(g));
                                    tmp.at<cv::Vec3b>(tobePlaced.y + i, tobePlaced.x + j)[2] = int(int(r));
                                }
                            }
                        }
                        tobePlaced.flag = HOME_NOT_EMPTY;
                        home.at(tobePlaced.id).isFileld = HOME_NOT_EMPTY;
                        Piece tmpPiece;
                        tmp.copyTo(board.window);
                        std::cout << TAB SUCCESS "Piece has been Placed" ENDL;
                        tmpPiece.setHome(home.at(tobePlaced.id).id);
                        tmpPiece.setColor(board.piecesImages.at(selected.id).colorID);
                        tmpPiece.setID(board.piecesImages.at(selected.id).nameID);
                        pieces.push_back(tmpPiece);
                    } else {
                        std::cout << TAB FAILED "Can Not Place Piece" ENDL;
                    }
                }
                break;
            };
            //-- Left Button Up
            case cv::EVENT_LBUTTONUP: {
                if (selected.flag = SELECT_PICK) {
                    selected.flag = SELECT_MOVE;
                    cv::Mat tmp;
                    board.window.copyTo(tmp);
                    cv::rectangle(
                        tmp,
                        cv::Point(
                            selected.x,
                            selected.y
                        ),
                        cv::Point(
                            selected.x + selected.size,
                            selected.y + selected.size
                        ),
                        cv::Scalar(0, 255, 255),
                        2,
                        cv::LINE_AA,
                        0
                    );
                    cv::imshow("Chess Board", tmp);
                    tmp.copyTo(tempMat1);
                    break;
                }
            };
            //-- Mouse Hover
            case cv::EVENT_MOUSEMOVE: {
                if (selected.flag == SELECT_PUT || selected.flag == SELECT_NONE) { // Blue Hover Box
                    for (int i = 0; i < board.piecesImages.size(); i++) {
                        if (
                            x >= board.piecesImages.at(i).x
                            &&
                            x < board.piecesImages.at(i).x + board.piecesImages.at(i).size
                        ) {
                            if (
                                y >= board.piecesImages.at(i).y
                                &&
                                y < board.piecesImages.at(i).y + board.piecesImages.at(i).size
                            ) {
                                cv::Mat tmp;
                                board.window.copyTo(tmp);
                                cv::rectangle(
                                    tmp,
                                    cv::Point(
                                        board.piecesImages.at(i).x,
                                        board.piecesImages.at(i).y
                                    ),
                                    cv::Point(
                                        board.piecesImages.at(i).x + board.piecesImages.at(i).size,
                                        board.piecesImages.at(i).y + board.piecesImages.at(i).size
                                    ),
                                    cv::Scalar(100, 100, 0),
                                    4,
                                    cv::LINE_AA,
                                    0
                                );
                                cv::rectangle(
                                    tmp,
                                    cv::Point(
                                        board.piecesImages.at(i).x - 2,
                                        board.piecesImages.at(i).y + board.piecesImages.at(i).size
                                    ),
                                    cv::Point(
                                        board.piecesImages.at(i).x + board.piecesImages.at(i).size + 2,
                                        board.piecesImages.at(i).y + board.piecesImages.at(i).size + 40
                                    ),
                                    cv::Scalar(100, 100, 0),
                                    -1,
                                    cv::LINE_AA,
                                    0
                                );
                                cv::putText(
                                    tmp,
                                    board.piecesImages.at(i).color + " " + board.piecesImages.at(i).name,
                                    cv::Point(
                                        board.piecesImages.at(i).x + 10,
                                        board.piecesImages.at(i).y + board.piecesImages.at(i).size + 25
                                    ),
                                    cv::FONT_HERSHEY_SIMPLEX,
                                    0.7,
                                    cv::Scalar(255, 255, 0),
                                    2
                                );
                                cv::imshow("Chess Board", tmp);
                                break;
                            }
                        }
                    }
                } else if (selected.flag = SELECT_MOVE) { // Moving Piece on Blue Box
                    cv::Mat tmp, fadePiece;
                    tempMat1.copyTo(tmp);
                    board.piecesImages.at(selected.id).image.copyTo(pieceImage);
                    pieceImage.copyTo(fadePiece);
                    // std::cout << "debug" << std::endl;
                    int resizeWidth = pieceImage.cols * PIECE_PICK_SIZE;
                    int resizeHeight = pieceImage.cols * PIECE_PICK_SIZE;
                    int placedWidth = home.at(0).size * PIECE_PLACE_SIZE;
                    int placedHeight = home.at(0).size * PIECE_PLACE_SIZE;
                    int widthPadding = (home.at(0).size - placedWidth) / 2;
                    int heightPadding = (home.at(0).size - placedHeight) / 2;
                    cv::resize(pieceImage, pieceImage, cv::Size(
                        resizeWidth,
                        resizeHeight
                    ), cv::INTER_LINEAR);
                    cv::resize(fadePiece, fadePiece, cv::Size(
                        placedWidth,
                        placedHeight
                    ), cv::INTER_LINEAR);
                    int r, g, b;
                    cv::Vec3b pixel;
                    //-- Check if is Placeable on Chess Home or Not
                    if (section == SEC_GAME) {
                        for (int h = 0; h < home.size(); h++) {
                            if (
                                x >= home.at(h).x &&
                                x < home.at(h).x + home.at(h).size
                            ) {
                                if (
                                    y >= home.at(h).y &&
                                    y < home.at(h).y + home.at(h).size
                                ) {
                                    cv::Scalar color;
                                    std::string status;
                                    if (home.at(h).isFileld == HOME_NOT_EMPTY) { // Piece Can Not be Placed
                                        color = cv::Scalar(0, 0, 255);
                                        status = "Can Not Place";
                                    } else if (home.at(h).isFileld == HOME_EMPTY) { // Piece Can be Placed
                                        color = cv::Scalar(0, 255, 0);
                                        status = "Ready to Place";
                                    } else { // Chess Board Home Status Unknown
                                        color = cv::Scalar(0, 255, 255);
                                    }
                                    cv::rectangle(
                                        tmp,
                                        cv::Point(
                                            home.at(h).x,
                                            home.at(h).y 
                                        ),
                                        cv::Point(
                                            home.at(h).x + home.at(h).size,
                                            home.at(h).y + home.at(h).size
                                        ),
                                        color,
                                        2,
                                        cv::LINE_AA,
                                        0
                                    );
                                    cv::Rect pos;
                                    cv::Point textPos;
                                    if (y <= board.size * 7 / 8) {
                                        pos = cv::Rect(
                                            cv::Point(
                                                home.at(h).x - 1,
                                                home.at(h).y + home.at(h).size
                                            ),
                                            cv::Point(
                                                home.at(h).x + home.at(h).size + 2,
                                                home.at(h).y + home.at(h).size + 40
                                            )
                                        );
                                        textPos = cv::Point(
                                            home.at(h).x + 6,
                                            home.at(h).y + home.at(h).size + 25
                                        );
                                    } else {
                                        pos = cv::Rect(
                                            cv::Point(
                                                home.at(h).x - 1,
                                                home.at(h).y
                                            ),
                                            cv::Point(
                                                home.at(h).x + home.at(h).size + 2,
                                                home.at(h).y - 40
                                            )
                                        );
                                        textPos = cv::Point(
                                            home.at(h).x + 6,
                                            home.at(h).y - 13
                                        );
                                    }
                                    cv::rectangle(
                                        tmp,
                                        pos,
                                        color,
                                        -1,
                                        cv::LINE_AA,
                                        0
                                    );
                                    cv::putText(
                                        tmp,
                                        status,
                                        textPos,
                                        cv::FONT_HERSHEY_SIMPLEX,
                                        0.7,
                                        cv::Scalar(0, 0, 0),
                                        2
                                    );
                                    tobePlaced.x = home.at(h).x + widthPadding;
                                    tobePlaced.y = home.at(h).y + heightPadding;
                                    tobePlaced.size = fadePiece.cols;
                                    tobePlaced.index = h + 1;
                                    tobePlaced.id = h;
                                    //-- Preload Image Inside Chess Home
                                    if (home.at(h).isFileld == HOME_EMPTY) {
                                        tobePlaced.flag = HOME_EMPTY;
                                        for (int i = 0; i < fadePiece.cols; i++) {
                                            for (int j = 0; j < fadePiece.rows; j++) {
                                                pixel = fadePiece.at<cv::Vec3b>(i, j);
                                                r = static_cast<int>(pixel[0]);
                                                g = static_cast<int>(pixel[1]);
                                                b = static_cast<int>(pixel[2]);
                                                if (
                                                    (r < 95 || r > 105) &&
                                                    (g < 95 || g > 105) &&
                                                    (b < 95 || b > 105)
                                                ){
                                                    tmp.at<cv::Vec3b>(widthPadding + home.at(h).y + i, heightPadding + home.at(h).x + j)[0] = int(int(b) / 2);
                                                    tmp.at<cv::Vec3b>(widthPadding + home.at(h).y + i, heightPadding + home.at(h).x + j)[1] = int(int(g) / 2);
                                                    tmp.at<cv::Vec3b>(widthPadding + home.at(h).y + i, heightPadding + home.at(h).x + j)[2] = int(int(r) / 2);
                                                }
                                            }
                                        }
                                    } else {
                                        tobePlaced.flag = HOME_NOT_EMPTY;
                                    }
                                }
                            }
                        }
                    }
                    //-- Load Image Inside Box
                    for (int i = 0; i < pieceImage.cols; i++) {
                        for (int j = 0; j < pieceImage.rows; j++) {
                            pixel = pieceImage.at<cv::Vec3b>(i, j);
                            r = static_cast<int>(pixel[0]);
                            g = static_cast<int>(pixel[1]);
                            b = static_cast<int>(pixel[2]);
                            if (
                                (r < 95 || r > 105) &&
                                (g < 95 || g > 105) &&
                                (b < 95 || b > 105)
                            ){
                                // if (
                                //     y + i - resizeWidth / 2 <= board.size  &&
                                //     x + j - resizeHeight / 2 <= board.size  &&
                                //     y + i - resizeWidth / 2 > 0 &&
                                //     x + j - resizeHeight / 2 > 0
                                // ) {
                                tmp.at<cv::Vec3b>(y + i - resizeWidth / 2 , x + j - resizeHeight / 2)[0] = int(b);
                                tmp.at<cv::Vec3b>(y + i - resizeWidth / 2 , x + j - resizeHeight / 2)[1] = int(g);
                                tmp.at<cv::Vec3b>(y + i - resizeWidth / 2 , x + j - resizeHeight / 2)[2] = int(r);
                                // }
                            }
                        }
                    }
                    cv::rectangle(
                        tmp,
                        cv::Point(
                            x + 60,
                            y + 60
                        ),
                        cv::Point(
                            x - 60,
                            y - 60
                        ),
                        cv::Scalar(100, 100, 0),
                        4,
                        cv::LINE_AA,
                        0
                    );
                    cv::rectangle(
                        tmp,
                        cv::Point(
                            x + 62,
                            y + 60
                        ),
                        cv::Point(
                            x - 62,
                            y + 100
                        ),
                        cv::Scalar(100, 100, 0),
                        -1,
                        cv::LINE_AA,
                        0
                    );
                    cv::putText(
                        tmp,
                        board.piecesImages.at(selected.id).color + " " + board.piecesImages.at(selected.id).name,
                        cv::Point(
                            x - 55,
                            y + 85
                        ),
                        cv::FONT_HERSHEY_SIMPLEX,
                        0.6,
                        cv::Scalar(255, 255, 0),
                        2
                    );
                    // cv::imshow("Selected", pieceImage);
                    cv::imshow("Chess Board", tmp);
                }
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
        // }
    }
    //-- Generate Chess Board
    void Chess::generateChessBoard() {
        ChessHome new_home;
        new_home.size = board.size / 8;
        std::cout << LOG "Generating Chess Homes" ENDL;
        char row;
        int homeID = 8;
        for (int i = 0; i < 8; i++) {
            row = char(65 + i);
            for (int j = 0; j < 8; j++, homeID--) {
                new_home.id = homeID;
                new_home.x = board.size * i / 8;
                new_home.y = board.size * j / 8;
                new_home.center_x = (new_home.x) + new_home.size / 2;
                new_home.center_y = (new_home.y) + new_home.size / 2;
                new_home.name.erase();
                new_home.name.resize(0);
                new_home.name.push_back(row);
                new_home.name.push_back(char(56 - j));
                new_home.isFileld = HOME_EMPTY;
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
            homeID = 8 * (i + 2);
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
                std::to_string(home.at(i).id),
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
        cv::waitKey(0);
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
                        board.piecesImages.at(board.piecesImages.size() - 1).nameID = CHESS_BISHOP;
                        board.piecesImages.at(board.piecesImages.size() - 1).colorID = CHESS_DARK;
                        board.piecesImages.at(board.piecesImages.size() - 1).name = "Bishop";
                        board.piecesImages.at(board.piecesImages.size() - 1).color = "Dark";
                    } else if (address[0] == 'k' && address[1] == 'd') {
                        std::cout << TAB TAB SUCCESS "Black King Detected" ENDL;
                        board.piecesImages.at(board.piecesImages.size() - 1).nameID = CHESS_KING;
                        board.piecesImages.at(board.piecesImages.size() - 1).colorID = CHESS_DARK;
                        board.piecesImages.at(board.piecesImages.size() - 1).name = "King";
                        board.piecesImages.at(board.piecesImages.size() - 1).color = "Dark";
                    } else if (address[0] == 'n' && address[1] == 'd') {
                        std::cout << TAB TAB SUCCESS "Black Knight Detected" ENDL;
                        board.piecesImages.at(board.piecesImages.size() - 1).nameID = CHESS_KNIGHT;
                        board.piecesImages.at(board.piecesImages.size() - 1).colorID = CHESS_DARK;
                        board.piecesImages.at(board.piecesImages.size() - 1).name = "Knight";
                        board.piecesImages.at(board.piecesImages.size() - 1).color = "Dark";
                    } else if (address[0] == 'p' && address[1] == 'd') {
                        std::cout << TAB TAB SUCCESS "Black Pawn Detected" ENDL;
                        board.piecesImages.at(board.piecesImages.size() - 1).nameID = CHESS_PAWN;
                        board.piecesImages.at(board.piecesImages.size() - 1).colorID = CHESS_DARK;
                        board.piecesImages.at(board.piecesImages.size() - 1).name = "Pawn";
                        board.piecesImages.at(board.piecesImages.size() - 1).color = "Dark";
                    } else if (address[0] == 'q' && address[1] == 'd') {
                        std::cout << TAB TAB SUCCESS "Black Queen Detected" ENDL;
                        board.piecesImages.at(board.piecesImages.size() - 1).nameID = CHESS_QUEEN;
                        board.piecesImages.at(board.piecesImages.size() - 1).colorID = CHESS_DARK;
                        board.piecesImages.at(board.piecesImages.size() - 1).name = "Queen";
                        board.piecesImages.at(board.piecesImages.size() - 1).color = "Dark";
                    } else if (address[0] == 'r' && address[1] == 'd') {
                        std::cout << TAB TAB SUCCESS "Black Castle Detected" ENDL;
                        board.piecesImages.at(board.piecesImages.size() - 1).nameID = CHESS_CASTLE;
                        board.piecesImages.at(board.piecesImages.size() - 1).colorID = CHESS_DARK;
                        board.piecesImages.at(board.piecesImages.size() - 1).name = "Castle";
                        board.piecesImages.at(board.piecesImages.size() - 1).color = "Dark";
                    } else if (address[0] == 'b' && address[1] == 'l') {
                        std::cout << TAB TAB SUCCESS "White Bishop Detected" ENDL;
                        board.piecesImages.at(board.piecesImages.size() - 1).nameID = CHESS_BISHOP;
                        board.piecesImages.at(board.piecesImages.size() - 1).colorID = CHESS_LIGHT;
                        board.piecesImages.at(board.piecesImages.size() - 1).name = "Bishop";
                        board.piecesImages.at(board.piecesImages.size() - 1).color = "Light";
                    } else if (address[0] == 'k' && address[1] == 'l') {
                        std::cout << TAB TAB SUCCESS "White King Detected" ENDL;
                        board.piecesImages.at(board.piecesImages.size() - 1).nameID = CHESS_KING;
                        board.piecesImages.at(board.piecesImages.size() - 1).colorID = CHESS_LIGHT;
                        board.piecesImages.at(board.piecesImages.size() - 1).name = "King";
                        board.piecesImages.at(board.piecesImages.size() - 1).color = "Light";
                    } else if (address[0] == 'n' && address[1] == 'l') {
                        std::cout << TAB TAB SUCCESS "White Knight Detected" ENDL;
                        board.piecesImages.at(board.piecesImages.size() - 1).nameID = CHESS_KNIGHT;
                        board.piecesImages.at(board.piecesImages.size() - 1).colorID = CHESS_LIGHT;
                        board.piecesImages.at(board.piecesImages.size() - 1).name = "Knight";
                        board.piecesImages.at(board.piecesImages.size() - 1).color = "Light";
                    } else if (address[0] == 'p' && address[1] == 'l') {
                        std::cout << TAB TAB SUCCESS "White Pawn Detected" ENDL;
                        board.piecesImages.at(board.piecesImages.size() - 1).nameID = CHESS_PAWN;
                        board.piecesImages.at(board.piecesImages.size() - 1).colorID = CHESS_LIGHT;
                        board.piecesImages.at(board.piecesImages.size() - 1).name = "Pawn";
                        board.piecesImages.at(board.piecesImages.size() - 1).color = "Light";
                    } else if (address[0] == 'q' && address[1] == 'l') {
                        std::cout << TAB TAB SUCCESS "White Queen Detected" ENDL;
                        board.piecesImages.at(board.piecesImages.size() - 1).nameID = CHESS_QUEEN;
                        board.piecesImages.at(board.piecesImages.size() - 1).colorID = CHESS_LIGHT;
                        board.piecesImages.at(board.piecesImages.size() - 1).name = "Queen";
                        board.piecesImages.at(board.piecesImages.size() - 1).color = "Light";
                    } else if (address[0] == 'r' && address[1] == 'l') {
                        std::cout << TAB TAB SUCCESS "White Castle Detected" ENDL;
                        board.piecesImages.at(board.piecesImages.size() - 1).nameID = CHESS_CASTLE;
                        board.piecesImages.at(board.piecesImages.size() - 1).colorID = CHESS_LIGHT;
                        board.piecesImages.at(board.piecesImages.size() - 1).name = "Castle";
                        board.piecesImages.at(board.piecesImages.size() - 1).color = "Light";
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
            //-- Add Check Button to Check if There is Possible Checkmate
        } else {
            std::cout << TAB FAILED << "Can Not Open Path " << PATH << ENDL;
        }
    }
    //-- Method to Check Moves of Pieces on Board
    void Chess::checkMoves() {
        std::cout << TAB LOG "Checking Pieces Moves : " << pieces.size() << ENDL;
        for (int i = 0; i < pieces.size(); i++) {
            PieceInfo tmp = pieces.at(i).getInfo();
            std::cout << TAB TAB LOG "Calculating Moves of Piece " << tmp.id << std::endl;
            std::vector<int> moves = pieces.at(i).getMoveHomes();
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
        //-- Check Key
        int key;
        while (true) {
            key = cv::waitKey(0);
            if (key == int('q') || key == int(' ')) {
                std::cout << SUCCESS "Program has been Terminated" ENDL;
                break;
            } else if (key == int('c')) {
                chess.programState = STATE_CHECK_CHECKMATE;
                std::cout << LOG "Checking Checkmate States ..." ENDL;
                chess.checkMoves();
            }
        }
        // cv::waitKey(0);
    }

# endif // AI_BABAK_KARASFI_CHESS