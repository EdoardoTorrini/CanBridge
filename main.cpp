#include <iostream>

// test 
#include "obj/src/res.cpp"  
#include "obj/src/steering.cpp"

int main(int argc, char** argv)
{

    try 
    {

        struct can_frame frame;

        frame.can_id = 0x654;
        frame.can_dlc = 5;
        sprintf((char *)frame.data, "suca");
        
        Res* ctRes = new Res("vcan0");
        Steering* ctSteer = new Steering("vcan0");


        // float angle = 3.14;
        // ctSteer->setSteeringAngle(angle);
        // ctRes->setPowerOn();
        
        sleep(120);

        ctSteer->stop();
        ctRes->stop();
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