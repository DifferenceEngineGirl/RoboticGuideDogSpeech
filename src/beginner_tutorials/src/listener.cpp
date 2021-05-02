/**
 * Based on code from http://wiki.ros.org/ROS/Tutorials/WritingPublisherSubscriber%28python%29
 */

#include "ros/ros.h"
#include "std_msgs/String.h"

// Initialise the name of the dog, to be used to mark commands
std::string name = "dog";

// Initialise an array containing the desired commands to be listened for
std::string comArray[] = {"sit", "stay", "down", "heel", "forward", "left", "right"};

// Find the number of commands, and save it as a variable
int noOfCom = sizeof(comArray)/sizeof(comArray[0]);

// Set a flag for if a command is found
int comFlag = 0;

// Function to detect a command within a string
void findCom(std::string com, std::string speech, std::size_t expComPos){
  // Find the location of the first character of the given command word in the string
  std::size_t foundCom = speech.find(" " + com + " ", expComPos);
  // If the command word is found where it is expected
  if (foundCom == expComPos){
    // Send the command + "command heard" to the stderr output
    std::cerr << com << " command heard.\n";
    // Send the command to the stdout output, which can be piped to a serial output.
    std::cout << com << "\n";
    // Set the command flag to 1
    comFlag = 1;
  }
}

// Function to recognise a command
void commandRecog(const std_msgs::String::ConstPtr& msg)
{
  // Create a ctring variable containing the input, with added spaces before and after
  std::string potCom = " " + std::string(msg->data) + " ";
  // Create a variable containing the position of the space before the peviously set name
  std::size_t namePos = potCom.find(" " + name + " ");
  // Set the command flag to 0
  comFlag = 0;

  // Send the recieved input to the stderr output
  std::cerr << msg->data.c_str() << "\n";

  // If the name is within the string
  if (namePos != std::string::npos){
    // For each command in the array
    for(int i = 0; i < noOfCom; i++) {
      // If a command hasn't already been found
      if(comFlag == 0) {
        // Run the findCom function for the current command in the array, looking at the word after the name
        findCom(comArray[i], potCom, namePos + name.length() + 1);
      }
    }
  }

  // If no command is found
  if (comFlag == 0) {
    // Send a message to the stderr output
    std::cerr << "No command found\n";
  }
}

// Main function
int main(int argc, char **argv)
{
  // Initialise with any arguments passed from the command line
  ros::init(argc, argv, "listener");

  // Create a ROS node handle
  ros::NodeHandle n;

  // Subscribe to the node, and call the commandRecog function with all data received
  ros::Subscriber sub = n.subscribe("chatter", 1000, commandRecog);


  // Enter a loop until ctrl+C is pressed
  ros::spin();

  return 0;
}

