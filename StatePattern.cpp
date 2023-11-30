// StatePattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>

enum TrafficLightType {RED, AMBER, GREEN};

class TrafficLightState
{
public:
    TrafficLightType trafficLightType; //Used to identify which derived class we should make unique when setting the unq pointer of this type, as we cant make unique abstract types, but we can have a unq pointer that is of an abstract type

    virtual void handle() = 0; //Pure virtual function, must be implemented in classes deriving from this abstract class

protected:
    std::string colour;
};

class RedTrafficLightState : public TrafficLightState
{
public:
    RedTrafficLightState()
    {
        colour = "RED";
        trafficLightType = RED;
    }
    void handle() override
    {
        std::cout << "Traffic Light Colour is " + colour + "\n";
    }
};

class AmberTrafficLightState : public TrafficLightState
{
public:
    AmberTrafficLightState()
    {
        colour = "AMBER";
        trafficLightType = AMBER;
    }
    void handle() override
    {
        std::cout << "Traffic Light Colour is " + colour + "\n";
    }
};

class GreenTrafficLightState : public TrafficLightState
{
public:
    GreenTrafficLightState()
    {
        colour = "GREEN";
        trafficLightType = GREEN;
    }
    void handle() override
    {
        std::cout << "Traffic Light Colour is " + colour + "\n";
    }
};

class TrafficLight 
{
public:

    TrafficLight() : trafficLightState(std::make_unique<RedTrafficLightState>(RedTrafficLightState()))
    {}

    void setState(const std::unique_ptr<TrafficLightState> &newState)
    {
        trafficLightState.reset();
        
        switch (newState->trafficLightType) //Will be used to identify the class, as we cant make unique the abstract type therefore we must deduce to the object type to make that unique instead 
        {
        case RED:
            trafficLightState = std::make_unique<RedTrafficLightState>(RedTrafficLightState());
            break;

        case AMBER:
            trafficLightState = std::make_unique<AmberTrafficLightState>(AmberTrafficLightState());
            break;

        case GREEN:
            trafficLightState = std::make_unique<GreenTrafficLightState>(GreenTrafficLightState());
            break;
        default:
            break;
        }
    }

    void change()
    {
        trafficLightState->handle();
    }

private:
    std::unique_ptr<TrafficLightState> trafficLightState; 
};



int main()
{
    TrafficLight trafficLight;

    trafficLight.change(); //Initial state red

    //Set state to amber and then show value
    trafficLight.setState(std::unique_ptr<TrafficLightState>(new AmberTrafficLightState()));
    trafficLight.change();

   // Set state to green and then show value
    trafficLight.setState(std::unique_ptr<TrafficLightState>(new GreenTrafficLightState()));
    trafficLight.change();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
