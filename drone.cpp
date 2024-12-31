#include <iostream>
#include <cmath>

class Drone {
private:
    float x, y, z; 
    float yaw, pitch, roll; 
    float battery;

public:
    Drone() : x(0), y(0), z(0), yaw(0), pitch(0), roll(0), battery(100) {}

    void moveForward(float distance) {
        x += distance * std::cos(yaw);
        y += distance * std::sin(yaw);
        battery -= distance * 0.1f; 
    }

    void moveUp(float height) {
        z += height;
        battery -= height * 0.2f; 
    }

    void rotate(float deltaYaw, float deltaPitch, float deltaRoll) {
        yaw += deltaYaw;
        pitch += deltaPitch;
        roll += deltaRoll;
        battery -= std::abs(deltaYaw + deltaPitch + deltaRoll) * 0.05f;
    }

    void displayStatus() const {
        std::cout << "Position: (" << x << ", " << y << ", " << z << ")\n";
        std::cout << "Orientation: Yaw: " << yaw << " Pitch: " << pitch << " Roll: " << roll << "\n";
        std::cout << "Battery: " << battery << "%\n";
    }

    bool isOperational() const {
        return battery > 0;
    }
};

int main() {
    Drone myDrone;

    while (myDrone.isOperational()) {
        myDrone.displayStatus();

        char command;
        std::cout << "\nCommands: (f) Forward, (u) Up, (r) Rotate, (q) Quit\n";
        std::cout << "Enter command: ";
        std::cin >> command;

        switch (command) {
            case 'f': {
                float distance;
                std::cout << "Enter distance: ";
                std::cin >> distance;
                myDrone.moveForward(distance);
                break;
            }
            case 'u': {
                float height;
                std::cout << "Enter height: ";
                std::cin >> height;
                myDrone.moveUp(height);
                break;
            }
            case 'r': {
                float deltaYaw, deltaPitch, deltaRoll;
                std::cout << "Enter yaw, pitch, roll changes: ";
                std::cin >> deltaYaw >> deltaPitch >> deltaRoll;
                myDrone.rotate(deltaYaw, deltaPitch, deltaRoll);
                break;
            }
            case 'q':
                std::cout << "Exiting simulation...\n";
                return 0;
            default:
                std::cout << "Invalid command.\n";
        }
    }

    std::cout << "Battery depleted. Simulation ended.\n";
    return 0;
}
