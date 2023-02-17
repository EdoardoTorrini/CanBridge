#include <iostream>

// test 
#include "obj/src/can_thread.cpp"

int main(int argc, char** argv)
{

    try {

        struct can_frame frame;

        frame.can_id = 0x654;
        frame.can_dlc = 5;
        sprintf((char *)frame.data, "suca");

        CanThread* ctTest = new CanThread("vcan0");

        ctTest->write_data(frame);

    }
    catch(...) {
        printf("cat vinia un beg in dal cul");
    }

    return 0;
}