#ifndef __POSITION_AGENT__H
#define __POSITION_AGENT__H 

#include "enviro.h"
#include <float.h>
#include <math.h>
#include "line.h"

using namespace enviro;
using namespace std;
#define STAR_COUNT 40


class positionController : public Process, public AgentInterface {

    public:
    positionController() : Process(), AgentInterface() {}

    void init() {
        watch("button_click", [&](Event& e) {
            string value = e.value()["value"];
            
            if (value.compare("align") == 0) {
                emit(Event("align"));
                std::cout << "align pressed" << "\n";
            } 
            
            else if (value.compare("reset") == 0) {
                emit(Event("reset"));
                std::cout <<"reset pressed, should wander" << "\n";
            }
        });

        watch("reset", [this](Event e) {
            emit(Event("wander"));
            std::cout << "emitted: wander\n";
        });

        watch("align", [this](Event e) {
            assign_position(2);
            //TODO assign_position((rand() / 47) % 3);
        });


        // Add stars for simulation
        for (int i = 0; i < STAR_COUNT; i++) {
            Agent& new_star = add_agent("Star", i, i -100, 0, STAR_STYLE);
            new_star.set_client_id(to_string(i));
            agent_ids[i] = new_star.get_id();
        }

    }
    void start() {}
    void update() {}
    void stop() {}

    const json STAR_STYLE = { 
                   {"fill", "yellow"}, 
                   {"stroke", "yellow"}, 
                   {"strokeWidth", "10px"},
                   {"strokeOpacity", "0.75"}
               };

    private:
    // Array of agent references
    int agent_ids[STAR_COUNT];

    vector<Point> line_formation = {Point{0, -30}, Point {0, -60}, Point{0, 0}, Point{0, 60}, Point{0, 90}};
    
    Line lines;
    vector<Point> no_formation = lines.get_no();
    vector<Point> ya_formation = lines.get_ya();

    void assign_position(int which_formation) {
        vector<Point> positions;    // Points to assign out to stars
        
        // TODO copy data structure for used formation
        switch (which_formation) {
            case 0:
                // Line formation
                positions = line_formation;
                break;

            case 1:
                // NO
                positions = no_formation;
                break;

            case 2:
                // YA
                positions = ya_formation;
                break;
            default:
                // MEH
                break;
        }

        // copy agent ids
        typedef struct ag_info {
            int id;
            bool is_assigned;
        } AgentInfo;

        vector<AgentInfo> agents;
        for (int i = 0; i < STAR_COUNT; i++) {
            agents.push_back( AgentInfo{agent_ids[i], false} );
        }

        // For each position, find nearest star
        for (int pos_idx = 0; pos_idx < positions.size(); pos_idx++) {
            Point p = positions[pos_idx];

            int closest_agent = 0;
            double shortest_dist = DBL_MAX;

            for (int i = 0; i < agents.size(); i++) {
                Agent& star = find_agent(agents[i].id);

                if ( !agents[i].is_assigned ) {
                    double dist = sqrt(pow(star.x()-p.x, 2) + pow(star.y()-p.y, 2));
                    if (dist < shortest_dist) {
                        closest_agent = i;
                        shortest_dist = dist;
                    }
                }
            }

            // Assign point to star
            agents[closest_agent].is_assigned = true;
            std::cout << "Star " << closest_agent << " to "<< "("<< p.x << ", " << p.y << ")\n";
            emit(Event("go_to_target", {
                { "star_id", to_string(closest_agent) },
                { "x", (p.x) },
                { "y", (p.y) },
            }));
        }

    }

};

class position : public Agent {
    public:
    position(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    positionController c;
};

DECLARE_INTERFACE(position)

#endif