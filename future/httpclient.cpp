#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <future>

using namespace std;

string Receive(int & fd)
{
    char buffer[1024];
    string response;
    while (true) {
        int n = recv(fd, buffer, sizeof(buffer), 0);
        if (n == -1) {
            throw runtime_error("Failed to receive response");
        } else if (n == 0) {
            break;
        } else {
            response.append(buffer, n);
        }
    }
    return response;
}

class HTTPClient {
public:
    HTTPClient(const string& host, int port) : m_host(host), m_port(port) {}

    void sendRequest(const string& request) {
        // 创建socket连接
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            throw runtime_error("Failed to create socket");
        }

        // 获取服务器IP地址
        struct hostent* server = gethostbyname(m_host.c_str());
        if (server == nullptr) {
            throw runtime_error("Failed to get server address");
        }

        // 设置服务器地址
        struct sockaddr_in serv_addr;
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(m_port);
        memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

        // 连接服务器
        if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
            throw runtime_error("Failed to connect to server");
        }

        // 发送请求
        if (send(sockfd, request.c_str(), request.length(), 0) == -1) {
            throw runtime_error("Failed to send request");
        }

        //std::future<string> f = std::async(Receive, std::ref(sockfd));
        // 接收响应

        std::packaged_task<string(int &)> task(Receive);
        std::future<string> f = task.get_future();
        task(std::ref(sockfd));

        // 输出响应
        cout << f.get() << endl;        

        // 关闭socket连接
        close(sockfd);

    }

private:
    string m_host;
    int m_port;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: client <host> <port>" << endl;
        return 1;
    }

    string host(argv[1]);
    int port = atoi(argv[2]);

    HTTPClient client(host, port);

    string request = "GET / HTTP/1.1\r\n"
                     "Host: " + host + "\r\n"
                     "Connection: close\r\n"
                     "\r\n";

    client.sendRequest(request);

    return 0;
}
