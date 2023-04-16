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
    int switches_state_WPH = 0;
    int switches_state_LO = 0;
    int switches_state_LI = 0;
    int switches_state_C = 0;
    int switches_state_H = 0;
    int light_color=5000;
    for (int day = 0; day < 1; ++day) {
        for (int hour = 0; hour < 24; ++hour) {
            std::cout<<"---------------------------------"<<std::endl;
           // std::cout<<switches_state_C<<" "<<switches_state_LO<< " "<< switches_state_H<< " "<<switches_state_WPH<< " "
           //          <<switches_state_LI<<std::endl;
           std::cout<<hour<<":00"<<std::endl;
            std::cout<<"---------------------------------"<<std::endl;
            std::cout
                    << "Hello, User!\nEnter the status of all the main sensors and lights outside temperature(one number),\n"
                       "inside temperature (one number), is there movement outside (yes/no),\nis the light on "
                       "in the house(on/off)." << std::endl;
            std::getline (std::cin, answer);

            std::stringstream answer_stream(answer);

            int insideTemp, outsideTemp;
            std::string outsideMove, currentLight;
            answer_stream >> outsideTemp >> insideTemp >> outsideMove >> currentLight;

              if (outsideTemp < 0 && switches_state_WPH==0) {
                  switches_state_WPH |= WATER_PIPE_HEATING;
                  std::cout<<"The water supply heating system is on" << std::endl;
              } else {
                  if (outsideTemp > 5 && switches_state_WPH==8) {
                      switches_state_WPH &= ~WATER_PIPE_HEATING;
                      std::cout << "The water supply heating system is off" << std::endl;
                  }
              }

              if (((hour>16 && hour<24) || (hour>=0 && hour<6)) && switches_state_LO==0) {
                  switches_state_LO |= LIGHTS_OUTSIDE;
                  std::cout<<"The garden light is on" << std::endl;
              }
              else{
                  if (outsideMove=="yes" && switches_state_LO==0) {
                      switches_state_LO |= LIGHTS_OUTSIDE;
                      std::cout<<"The garden light is on" << std::endl;
                  }
                  else {
                      if (switches_state_LO == 2 && (hour > 5 && hour < 16) && outsideMove!="yes") {
                          switches_state_LO &= ~LIGHTS_OUTSIDE;
                          std::cout << "The garden light is off" << std::endl;
                      }
                  }
              }

              if (insideTemp<22 && switches_state_H==0) {
                  switches_state_H |= HEATERS;
                  std::cout<<"Heaters is on" << std::endl;
              }
              else {
                  if (insideTemp>=25 && switches_state_H==4) {
                      switches_state_H &= ~HEATERS;
                      std::cout<<"Heaters is off" << std::endl;
                  }
              }

              if (insideTemp>=30 && switches_state_C==0) {
                  switches_state_C |= CONDITIONER;
                  std::cout<<"Air conditioning is on" << std::endl;
              }
              else {
                  if (insideTemp<=25 && switches_state_C==16) {
                      switches_state_C &= ~CONDITIONER;
                      std::cout<<"Air conditioning is off" << std::endl;
                  }
              }

              if (currentLight=="on" && (hour>15 && hour<21) && switches_state_LI==0) {
                  light_color-=575;
                  switches_state_LI |= LIGHTS_INSIDE;
                  std::cout<<"The light in the room is on, the current color temperature:"<<light_color<<"K" << std::endl;
              }
              else {
                  if (currentLight=="off" && switches_state_LI==1) {
                      switches_state_LI &= ~LIGHTS_INSIDE;
                      std::cout<<"The light in the room is off"<< std::endl;
                  }
              }

              if (currentLight=="on" && switches_state_LI==0) {
                  switches_state_LI |= LIGHTS_INSIDE;
                  std::cout<<"The light in the room is on"<< std::endl;
              }

              if (currentLight=="on") {
                  std::cout<<"The current color temperature:"<<light_color<<"K" << std::endl;
              }
        }
    }
}
