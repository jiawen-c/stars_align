Stars Align: A simulation of moving stars
===

Goal
===
This simulation shows stars freely moving about a space. When they are asked to align, they move into formation with a graphical representation of a word answer.

My goal for this project was to use enviro to understand events. To that end, I used different screen elements and tracked clicks, and emitted events that carried specific IDs and coordinate position information, that individual agents had to decode.

Key Challenges
===
My primary issue was how to address the journey of many star agents to their position in the star formation, without collisions. It is a little bit of a marching band issue. Initially, I tried to assign each agent to the nearest formation position. However, this didn't work, because if the number of the agents didn't exactly equal the number of formation positions, I would neglect to query all the agents. This would mean that only some agents were going to the nearest formation position, but not necessarily that each journey made to a formation position was the shortest possible. Ultimately, I landed on a solution of iterating through every point in a formation and assigning that position to the nearest star agent.

However, this could be computationally expensive, so a future improvement might be organizing these positions and the known positions of star agents into zones within the simulation space, thereby reducing the number of agents to query for each position in the formation.


Getting the Code
===
Clone this repository, and open the docker image environment. See below.

Dockerhub Images
===

To start the docker image environment, do
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.5 bash
```
This will start a bash prompt from which to build this project while running the enviro server.

Viewing the Simulation
===
You will need to do the following after opening the image:
```
make
esm init
enviro
```

Then navigate your browser to `http://localhost` you should see a rectangular walled area. 

You can press `Ctrl-C` at the `bash` interface to stop the enviro server. 

Getting the Stars Moving
===

Click the "Reset" button to see the stars move.

Getting the Stars to Answer You
===
Click the "Align" button to see the stars' answer to your yes/no question.

Acknowledgements
===
This project is based on the work of Professor Klavins. (https://github.com/klavinslab/enviro) 

I used ECE 520 knowledge to complete the project, and thank classmates for their help in understanding and working the examples. 