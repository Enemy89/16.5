#include <iostream>
#include <sstream>

enum switches
{
    LIGHTS_INSIDE = 1,
    LIGHTS_OUTSIDE = 2,
    HEATERS = 4,
    WATER_PIPE_HEATING = 8,
    CONDITIONER = 16
};

int main() {
    std::string answer;
    int switches_state = 0;
    for (int day = 0; day < 1; ++day) {
        for (int hour = 0; hour < 24; ++hour) {
            std::cout
                    << "Hello, User!\nEnter the status of all the main sensors and lights outside temperature(one number),\n"
                       "inside temperature (one number), is there movement outside (yes/no),\nis the light on "
                       "in the house(on/off)." << std::endl;
            std::cin >> answer;

            std::stringstream answer_stream(answer);

            int insideTemp, outsideTemp;
            std::string outsideMove, currentLight;
            answer_stream >> outsideTemp >> insideTemp >> outsideMove >> currentLight;

            if (outsideTemp < 0) {
                switches_state |= WATER_PIPE_HEATING;
                std::cout<<"The water supply heating system is on" << std::endl;
            } else {
                if (outsideTemp > 5) {
                    switches_state &= ~WATER_PIPE_HEATING;
                    std::cout<<"The water supply heating system is off" << std::endl;
                }
            }
        }

    }
}
