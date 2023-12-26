//-- Disable Warnings
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-variable"
# pragma GCC diagnostic ignored "-Wsign-compare"
# pragma GCC diagnostic ignored "-Wunused-value"
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
        //-- Clear Move Homes
        moveHomes.resize(0);
        parent = home - 1;
        //-- Find Move Homes
        switch (id) {
            case CHESS_PAWN: {
                //-- Forward Moves
                if (color == CHESS_LIGHT) {
                    if (home % 8 != 0) {
                        moveHomes.push_back(home + 1 - 1);
                        //-- Diagonal Attack Right
                        if (home < 57) {
                            moveHomes.push_back(home + 1 + 8 - 1);
                        }
                        //-- Diagonal Attack Left
                        if (home > 8) {
                            moveHomes.push_back(home + 1 - 8 - 1);
                        }
                    }
                } else if (color == CHESS_DARK) {
                    if (home % 8 != 1) {
                        moveHomes.push_back(home - 1 - 1);
                        //-- Diagonal Attack Right
                        if (home < 57) {
                            moveHomes.push_back(home - 1 + 8 - 1);
                        }
                        //-- Diagonal Attack Left
                        if (home > 8) {
                            moveHomes.push_back(home - 1 - 8 - 1);
                        }
                    }
                }
                break;
            }
            case CHESS_KNIGHT: {
                //-- Left
                if (home > 16) {
                    //-- Lower
                    if (home % 8 != 1) {
                        moveHomes.push_back(home - 16 - 1 - 1);
                    }
                    //-- Upper
                    if (home % 8 != 0) {
                        moveHomes.push_back(home - 16 + 1 - 1);
                    }
                }
                //-- Right
                if (home < 49) {
                    //-- Lower
                    if (home % 8 != 1) {
                        moveHomes.push_back(home + 16 - 1 - 1);
                    }
                    //-- Upper
                    if (home % 8 != 0) {
                        moveHomes.push_back(home + 16 + 1 - 1);
                    }
                }
                //-- Up
                if (home % 8 != 0 && home % 8 != 7) {
                    //-- Left
                    if (home > 8) {
                        moveHomes.push_back(home - 8 + 2 - 1);
                    }
                    //-- Right
                    if (home < 57) {
                        moveHomes.push_back(home + 8 + 2 - 1);
                    }
                }
                //-- Down
                if (home % 8 != 1 && home % 8 != 2) {
                    //-- Left
                    if (home > 8) {
                        moveHomes.push_back(home - 8 - 2 - 1);
                    }
                    //-- Right
                    if (home < 57) {
                        moveHomes.push_back(home + 8 - 2 - 1);
                    }
                }
                break;
            }
            case CHESS_BISHOP: {
                int tmpHome = home;
                //-- Up Right
                for (int i = 0; i < 8; i++) {
                    tmpHome += 9;
                    if (tmpHome % 8 == 1 || tmpHome > 64) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                //-- Down Right
                tmpHome = home;
                for (int i = 0; i < 8; i++) {
                    tmpHome += 7;
                    if (tmpHome % 8 == 0 || tmpHome > 64) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                //-- Up Left
                tmpHome = home;
                for (int i = 0; i < 8; i++) {
                    tmpHome -= 7;
                    if (tmpHome % 8 == 1 || tmpHome < 1) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                //-- Down Left
                tmpHome = home;
                for (int i = 0; i < 8; i++) {
                    tmpHome -= 9;
                    if (tmpHome % 8 == 0 || tmpHome < 1) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                break;
            }
            case CHESS_CASTLE: {
                int tmpHome = home;
                //-- Right
                for (int i = 0; i < 8; i++) {
                    tmpHome += 8;
                    if (tmpHome > 64) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                //-- Left
                tmpHome = home;
                for (int i = 0; i < 8; i++) {
                    tmpHome -= 8;
                    if (tmpHome < 1) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                //-- Up
                tmpHome = home;
                for (int i = 0; i < 8; i++) {
                    tmpHome += 1;
                    if (tmpHome % 8 == 1) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                //-- Down
                tmpHome = home;
                for (int i = 0; i < 8; i++) {
                    tmpHome -= 1;
                    if (tmpHome % 8 == 0) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                break;
            }
            case CHESS_QUEEN: {
                int tmpHome = home;
                //-- Up Right
                for (int i = 0; i < 8; i++) {
                    tmpHome += 9;
                    if (tmpHome % 8 == 1 || tmpHome > 64) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                //-- Down Right
                tmpHome = home;
                for (int i = 0; i < 8; i++) {
                    tmpHome += 7;
                    if (tmpHome % 8 == 0 || tmpHome > 64) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                //-- Up Left
                tmpHome = home;
                for (int i = 0; i < 8; i++) {
                    tmpHome -= 7;
                    if (tmpHome % 8 == 1 || tmpHome < 1) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                //-- Down Left
                tmpHome = home;
                for (int i = 0; i < 8; i++) {
                    tmpHome -= 9;
                    if (tmpHome % 8 == 0 || tmpHome < 1) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                tmpHome = home;
                //-- Right
                for (int i = 0; i < 8; i++) {
                    tmpHome += 8;
                    if (tmpHome > 64) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                //-- Left
                tmpHome = home;
                for (int i = 0; i < 8; i++) {
                    tmpHome -= 8;
                    if (tmpHome < 1) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                //-- Up
                tmpHome = home;
                for (int i = 0; i < 8; i++) {
                    tmpHome += 1;
                    if (tmpHome % 8 == 1) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                //-- Down
                tmpHome = home;
                for (int i = 0; i < 8; i++) {
                    tmpHome -= 1;
                    if (tmpHome % 8 == 0) {
                        break;
                    }
                    moveHomes.push_back(tmpHome - 1);
                }
                break;
            }
            case CHESS_KING: {
                //-- Left
                if (home > 8) {
                    moveHomes.push_back(home - 8 - 1);
                }
                //-- Right
                if (home < 57) {
                    moveHomes.push_back(home + 8 - 1);
                }
                //-- Up
                if (home % 8 != 0) {
                    moveHomes.push_back(home + 1 - 1);
                    //-- Up Right
                    if (home < 57) {
                        moveHomes.push_back(home + 1 + 8 - 1);
                    }
                    //-- Up Left
                    if (home > 8) {
                        moveHomes.push_back(home + 1 - 8 - 1);
                    }
                }
                //-- Down
                if (home % 8 != 1) {
                    moveHomes.push_back(home - 1 - 1);
                    //-- Down Right
                    if (home < 57) {
                        moveHomes.push_back(home - 1 + 8 - 1);
                    }
                    //-- Down Left
                    if (home > 8) {
                        moveHomes.push_back(home - 1 - 8 - 1);
                    }
                }
                break;
            }
        }
    }
    //-- Method to Get Piece Move Homes
    std::vector<int> Piece::getMoveHomes() {
        findMoveHomes();
        return moveHomes;
    }
    //-- Method to Get Piece Attack Homes
    std::vector<int> Piece::getAttackHomes() {
        return attackHomes;
    }
    //-- Chess Class Constructor
    Chess::Chess(
        int &_size
    ) {
        total = 32;
        home.resize(0);
        picked_up = false;
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
        return true;
    }
    //-- OnMouseCallback Method
    void Chess::onMouseCallback(int event, int x, int y, int flags, void* userdata) {
        static_cast<Chess*>(userdata)->onMouse(event, x, y, flags);
    }
    //-- Mouse Callbacks Handling
    void Chess::onMouse(int event, int x, int y, int flags) {
        if (programState == STATE_PLACE_PIECES) {
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
                        picked_up = true;
                    } else if (section == SEC_GAME) {
                        if (picked_up == true) {
                            if (tobePlaced.flag == HOME_EMPTY) {
                                cv::Mat tmp, fadePiece;
                                tempMat1.copyTo(tmp);
                                board.piecesImages.at(selected.id).image.copyTo(pieceImage);
                                pieceImage.copyTo(fadePiece);
                                int placedWidth = home.at(0).size * PIECE_PLACE_SIZE;
                                int placedHeight = home.at(0).size * PIECE_PLACE_SIZE;
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
                    }
                    break;
                };
                //-- Left Button Up
                case cv::EVENT_LBUTTONUP: {
                    // if (selected.flag = SELECT_PICK) {
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
                    // }
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
                    } else if (selected.flag == SELECT_MOVE) { // Moving Piece on Blue Box
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
                                    if (
                                        y + i - resizeWidth / 2 < board.size &&
                                        x + j - resizeHeight / 2 < board.size * (1 + PANEL_WIDTH_SCALE) &&
                                        y + i - resizeWidth / 2 > 0 &&
                                        x + j - resizeHeight / 2 > 0
                                    ) {
                                    tmp.at<cv::Vec3b>(y + i - resizeWidth / 2 , x + j - resizeHeight / 2)[0] = int(b);
                                    tmp.at<cv::Vec3b>(y + i - resizeWidth / 2 , x + j - resizeHeight / 2)[1] = int(g);
                                    tmp.at<cv::Vec3b>(y + i - resizeWidth / 2 , x + j - resizeHeight / 2)[2] = int(r);
                                    }
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
        }
    }
    //-- Generate Chess Board
    void Chess::generateChessBoard() {
        ChessHome new_home;
        new_home.size = board.size / 8;
        std::cout << LOG "Generating Chess Homes" ENDL;
        char row;
        int homeID = 8;
        home.resize(64);
        //-- Generate Homes
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
                std::cout << TAB LOG "Home " << new_home.name <<" has been Generated at " << new_home.center_x << " x " << new_home.center_y << " with ID " << new_home.id << ENDL;
                // home.push_back(new_home);
                home[homeID - 1] = new_home;
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
        //-- Draw Border of Homes
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
        //-- Write Home Names
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
            cv::waitKey(SPEED * 10);
        }
        int sign = 1;
        int color = 0;
        //-- Draw White and Black Homes
        for (int i = 0; i < 64; i++) {
            if (i % 8 != 0) {
                sign *= -1;
            }
            if (sign == -1) {
                color = 255;
                home.at(i).color = CHESS_LIGHT;
            } else {
                color = 0;
                home.at(i).color = CHESS_DARK;
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
        cv::Scalar rgbColor;
        //-- Draw Brown and Cream Homes
        for (int i = 0; i < home.size(); i++) {
            if (home.at(i).color == CHESS_LIGHT) {
                rgbColor = cv::Scalar(93, 120, 138);
            } else {
                rgbColor = cv::Scalar(46, 58, 87);
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
        //-- Check if Chess Pieces Directory is Opened or Not
        if (file) {
            std::cout << TAB SUCCESS << PATH << " Directory has been Opened" ENDL;
            Display* disp = XOpenDisplay(NULL);
            Screen* scrn = DefaultScreenOfDisplay(disp);
            cv::imshow("Chess Board", board.window);
            cv::Mat chessboard;
            board.window.copyTo(chessboard);
            int panel_width = board.size * PANEL_WIDTH_SCALE;
            int addition = 2;
            //-- Resize Chess Board to Add Panel Width
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
            //-- Write Home Names on The Board
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
                    if (address[0] == '.') {
                        std::cout << TAB TAB WARNING "Passed Dot File Type" ENDL;
                    } else {
                        std::cout << TAB TAB FAILED "Can Not Import Because It is Not PNG" ENDL;
                    }
                }
            }
            cv::Point startPoint(board.size + 50, 40);
            cv::imshow("Chess Board", board.window);
            int startposx = 0, startposy = 0;
            cv::Mat tmp;
            board.window.copyTo(tmp);
            //-- Draw Pieces Panel Sections
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
                                cv::Scalar(230, 10, 0),
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
            //-- Draw Pieces Panel Boxes
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
            int r, g, b;
            cv::Vec3b pixel;
            //-- Add Pieces to Board
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
                cv::waitKey(SPEED * 30);
                cv::imshow("Chess Board", board.window);
            }
        } else {
            std::cout << TAB FAILED << "Can Not Open Path " << PATH << ENDL;
        }
        //-- Close Opened Directory
        // closedir(file);
    }
    //-- Method to Check Moves of Pieces on Board
    void Chess::checkMoves() {
        programState = STATE_CHECK_CHECKMATE;
        cv::imshow("Chess Board", board.window);
        //-- Count Amount of Pieces
        int pieceCount = pieces.size();
        if (pieceCount == 1) {
            std::cout << TAB LOG "Checking Moves of " << pieces.size() << " Piece" << ENDL;
        } else {
            std::cout << TAB LOG "Checking Moves of " << pieces.size() << " Pieces" << ENDL;
        }
        //-- Calculate Moves of Pieces
        cv::Mat tmpMat;
        for (int i = 0; i < pieceCount; i++) {
            PieceInfo tmp = pieces.at(i).getInfo();
            std::cout << TAB TAB LOG "Calculating Moves of Piece " << tmp.id << " on Home " << tmp.home << std::endl;
            std::vector<int> moves = pieces.at(i).getMoveHomes();
            board.window.copyTo(tmpMat);
            for (int j = 0; j < moves.size(); j++) {
                for (int h = 0; h < home.size(); h++) {
                    if (home.at(h).id == tmp.home) {
                        std::cout << TAB TAB TAB INFO "Piece " << tmp.id << " Can Move to Home " << home.at(moves.at(j)).id << std::endl;
                        cv::rectangle(
                            tmpMat,
                            cv::Point(
                                home.at(moves.at(j)).x,
                                home.at(moves.at(j)).y
                            ),
                            cv::Point(
                                home.at(moves.at(j)).x + home.at(moves.at(j)).size,
                                home.at(moves.at(j)).y + home.at(moves.at(j)).size
                            ),
                            cv::Scalar(
                                255, 255, 100
                            ),
                            4, 8, 0
                        );
                        cv::circle(
                            tmpMat,
                            cv::Point(
                                home.at(moves.at(j)).center_x,
                                home.at(moves.at(j)).center_y
                            ),
                            5,
                            cv::Scalar(
                                0, 170, 255
                            ),
                            -1, 8, 0
                        );
                    }
                }
                cv::imshow("Chess Board", tmpMat);
                cv::waitKey(SPEED * 6);
                // cv::waitKey(0);
                board.window.copySize(tmpMat);
            }
            board.window.copyTo(tmpMat);
        }
        //-- Check Checkmate State for each King on Board
        std::cout << TAB LOG "Finding Kings on Board ..." ENDL;
        std::vector<int> king_moves;
        for (int i = 0; i < pieceCount; i++) {
            king_moves.resize(0);
            if (pieces.at(i).getInfo().id == CHESS_KING) {
                std::cout << TAB TAB SUCCESS "King Found on Home " << pieces.at(i).getInfo().home << ENDL;
                //-- Store King Moves and Its home on Last Index
                king_moves = pieces.at(i).getMoveHomes();
                king_moves.push_back(pieces.at(i).parent);
                //-- Show Found King on Board
                cv::rectangle(
                    tmpMat,
                    cv::Point(
                        home.at(pieces.at(i).parent).x,
                        home.at(pieces.at(i).parent).y
                    ),
                    cv::Point(
                        home.at(pieces.at(i).parent).x + home.at(pieces.at(i).parent).size,
                        home.at(pieces.at(i).parent).y + home.at(pieces.at(i).parent).size
                    ),
                    cv::Scalar(
                        0, 255, 0
                    ),
                    4, 8, 0
                );
                cv::putText(
                    tmpMat,
                    "King    " + std::to_string(pieces.at(i).getInfo().home),
                    cv::Point(
                        home.at(pieces.at(i).getInfo().home - 1).x + 10,
                        home.at(pieces.at(i).getInfo().home - 1).y + 30
                    ),
                    cv::FONT_HERSHEY_SIMPLEX,
                    1,
                    cv::Scalar(0, 255, 0),
                    2
                );
                cv::imshow("Chess Board", tmpMat);
                cv::waitKey(SPEED * 30);
                //-- Iterate on All Pieces Again and Find if King is in Checkmate State
                std::cout << TAB TAB LOG "Checking Checkmate State of King on Home " << pieces.at(i).getInfo().home << ENDL;
                std::vector<int> moves;
                cv::Mat tmpMat2;
                tmpMat.copyTo(tmpMat2);
                for (int j = 0; j < pieceCount; j++) {
                    // if (pieces.at(j).getInfo().id == CHESS_KING) {
                    //     continue;
                    // }
                    if (pieces.at(j).parent == CHESS_KING) {
                        continue;
                    }
                    //-- Store Moves of Pieces
                    moves.resize(0);
                    moves = pieces.at(j).getMoveHomes();
                    //-- Check if King is in Checkmate State
                    for (int k = 0; k < moves.size(); k++) {
                        cv::rectangle(
                            tmpMat2,
                            cv::Point(
                                home.at(moves.at(k)).x,
                                home.at(moves.at(k)).y
                            ),
                            cv::Point(
                                home.at(moves.at(k)).x + home.at(moves.at(k)).size,
                                home.at(moves.at(k)).y + home.at(moves.at(k)).size
                            ),
                            cv::Scalar(
                                0, 255, 255
                            ),
                            4, 8, 0
                        );
                        if (moves.at(k) == king_moves.at(king_moves.size() - 1)) {
                            //-- Check if King is in Checkmate State by Piece with Opposite Color
                            if (pieces.at(j).getInfo().color != pieces.at(i).getInfo().color) {
                                std::cout << TAB TAB TAB INFO "King on Home " << pieces.at(i).getInfo().home << " is in Checkmate State by Piece on Home " << pieces.at(j).getInfo().home << ENDL;
                                cv::rectangle(
                                    tmpMat,
                                    cv::Point(
                                        home.at(pieces.at(i).parent).x,
                                        home.at(pieces.at(i).parent).y
                                    ),
                                    cv::Point(
                                        home.at(pieces.at(i).parent).x + home.at(pieces.at(i).parent).size,
                                        home.at(pieces.at(i).parent).y + home.at(pieces.at(i).parent).size
                                    ),
                                    cv::Scalar(
                                        0, 0, 255
                                    ),
                                    4, 8, 0
                                );
                                cv::rectangle(
                                    tmpMat2,
                                    cv::Point(
                                        home.at(pieces.at(i).parent).x,
                                        home.at(pieces.at(i).parent).y
                                    ),
                                    cv::Point(
                                        home.at(pieces.at(i).parent).x + home.at(pieces.at(i).parent).size,
                                        home.at(pieces.at(i).parent).y + home.at(pieces.at(i).parent).size
                                    ),
                                    cv::Scalar(
                                        0, 0, 255
                                    ),
                                    4, 8, 0
                                );
                                cv::putText(
                                    tmpMat,
                                    "Checkmate",
                                    cv::Point(
                                        home.at(pieces.at(i).parent).x + 10,
                                        home.at(pieces.at(i).parent).y + home.at(pieces.at(i).parent).size - 10
                                    ),
                                    cv::FONT_HERSHEY_SIMPLEX,
                                    0.8,
                                    cv::Scalar(0, 0, 255),
                                    2
                                );
                                cv::putText(
                                    tmpMat2,
                                    "Checkmate",
                                    cv::Point(
                                        home.at(pieces.at(i).parent).x + 10,
                                        home.at(pieces.at(i).parent).y + home.at(pieces.at(i).parent).size - 10
                                    ),
                                    cv::FONT_HERSHEY_SIMPLEX,
                                    0.8,
                                    cv::Scalar(0, 0, 255),
                                    2
                                );
                                cv::putText(
                                    tmpMat,
                                    "Attacker",
                                    cv::Point(
                                        home.at(pieces.at(j).parent).x + 10,
                                        home.at(pieces.at(j).parent).y + 30
                                    ),
                                    cv::FONT_HERSHEY_SIMPLEX,
                                    1,
                                    cv::Scalar(0, 0, 255),
                                    2
                                );
                                cv::rectangle(
                                    tmpMat,
                                    cv::Point(
                                        home.at(pieces.at(j).parent).x,
                                        home.at(pieces.at(j).parent).y
                                    ),
                                    cv::Point(
                                        home.at(pieces.at(j).parent).x + home.at(pieces.at(j).parent).size,
                                        home.at(pieces.at(j).parent).y + home.at(pieces.at(j).parent).size
                                    ),
                                    cv::Scalar(
                                        0, 0, 255
                                    ),
                                    4, 8, 0
                                );
                                cv::putText(
                                    tmpMat2,
                                    "Attacker",
                                    cv::Point(
                                        home.at(pieces.at(j).parent).x + 10,
                                        home.at(pieces.at(j).parent).y + 30
                                    ),
                                    cv::FONT_HERSHEY_SIMPLEX,
                                    1,
                                    cv::Scalar(0, 0, 255),
                                    2
                                );
                                cv::rectangle(
                                    tmpMat2,
                                    cv::Point(
                                        home.at(pieces.at(j).parent).x,
                                        home.at(pieces.at(j).parent).y
                                    ),
                                    cv::Point(
                                        home.at(pieces.at(j).parent).x + home.at(pieces.at(j).parent).size,
                                        home.at(pieces.at(j).parent).y + home.at(pieces.at(j).parent).size
                                    ),
                                    cv::Scalar(
                                        0, 0, 255
                                    ),
                                    4, 8, 0
                                );
                                cv::rectangle(
                                    tmpMat2,
                                    cv::Point(
                                        home.at(pieces.at(i).parent).x + 36,
                                        home.at(pieces.at(i).parent).y + 36
                                    ),
                                    cv::Point(
                                        home.at(pieces.at(i).parent).x + home.at(pieces.at(i).parent).size - 36,
                                        home.at(pieces.at(i).parent).y + home.at(pieces.at(i).parent).size - 36
                                    ),
                                    cv::Scalar(
                                        0, 0, 255
                                    ),
                                    2, 8, 0
                                );
                                cv::arrowedLine(
                                    tmpMat,
                                    cv::Point(
                                        home.at(pieces.at(j).parent).center_x,
                                        home.at(pieces.at(j).parent).center_y
                                    ),
                                    cv::Point(
                                        home.at(pieces.at(i).parent).center_x,
                                        home.at(pieces.at(i).parent).center_y
                                    ),
                                    cv::Scalar(
                                        0, 0, 255
                                    ),
                                    4, 8, 0
                                );
                                //-- Check Defends According to Available Attacker
                                for (int h = 0; h < pieceCount; h++) {
                                    if (
                                        pieces.at(h).getInfo().color == pieces.at(i).getInfo().color &&
                                        pieces.at(h).getInfo().id != CHESS_KING
                                    ) {
                                        //-- Check if Piece with King Color is Blocking the Attack Way
                                        //-- Check if Piece Can Move to Defend King with Same Color
                                        std::vector<int> defender_moves = pieces.at(h).getMoveHomes();
                                        for (int l = 0; l < defender_moves.size(); l++) {
                                            if (defender_moves.at(l) == pieces.at(j).parent) {
                                                std::cout << TAB TAB TAB INFO "Piece on Home " << pieces.at(h).getInfo().home << " Can Defend King on Home " << pieces.at(i).getInfo().home << " by Going to Home " << defender_moves.at(l) << ENDL;
                                                cv::rectangle(
                                                    tmpMat2,
                                                    cv::Point(
                                                        home.at(defender_moves.at(l)).x + 36,
                                                        home.at(defender_moves.at(l)).y + 36
                                                    ),
                                                    cv::Point(
                                                        home.at(defender_moves.at(l)).x + home.at(defender_moves.at(l)).size - 36,
                                                        home.at(defender_moves.at(l)).y + home.at(defender_moves.at(l)).size - 36
                                                    ),
                                                    cv::Scalar(
                                                        0, 100, 255
                                                    ),
                                                    2, 8, 0
                                                );
                                                cv::putText(
                                                    tmpMat2,
                                                    "Defender",
                                                    cv::Point(
                                                        home.at(pieces.at(h).parent).x + 10,
                                                        home.at(pieces.at(h).parent).y + 30
                                                    ),
                                                    cv::FONT_HERSHEY_SIMPLEX,
                                                    1,
                                                    cv::Scalar(0, 255, 0),
                                                    2
                                                );
                                                cv::rectangle(
                                                    tmpMat2,
                                                    cv::Point(
                                                        home.at(pieces.at(h).parent).x,
                                                        home.at(pieces.at(h).parent).y
                                                    ),
                                                    cv::Point(
                                                        home.at(pieces.at(h).parent).x + home.at(pieces.at(h).parent).size,
                                                        home.at(pieces.at(h).parent).y + home.at(pieces.at(h).parent).size
                                                    ),
                                                    cv::Scalar(
                                                        0, 255, 100
                                                    ),
                                                    4, 8, 0
                                                );
                                                cv::arrowedLine(
                                                    tmpMat2,
                                                    cv::Point(
                                                        home.at(pieces.at(h).parent).center_x,
                                                        home.at(pieces.at(h).parent).center_y
                                                    ),
                                                    cv::Point(
                                                        home.at(defender_moves.at(l)).center_x,
                                                        home.at(defender_moves.at(l)).center_y
                                                    ),
                                                    cv::Scalar(
                                                        0, 100, 255
                                                    ),
                                                    4, 8, 0
                                                );
                                                cv::imshow("Chess Board", tmpMat2);
                                                cv::waitKey(0);
                                            }
                                        }
                                        // for (int l = 0; l < defender_moves.size(); l++) {
                                        //     if (defender_moves.at(l) == moves.at(k)) {
                                        //         std::cout << TAB TAB TAB INFO "Piece on Home " << pieces.at(h).getInfo().home << " Can Defend King on Home " << pieces.at(i).getInfo().home << " by Going to Home " << defender_moves.at(l) << ENDL;
                                        //         cv::rectangle(
                                        //             tmpMat2,
                                        //             cv::Point(
                                        //                 home.at(defender_moves.at(l)).x,
                                        //                 home.at(defender_moves.at(l)).y
                                        //             ),
                                        //             cv::Point(
                                        //                 home.at(defender_moves.at(l)).x + home.at(defender_moves.at(l)).size,
                                        //                 home.at(defender_moves.at(l)).y + home.at(defender_moves.at(l)).size
                                        //             ),
                                        //             cv::Scalar(
                                        //                 0, 255, 0
                                        //             ),
                                        //             4, 8, 0
                                        //         );
                                        //         cv::putText(
                                        //             tmpMat2,
                                        //             "Defender",
                                        //             cv::Point(
                                        //                 home.at(pieces.at(h).parent).x + 10,
                                        //                 home.at(pieces.at(h).parent).y + 30
                                        //             ),
                                        //             cv::FONT_HERSHEY_SIMPLEX,
                                        //             1,
                                        //             cv::Scalar(0, 255, 0),
                                        //             2
                                        //         );
                                        //         cv::rectangle(
                                        //             tmpMat2,
                                        //             cv::Point(
                                        //                 home.at(pieces.at(h).parent).x,
                                        //                 home.at(pieces.at(h).parent).y
                                        //             ),
                                        //             cv::Point(
                                        //                 home.at(pieces.at(h).parent).x + home.at(pieces.at(h).parent).size,
                                        //                 home.at(pieces.at(h).parent).y + home.at(pieces.at(h).parent).size
                                        //             ),
                                        //             cv::Scalar(
                                        //                 0, 255, 0
                                        //             ),
                                        //             4, 8, 0
                                        //         );
                                        //         cv::imshow("Chess Board", tmpMat2);
                                        //         cv::waitKey(0);
                                        //     }
                                        //     // for (int m = 0; m < king_moves.size() - 1; m++) {
                                        //     //     if (defender_moves.at(l) == king_moves.at(m)) {
                                        //     //         std::cout << TAB TAB TAB INFO "Piece on Home " << pieces.at(h).getInfo().home << " Can Defend King on Home " << pieces.at(i).getInfo().home << " by Going to Home " << defender_moves.at(l) << ENDL;
                                        //     //     }
                                        //     // }
                                        //     // if (defender_moves.at(l) == king_moves.at(king_moves.size() - 1)) {
                                        //     //     std::cout << TAB TAB TAB INFO "King on Home " << pieces.at(i).getInfo().home << " is in Check State by Piece on Home " << pieces.at(j).getInfo().home << ENDL;
                                        //     // }
                                        // }
                                    } else {
                                        
                                    }
                                }
                            }
                            cv::imshow("Chess Board", tmpMat2);
                            cv::waitKey(0);
                            break;
                        } else {
                            // for (int h = 0; h < king_moves.size() - 1; h++) {
                            //     if (moves.at(k) == king_moves.at(h)) {
                            //         std::cout << TAB TAB TAB WARNING "King on Home " << pieces.at(i).getInfo().home << " is in Check State by Piece on Home " << pieces.at(j).getInfo().home << ENDL;
                            //         cv::rectangle(
                            //             tmpMat,
                            //             cv::Point(
                            //                 home.at(pieces.at(i).parent).x,
                            //                 home.at(pieces.at(i).parent).y
                            //             ),
                            //             cv::Point(
                            //                 home.at(pieces.at(i).parent).x + home.at(pieces.at(i).parent).size,
                            //                 home.at(pieces.at(i).parent).y + home.at(pieces.at(i).parent).size
                            //             ),
                            //             cv::Scalar(
                            //                 0, 100, 255
                            //             ),
                            //             4, 8, 0
                            //         );
                            //         cv::rectangle(
                            //             tmpMat2,
                            //             cv::Point(
                            //                 home.at(pieces.at(i).parent).x,
                            //                 home.at(pieces.at(i).parent).y
                            //             ),
                            //             cv::Point(
                            //                 home.at(pieces.at(i).parent).x + home.at(pieces.at(i).parent).size,
                            //                 home.at(pieces.at(i).parent).y + home.at(pieces.at(i).parent).size
                            //             ),
                            //             cv::Scalar(
                            //                 0, 100, 255
                            //             ),
                            //             4, 8, 0
                            //         );
                            //         cv::putText(
                            //             tmpMat,
                            //             "Check",
                            //             cv::Point(
                            //                 home.at(pieces.at(i).parent).x + 10,
                            //                 home.at(pieces.at(i).parent).y + home.at(pieces.at(i).parent).size - 10
                            //             ),
                            //             cv::FONT_HERSHEY_SIMPLEX,
                            //             0.8,
                            //             cv::Scalar(0, 100, 255),
                            //             2
                            //         );
                            //         cv::putText(
                            //             tmpMat2,
                            //             "Check",
                            //             cv::Point(
                            //                 home.at(pieces.at(i).parent).x + 10,
                            //                 home.at(pieces.at(i).parent).y + home.at(pieces.at(i).parent).size - 10
                            //             ),
                            //             cv::FONT_HERSHEY_SIMPLEX,
                            //             0.8,
                            //             cv::Scalar(0, 100, 255),
                            //             2
                            //         );
                            //         cv::putText(
                            //             tmpMat,
                            //             "Attacker",
                            //             cv::Point(
                            //                 home.at(pieces.at(j).parent).x + 10,
                            //                 home.at(pieces.at(j).parent).y + 30
                            //             ),
                            //             cv::FONT_HERSHEY_SIMPLEX,

                            //             1,
                            //             cv::Scalar(0, 100, 255),
                            //             2
                            //         );
                            //         cv::rectangle(
                            //             tmpMat,
                            //             cv::Point(
                            //                 home.at(pieces.at(j).parent).x,
                            //                 home.at(pieces.at(j).parent).y
                            //             ),
                            //             cv::Point(
                            //                 home.at(pieces.at(j).parent).x + home.at(pieces.at(j).parent).size,
                            //                 home.at(pieces.at(j).parent).y + home.at(pieces.at(j).parent).size
                            //             ),
                            //             cv::Scalar(
                            //                 0, 100, 255
                            //             ),
                            //             4, 8, 0
                            //         );
                            //         cv::putText(
                            //             tmpMat2,
                            //             "Attacker",
                            //             cv::Point(
                            //                 home.at(pieces.at(j).parent).x + 10,
                            //                 home.at(pieces.at(j).parent).y + 30
                            //             ),
                            //             cv::FONT_HERSHEY_SIMPLEX,
                            //             1,
                            //             cv::Scalar(0, 100, 255),
                            //             2
                            //         );
                            //         cv::rectangle(
                            //             tmpMat2,
                            //             cv::Point(
                            //                 home.at(pieces.at(j).parent).x,
                            //                 home.at(pieces.at(j).parent).y
                            //             ),
                            //             cv::Point(
                            //                 home.at(pieces.at(j).parent).x + home.at(pieces.at(j).parent).size,
                            //                 home.at(pieces.at(j).parent).y + home.at(pieces.at(j).parent).size
                            //             ),
                            //             cv::Scalar(
                            //                 0, 100, 255
                            //             ),
                            //             4, 8, 0
                            //         );
                            //         cv::imshow("Chess Board", tmpMat2);
                            //         cv::waitKey(0);
                            //     }
                            // }
                        }
                        tmpMat.copyTo(tmpMat2);
                    }
                }
            }
        }
    }
    //-- Start Animation
    void Chess::startAnimation() {
        int color = 0;
        int radius = board.size;
        int maxcolor = 255;
        for (int j = 0; j < 180; j++) {
            for (int i = 0; i < radius / 2; i++) {
                color = i * maxcolor / board.size;
                if (i % ((j + 1) * 2) == 0) {
                    cv::rectangle(
                        board.window,
                        cv::Point(
                            board.size / 2 - i,
                            board.size / 2 - i
                        ),
                        cv::Point(
                            board.size / 2 + i,
                            board.size / 2 + i
                        ),
                        cv::Scalar(
                            color, color, 0
                        ),
                        2,
                        cv::LINE_AA,
                        0
                    );
                    cv::imshow("Chess Board", board.window);
                    cv::waitKey(SPEED);
                }
            }
            maxcolor /= 0.37;
        }
        for (int i = 0; i < radius / 15; i++) {
            cv::rectangle(
                board.window,
                cv::Point(
                    board.size / 2 - i,
                    board.size / 2 - i
                ),
                cv::Point(
                    board.size / 2 + i,
                    board.size / 2 + i
                ),
                cv::Scalar(
                    0, 0, 0
                ),
                2,
                cv::LINE_AA,
                0
            );
            cv::imshow("Chess Board", board.window);
            cv::waitKey(SPEED * 4);
        }
        cv::Size textSize = cv::getTextSize("by Ramtin Kosari", cv::FONT_HERSHEY_COMPLEX, 2, 1, nullptr);
        cv::Point textPosition(board.size / 2 - textSize.width / 2, board.size / 2 + textSize.height / 2);
        cv::Size textSize2 = cv::getTextSize("AI Course Project of Dr. Babak Karasfi", cv::FONT_HERSHEY_COMPLEX, 1, 1, nullptr);
        cv::Point textPosition2(board.size / 2 - textSize2.width / 2, board.size / 2 + textSize2.height / 2 + 100);
        for (int i = 0; i < 255 * 3; i++) {
            // output.copyTo(tmp);
            cv::putText(board.window, "By Ramtin Kosari", textPosition, cv::FONT_HERSHEY_COMPLEX, 2, cv::Scalar(i / 4 + 20, i / 4 + 20, i / 4));
            if (i < 255) {
                cv::putText(board.window, "AI Course Project of Dr. Babak Karasfi", textPosition2, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(i, i, 0));
            } else if (i >= 255 * 2) {
                cv::putText(board.window, "AI Course Project of Dr. Babak Karasfi", textPosition2, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255 - (i - 255 * 2), 255 - (i - 255 * 2), 0));
            } else {
                cv::putText(board.window, "AI Course Project of Dr. Babak Karasfi", textPosition2, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 255, 0));
            }
            cv::imshow("Chess Board", board.window);
            cv::waitKey(5);
        }
        cv::imshow("Chess Board", board.window);
    }
    //-- Main
    int main() {
        int size = 1600;
        //-- Initialize Chess Window and Board
        Chess chess(size);
        //-- Show StartUp Animation
        // chess.startAnimation();
        //-- Generate Chess Board
        chess.generateChessBoard();
        //-- Load Chess Pieces
        chess.loadChessPieces();
        //-- Check Moves
        while (true) {
            int key = cv::waitKey(0);
            if (key == int('q')) {
                break;
            } else if (key == int('c')) {
                if (cv::waitKey(0) == int('h')) {
                    std::cout << LOG "Waiting for Key ..." << std::endl;
                    if (cv::waitKey(0) == int('e')) {
                        if (cv::waitKey(0) == int('c')) {
                            if (cv::waitKey(0) == int('k')) {
                                chess.checkMoves();
                            } else {
                                continue;
                            }
                        } else {
                            continue;
                        }
                    } else {
                        continue;
                    }
                } else {
                    continue;
                }
            } else {
                continue;
            }
        }
        cv::destroyAllWindows();
        return 0;
    }

# endif // AI_BABAK_KARASFI_CHESS
# pragma GCC diagnostic pop