#include <iostream>

// test 
#include "obj/src/steering.cpp"

int main(int argc, char** argv)
{

    try 
    {

        struct can_frame frame;

        frame.can_id = 0x654;
        frame.can_dlc = 5;
        sprintf((char *)frame.data, "suca");

        Steering* ctSteer = new Steering("vcan0");

        float angle = 3.14;
        ctSteer->setSteeringAngle(angle);
        
        sleep(60);
    }
    catch(CanException &eErr)
    {
        printf("[ ERROR ]\n");
        printf(
            "[ MESSAGE ]: %s, [ CODE ]: %d\n", 
            eErr.getMsg(), eErr.getStatusCode()
        );
    }
    catch(...) 
    {
        printf("cat vinia un beg in dal cul");
    }

    return 0;
}