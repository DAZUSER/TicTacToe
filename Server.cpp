#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <mutex>
#include <thread>
#include "Game.h"  

using namespace boost::asio;
using boost::asio::ip::tcp;

const int PORT = 0;

class TicTacToeServer {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor_;
    std::recursive_mutex mtx;

public:
    TicTacToeServer() : acceptor_(io_context, tcp::endpoint(tcp::v4(), PORT)) {
        startAccept();
    }

    void startAccept() {
        auto socket1 = std::make_shared<tcp::socket>(io_context);
        auto socket2 = std::make_shared<tcp::socket>(io_context);

        acceptor_.async_accept(*socket1, [this, socket1, socket2](const boost::system::error_code& error) {
            if (!error) {
                std::cout << "Player 1 connected\n";

                
                boost::asio::streambuf buf;
                boost::asio::read_until(*socket1, buf, "\n");
                std::istream is(&buf);
                int N, M;
                is >> N >> M;
                
                Game game(N, M);

                
                acceptor_.async_accept(*socket2, [this, socket1, socket2, game = std::move(game)](const boost::system::error_code& error) mutable {
                    if (!error) {
                        std::cout << "Player 2 connected\n";
                        std::thread(&TicTacToeServer::handleGame, this, socket1, socket2, std::move(game)).detach();
                    }
                });
            }
            });

        io_context.run();
    }

    void handleGame(std::shared_ptr<tcp::socket> socket1, std::shared_ptr<tcp::socket> socket2, Game game) {
        try {
            bool gameEnded = false;
            while (!gameEnded) {
                for (auto& socket : { socket1, socket2 }) {
                    boost::asio::streambuf buf;
                    boost::asio::read_until(*socket, buf, "\n");
                    std::istream is(&buf);
                    std::string input;
                    std::getline(is, input);

                    std::lock_guard<std::recursive_mutex> lock(mtx);
                    std::string message;

                    if (input.find("/chat", 0) == 0) {
                        message = "CHAT: " + input.substr(6) + "\n";
                    }
                    else {
                        int cell = std::stoi(input);
                        bool validMove = game.makeMove(cell);

                        if (validMove) {
                            bool win = game.checkWin();
                            bool draw = game.checkDraw();

                            if (win) {
                                message = game.getBoard() + "WIN\n";
                                gameEnded = true;
                            }
                            else if (draw) {
                                message = game.getBoard() + "DRAW\n";
                                gameEnded = true;
                            }
                            else {
                                message = game.getBoard() + "CONTINUE\n";
                            }
                        }
                        else {
                            message = "INVALID MOVE\n";
                        }
                    }

                    
                    if (!message.empty()) {
                        for (auto& client : { socket1, socket2 }) {
                            boost::asio::write(*client, boost::asio::buffer(message));
                        }
                    }
                }
            }
        }
        catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }
};

int main() {
    try {
        TicTacToeServer server;
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

