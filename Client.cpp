#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <limits>

using namespace boost::asio;
using boost::asio::ip::tcp;

const int PORT = 0;

bool starts_with(const std::string& message, const std::string& prefix_chat)
{
    if (message.size() < prefix_chat.size()) 
        return false;

    for (size_t i = 0; i < prefix_chat.size(); ++i)
        if (message[i] != prefix_chat[i])
            return false;
    return true;
}



enum class Messages {
    INVALID_MOVE,
    OTHER_PLAYER_MOVED,
    WIN,
    LOSE,
    DRAW,
    BOARD_STATE,
    CHAT_MESSAGE,
    UNKNOWN
};

Messages parseMessage(const std::string& message) {
    if (message == "INVALID") return Messages::INVALID_MOVE;
    if (message.find("OTHER_PLAYER_MOVED") == 0) return Messages::OTHER_PLAYER_MOVED;
    if (message == "WIN") return Messages::WIN;
    if (message == "LOSE") return Messages::LOSE;
    if (message == "DRAW") return Messages::DRAW;
    if (starts_with(message, "/chat")) return Messages::CHAT_MESSAGE;
    return Messages::BOARD_STATE;
}

void setDifficulty(tcp::socket& socket)
{
    int N, M;
    std::cout << "������� ������ ���� N � ���������� M ������ ��� ������: ";
    while (!(std::cin >> N >> M) || M > N || M <= 0 || N <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "������������ ����. ������ ���� (N) ������ ���� ������ ��� ����� ���������� ������ ��� ������ (M), � ��� �������� ������ ���� ��������������. ���������� �����: ";
    }
    boost::asio::write(socket, boost::asio::buffer(std::to_string(N) + " " + std::to_string(M) + "\n"));
}

void makeMove(tcp::socket& socket) {
    while (true) {
        std::cout << "������� ����� ������ ��� ������� /chat <���������>: ";
        std::string input;
        std::getline(std::cin, input);

        if (starts_with(input, "/chat")) {
            boost::asio::write(socket, boost::asio::buffer(input + "\n"));
            continue;
        }

        try {
            int cell = std::stoi(input);
            boost::asio::write(socket, boost::asio::buffer(std::to_string(cell) + "\n"));
        }
        catch (std::invalid_argument&) {
            std::cout << "�������� ����. ������� ����� ������." << std::endl;
            continue;
        }

        boost::asio::streambuf buf;
        boost::asio::read_until(socket, buf, "\n");
        std::istream is(&buf);
        std::string message;
        std::getline(is, message);

        Messages parsedMessage = parseMessage(message);

        switch (parsedMessage) {
        case Messages::INVALID_MOVE:
            std::cout << "�������� ���. �������� ������ ������." << std::endl;
            break;
        case Messages::OTHER_PLAYER_MOVED:
            std::cout << "������ ����� ������ ���.\n" << message.substr(18) << std::endl;
            break;
        case Messages::WIN:
            std::cout << "�����������! �� ��������!" << std::endl;
            return;
        case Messages::LOSE:
            std::cout << "�� ���������. ���������� �����." << std::endl;
            return;
        case Messages::DRAW:
            std::cout << "���� ���������� ������." << std::endl;
            return;
        case Messages::CHAT_MESSAGE:
            std::cout << "��������� � ����: " << message.substr(6) << std::endl;
            break;
        case Messages::BOARD_STATE:
            std::cout << "������� �����:\n" << message << std::endl;
            break;
        default:
            std::cerr << "����������� ��������� �� �������." << std::endl;
            break;
        }
    }
}

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", std::to_string(PORT));
        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        setDifficulty(socket);
        makeMove(socket);
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
