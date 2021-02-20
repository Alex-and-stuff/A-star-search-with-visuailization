# A-star-search-with-visuailization
building on top of the previous A star code, i used simple openCV to do visualization

# Some notes
so after finishing the path planning program for Eurobot, I thought it would be pretty cool to make a cool program for better visualization.
 In the beginning I was lookong at D++ and some other visualization tools, but I wasn't too familiar with those and I didn't have much time to spare. 
 So after some looking around, I decided to write an individual program in python using openCV, and link the two programs through a txt file.
 this is not the optimal solution, but it made it so that I did not need to do too many changes to the original path planning program and also it was easier to do CV in python for  me.

# Steps
so basically you can initalize the positions and obstacles in the main.c file and then compile. after running the exe program, you will see that the program stops at each search and produces a .txt file. Run the python file and you will get a visualization of the path planning program and also a refined path using an alteration of breseham's line algorithom
