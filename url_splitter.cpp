#include <iostream>
#include <string>
#include <regex>

using namespace std;

// Function to split a URL into its components
void splitURL(const string& url) {
    // Regex to match the four components of a URL
    regex urlRegex(R"((\w+):\/\/([^\/:]+)(?::(\d+))?(\/.*)?)");
    smatch urlMatch;

    if (regex_match(url, urlMatch, urlRegex)) {
        cout << "URL: " << url << endl;

        // Extracting components
        string protocol = urlMatch[1];      // Protocol (e.g., http, https)
        string hostname = urlMatch[2];      // Hostname (e.g., www.example.com)
        string port = urlMatch[3];          // Port (optional, e.g., 8080)
        string path = urlMatch[4];          // Path (optional, e.g., /index.html)

        // Displaying components
        cout << "Protocol: " << protocol << endl;
        cout << "Hostname: " << hostname << endl;
        cout << "Port: " << (port.empty() ? "Default" : port) << endl;
        cout << "Path: " << (path.empty() ? "/" : path) << endl;
    } else {
        // If the URL does not match the expected format
        cout << "Invalid URL format." << endl;
    }
}

int main() {
    string url;

    cout << "Enter a URL: ";
    getline(cin, url);

    // Call the function to split the URL
    splitURL(url);

    return 0;
}