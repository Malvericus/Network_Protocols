#include <iostream>
#include <deque>
#include <string>
#include <thread>
#include <chrono>
#include <csignal>

using namespace std;

// Packet class to simulate data packets.
class Packet {
private:
    int id;
    int size;
public:
    // Constructor to initialize packets.
    Packet(int packet_id, int packet_size) : id(packet_id), size(packet_size) {}
    
    // Getter for size
    int getSize() const {
        return size;
    }
    
    // Getter for ID
    int getId() const {
        return id;
    }
    
    // String representation of the packet
    string toString() const {
        return "Packet(id=" + to_string(id) + ", size=" + to_string(size) + ")";
    }
};

// Overload << operator for Packet for easier logging
ostream& operator<<(ostream& os, const Packet& pkt) {
    os << pkt.toString();
    return os;
}

// LeakyBucket class to simulate leaky bucket algorithm.
class LeakyBucket {
private:
    int leakRate;               // Rate at which packets are transmitted (units per tick)
    int bufferSizeLimit;        // Maximum buffer size
    int currBufferSize;         // Current size of the buffer
    deque<Packet> buffer;       // Buffer to store packets (using deque for efficient FIFO operations)
public:
    // Constructor to initialize leak rate and maximum buffer size available.
    LeakyBucket(int leak_rate, int size) 
        : leakRate(leak_rate), bufferSizeLimit(size), currBufferSize(0) {}
    
    // Function to add new packets at the end of the buffer.
    void addPacket(const Packet& newPacket) {
        if(currBufferSize + newPacket.getSize() > bufferSizeLimit) {
            // If the packet cannot fit in the buffer, then reject the packet.
            cout << "[WARNING] Bucket is full. Packet rejected: " << newPacket << endl;
            return;
        }
        // Add packet to the buffer.
        buffer.push_back(newPacket);
        // Update current Buffer Size.
        currBufferSize += newPacket.getSize();
        // Print out the appropriate message.
        cout << "[INFO] Packet added to bucket: " << newPacket << endl;
    }
    
    // Function to transmit packets. Called at each clock tick.
    void transmit() {
        if(buffer.empty()) {
            // Check if there is a packet in the buffer.
            cout << "[DEBUG] No packets in the bucket." << endl;
            return;
        }
        // Initialize n to the leak rate.
        int n = leakRate;
        while(!buffer.empty()) {
            Packet topPacket = buffer.front();
            int topPacketSize = topPacket.getSize();
            // Check if the packet can be transmitted or not.
            if(topPacketSize > n) break;
            // Reduce n by packet size that will be transmitted.
            n -= topPacketSize;
            // Update the current buffer size.
            currBufferSize -= topPacketSize;
            // Remove packet from buffer.
            buffer.pop_front();
            cout << "[INFO] Packet transmitted: " << topPacket << endl;
        }
    }
    
    // Getter for current buffer size
    int getCurrentBufferSize() const {
        return currBufferSize;
    }
    
    // Getter for buffer length
    int getBufferLength() const {
        return buffer.size();
    }
};

int main() {
    // Initialize LeakyBucket with leakRate=1000 units and bufferSizeLimit=10000 units
    LeakyBucket bucket(1000, 10000);
    
    // Add example packets to the bucket
    bucket.addPacket(Packet(1, 200));
    bucket.addPacket(Packet(2, 500));
    bucket.addPacket(Packet(3, 400));
    bucket.addPacket(Packet(4, 500));
    bucket.addPacket(Packet(5, 200));
    
    // Transmission loop that terminates when all packets are transmitted
    while(bucket.getBufferLength() > 0) {
        bucket.transmit();
        cout << "Waiting for next unit." << endl;
        // Sleep for 1 second to simulate a clock tick
        this_thread::sleep_for(chrono::seconds(1));
    }
    
    cout << "\nLeaky Bucket simulation completed. All packets have been transmitted." << endl;
    cout << "Final Buffer Size: " << bucket.getCurrentBufferSize() << " units." << endl;
    cout << "Packets remaining in buffer: " << bucket.getBufferLength() << endl;
    
    return 0;
}