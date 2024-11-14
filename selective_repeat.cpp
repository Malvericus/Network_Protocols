#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int simulate(int windowsize);
int receiver(int tmp1);
int negack(int tmp1);

int receiver(int tmp1) {
    return rand() % tmp1;
}

int negack(int tmp1) {
    return rand() % tmp1;
}

int simulate(int windowsize) {
    int tmp1 = rand() % windowsize;
    return (tmp1 == 0) ? windowsize : tmp1;
}

int main() {
    srand(time(0));
    int windowsize = 0, noofPacket = 0, morePacket;
    int tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0, tmp5 = 0;

    // Initialize number of packets
    cout << "Number of frames is: ";
    cin >> noofPacket;
    cout << "Window Size is: ";
    cin >> windowsize;

    morePacket = noofPacket;

    while (morePacket > 0) {
        tmp1 = simulate(min(windowsize, morePacket)); // Frames to send in the current window
        tmp4 += tmp1;

        if (tmp4 > noofPacket) tmp4 = noofPacket;

        for (int i = noofPacket - morePacket; i < tmp4; i++) {
            cout << "\nSending Frame " << i;
        }

        tmp2 = receiver(tmp1); // Successful acknowledgments
        tmp3 += tmp2;

        if (tmp3 > noofPacket) tmp3 = noofPacket;

        tmp5 = negack(tmp1); // Simulate negative acknowledgment
        if (tmp5 != 0) {
            cout << "\nNo acknowledgment for frame " << tmp5;
            cout << "\nRetransmitting frame " << tmp5;
        }

        morePacket -= tmp1;

        if (windowsize <= 0) windowsize = min(4, morePacket);
    }

    cout << "\nSelective Repeat Protocol Ends. All packets are successfully transmitted." << endl;
    return 0;
}