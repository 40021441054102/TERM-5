# ifndef AI_BABAK_KARASFI_CHESS
    /**
     * @file Chess.hpp
     * @author Ramtin Kosari (ramtinkosari@gmail.com)
     * @brief Babak Karasfi Term 5 Chess Project
     * @version 0.0.1
     * @date 2023-10-24
     */
    # define AI_BABAK_KARASFI_CHESS
    //-- Include Needed Libraries
    # include <X11/Xlib.h>
    # include <iostream>
    # include <dirent.h>
    # include <string>
    # include <vector>
    //-- Include OpenCV
    # ifndef OPENCV_HIGHGUI_HPP
        # include <opencv4/opencv2/highgui.hpp>
        # include <opencv4/opencv2/imgproc.hpp>
    # endif // OPENCV_HIGHGUI
    # define WARNING "\033[38;2;255;255;0m[WARNING]\033[0m "
    # define SUCCESS "\033[38;2;0;255;0m[SUCCESS]\033[0m "
    # define FAILED "\033[38;2;255;0;0m[FAILED]\033[0m "
    # define LOG "\033[38;2;150;150;150m[LOG]\033[0m "
    # define INFO "\033[38;2;0;150;150m[INFO]\033[0m "
    # define MOVE "\033[38;2;150;150;0m[MOVE]\033[0m "
    # define PATH "Assets/"
    # define TAB "   "
    # define ENDL "\n"
    # define SPEED 2
    # define PIECE_PICK_SIZE 0.85
    # define PIECE_PLACE_SIZE 0.8
    # define PANEL_WIDTH_SCALE 0.313
    //-- Program States
    enum ProgramStates {
        STATE_PLACE_PIECES,
        STATE_CHECK_CHECKMATE
    };
    //-- Chess Board's Home Status
    enum ChessHomeStatus {
        HOME_EMPTY,
        HOME_NOT_EMPTY
    };
    //-- Piece Selecting States
    enum SelectingStates {
        SELECT_NONE,
        SELECT_PICK,
        SELECT_MOVE,
        SELECT_PUT
    };
    //-- Window Sections
    enum ChessBoardSection {
        SEC_GAME,
        SEC_PIECES
    };
    //-- Chess Pieces Colors
    enum ChessPieceColors {
        CHESS_DARK = 0,
        CHESS_LIGHT = 1
    };
    //-- Chess Pieces Name
    enum ChessPieceNames {
        CHESS_KING,
        CHESS_PAWN,
        CHESS_QUEEN,
        CHESS_BISHOP,
        CHESS_CASTLE,
        CHESS_KNIGHT
    };
    //-- Chess Homes Name
    enum ChessHomeNames {
        //-- A
        CHESS_A1 = 1, CHESS_A2, CHESS_A3, CHESS_A4, CHESS_A5, CHESS_A6, CHESS_A7, CHESS_A8,
        //-- B
        CHESS_B1, CHESS_B2, CHESS_B3, CHESS_B4, CHESS_B5, CHESS_B6, CHESS_B7, CHESS_B8,
        //- C
        CHESS_C1, CHESS_C2, CHESS_C3, CHESS_C4, CHESS_C5, CHESS_C6, CHESS_C7, CHESS_C8,
        //-- D 
        CHESS_D1, CHESS_D2, CHESS_D3, CHESS_D4, CHESS_D5, CHESS_D6, CHESS_D7, CHESS_D8,
        //-- E
        CHESS_E1, CHESS_E2, CHESS_E3, CHESS_E4, CHESS_E5, CHESS_E6, CHESS_E7, CHESS_E8,
        //-- F
        CHESS_F1, CHESS_F2, CHESS_F3, CHESS_F4, CHESS_F5, CHESS_F6, CHESS_F7, CHESS_F8,
        //-- G
        CHESS_G1, CHESS_G2, CHESS_G3, CHESS_G4, CHESS_G5, CHESS_G6, CHESS_G7, CHESS_G8,
        //-- H
        CHESS_H1, CHESS_H2, CHESS_H3, CHESS_H4, CHESS_H5, CHESS_H6, CHESS_H7, CHESS_H8,
    };
    struct PieceInfo {
        int home_color;
        int color;
        int home;
        int id;
    };
    //-- Piece Class Definition
    class Piece {
        private:
            int id;
            int home;
            int color;
            bool onboard_status;
            std::vector<int> moveHomes;
            std::vector<int> attackHomes;
        public:
            Piece(
                std::int8_t &,
                std::int8_t &,
                bool &
            );
            Piece() {
                color = std::int8_t(CHESS_DARK);
                id = std::int8_t(CHESS_PAWN);
                attackHomes.resize(0);
                moveHomes.resize(0);
            }
            std::vector<int> getMoveHomes();
            std::vector<int> getAttackHomes();
            void setColor(int &);
            PieceInfo getInfo();
            void setID(int &);
            void setOnBoard(bool &);
            void setHome(int &);
            void findMoveHomes();
            void findAttackHomes();
    };
    //-- Chess Moves Class
    class Move {
        private:
            //-- Move Name
            std::string name;
            //-- Move Frame
            cv::Mat frame;
            //-- Piece Information
            struct PieceInfo {
                cv::Point initPos;
                cv::Point endPos;
                cv::Mat image;
            };
            PieceInfo piece;
    };
    //-- Chess Gameplay Class
    class Gameplay {
        private:
            std::vector<Move> moves;
        public:
            Gameplay();
            //-- Method to Load Specific Move
            //-- Method to Display Moves
            
    };
    //-- Chess Class Definition
    class Chess {
        private:
            bool picked_up;
            cv::Mat tempMat1, pieceImage;
            int total;
            struct Selected {
                int index;
                int flag;
                int x, y;
                int size;
                int id;
            };
            Selected selected, tobePlaced;
            //-- Game Section or Pieces Section Flag
            int section;
            std::vector<Piece> pieces;
            struct Board {
                cv::Mat window;
                int size;
                struct PieceImage {
                    std::string name, color;
                    int colorID;
                    cv::Mat image;
                    int nameID;
                    int size;
                    int x;
                    int y;
                };
                std::vector<PieceImage> piecesImages;
            };
            Board board;
            struct ChessHome {
                int center_x, center_y;
                std::string name;
                int isFileld;
                int color;
                int x, y;
                int size;
                int id;
            };
            std::vector<ChessHome> home;
        public:
            void startAnimation();
            bool programState;
            Chess(
                int &
            );
            ~Chess() {
                cv::destroyAllWindows();
            }
            void generateChessBoard();
            void loadChessPieces();
            static void onMouseCallback(int event, int x, int y, int flags, void* userdata);
            void onMouse(int event, int x, int y, int flags);
            bool checkPlaceable(int, int, int);
            void checkMoves();
    };
# endif // AI_BABAK_KARASFI_CHESS