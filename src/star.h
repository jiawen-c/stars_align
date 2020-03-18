#ifndef __STAR_AGENT__H
#define __STAR_AGENT__H 

#include "enviro.h"

using namespace enviro;
using namespace std;

//! StarController class

//! Defines the individual star agent that wanders the space and gets into formation.
class StarController : public Process, public AgentInterface {

    public:
    //! Constructor
    StarController() : Process(), AgentInterface(), assigned(0), target_x(0), target_y(0){}

    //! Initializes controller, and watches for instruction to wander, stop or go to a target
    void init() {
        watch("wander", [&](Event e) {
            
            track_velocity(id()*35 % 20, id() % 3);    // temp until sensors working
            clear_label();
            assigned = false;
            /* Sensors still aren't working. Adding into to star.json results in segfault
            if ( sensor_value(0) < 60 ) {
                // Forward
                track_velocity(0, 1.5*id());
            } else {
                // Rotate
                track_velocity(4, 0);
            }
            */
        });

        watch("stop", [this](Event e) {
            string a = e.value()["star_id"];
            string b = get_client_id();
            
            if (a.compare(b) == 0) {
                track_velocity(0, 0);
            }
        });

        watch("go_to_target", [this](Event e) {
            string a = e.value()["star_id"];
            string b = get_client_id();
            
            if (a.compare(b) == 0) {
                std::cout << "Star " << a << " assigned\n";
                assigned = true;

                target_x = (int) e.value()["x"];
                target_y = (int) e.value()["y"];
                move_toward(target_x, target_y);
            }
        });
    }

    //! Empty
    void start() {}

    //! On each update, move closer to target
    void update() {
        if (assigned) {
            move_toward(target_x, target_y, 150, 40 );
        }
    }

    //! Empty
    void stop() {}

    private:
    int target_x;
    int target_y;
    bool assigned;

};

//! Star Class

//! The Star class is controlled by the StarController
class Star : public Agent {
    public:
    Star(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    StarController c;
};

DECLARE_INTERFACE(Star)

#endif