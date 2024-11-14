#include <iostream>
#include <string>
using namespace std;

int main() {
    string url, protocol, host, port, path;
    cout << "Enter a URL: ";
    cin >> url;

    // Find protocol
    int protocol_pos = url.find("://");
    if (protocol_pos != -1) {
        protocol = url.substr(0, protocol_pos);
        url = url.substr(protocol_pos + 3);
    }

    // Find host, port, and path
    int port_pos = url.find(":");
    int path_pos = url.find("/");
    if (port_pos != -1) {
        host = url.substr(0, port_pos);
        if (path_pos != -1) {
            port = url.substr(port_pos + 1, path_pos - port_pos - 1);
            path = url.substr(path_pos);
        } else {
            port = url.substr(port_pos + 1);
        }
    } else if (path_pos != -1) {
        host = url.substr(0, path_pos);
        path = url.substr(path_pos);
    } else {
        host = url;
    }

    // Display results
    cout << "Protocol: " << (protocol.empty() ? "None" : protocol) << endl;
    cout << "Host/Domain: " << host << endl;
    cout << "Port: " << (port.empty() ? "None" : port) << endl;
    cout << "Path: " << (path.empty() ? "/" : path) << endl;

    return 0;
}
