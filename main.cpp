/*
 * File:Main.cpp
 * Description:this will make a descion tree for a game that guesses what animal you are thinking of kinda like akinator but just for animals
 * Author:Miguel Pizano Regalado
 * Email:miguelp6479@student.vvc.edu
 
   This program will create a decision tree for an animal
   guessing game.

   
   Pseudocode has been added as a hint to help with developing this
   program
*/

#include <iostream>
#include <fstream>
#include <string>
#include "binary_tree.h"

Binary_tree read(istream& in)
{
  // Note the stream is called in
  // declare data as string
  string data;
  // declare level as integer
  int level;
  // get level from stream
  in >> level;

  if(level == -1)
  {
    return Binary_tree();
  }  
  // get line from stream and assign it to data
  getline(in,data);

  // declare left as a Binary_tree and assign it read(in) 
  // Note:  it is a recursive call
  Binary_tree left = read(in);

  // declare right as a Binary_tree and assign it to read(in)
  // Note:  it is a recursive call
  Binary_tree right = read(in);
  // return Binary_tree(data, left, right)
  return Binary_tree(data, left, right);
}

void write(ostream& out, const Binary_tree& tree, int level)
{
  if(tree.empty())
  {
    out << -1 << endl;
    return;
  }
  // output level + ' ' + tree.data() + \n to out
  out << level << " " << tree.data() << endl;
    
  // call write (out, tree.left(), level + 1)
  write(out,tree.left(), level+1);
  // call write (out, tree.right(), level + 1)
  write(out, tree.right(), level+1);
}

/*
 * helper function that will help with definite or indefinite 
 * articles in a string
 */
std::string article(const std::string& entry)
{
  std::string article = "a";
  if (std::string("aeiou").find(entry[0]) != std::string::npos)
  {
    article =  "an";
  }
  return article;
}

int main(int argc,char **argv)
{
  Binary_tree root;
  // Strategy
  // get the filename from the command line arguments
  if(argc != 2)
  {
    cout << "Invalid arguments" << endl;
    return -1;
  }
  string filename=argv[1];
  // open the file stream
  ifstream in;
  in.open(filename);
  // initialize the root Binary_tree variable with data from the 
  // file stream to initialize the decision tree root by calling
  // the read function
   
  root = read(in);
  in.close();

  // declare a Binary_tree question_tree and set it to root
  Binary_tree question_tree = root;

  bool done = false;
  string animal; 
  string question_response;
  // while not done
  while(!done)
  {
    // declare a string called response
    string response;
    // declare a Binary_tree called left and set it to 
    Binary_tree left = question_tree.left();
    // declare a Binary_tree called right and set it to 
    Binary_tree right = question_tree.right();
    if(left.empty() && right.empty())
    {
      // Add code here that will carry on something like the 
      // following dialog:
      // Is it a mammal? Y  
      // Does it have stripes? N  
      // Is it a pig? N  
      cout << "Is it " << article(question_tree.data()) << " " << question_tree.data() << "? ";
      // get the response from the user and 
      cin >> response;
      // if it is correct,
      if(response == "Y" || response == "y")
      {
        // print "I guessed it!"
        cout << "I guessed it!" << endl;
      }
      // else
      else
      {
        // print "I give up. What is it?"
        cout << "I give up. What is it?";
        cin >> animal;
        // if user enters A hamster  
        // then
        // print "Please give me a question that is true 
        // for a hamster and false for a pig."
        cout << "Please give me a question that is true for " << article(animal) << " " << animal << " but false for " << article(question_tree.data()) << " " << question_tree.data() << endl;
        //get the response from the user
        //example user response: Is it small and cuddly?
        getline(cin, question_response);
        getline(cin, question_response);

        // Insert a node into question_tree so that this 
        // question is used in future dialogs:
        // One strategy to consider is to implement a set method 
        // in the Binary_tree called root
        // the set method will set the data and the left and right 
        // subtrees for the given root
        question_tree.set(question_response, Binary_tree(animal), Binary_tree(question_tree.data()));
      }
      // Future dialog:
      // print "May I try again? "
      cout<<"May I try again? ";
      // get response
      cin>>response;
      // if response is yes
      if(response == "n" || response == "N")
      {
        done = true; 
      }
      else
      {
        question_tree = root;
      }
    }
    else
    {
      do
      {
        // print Is it a question_tree.data()  (y/n): 
        cout << question_tree.data()<<" (y/n) ";
        // get response
        cin >> response;
      }
      while (response!="y" and response != "n");
      if(response=="y")
      {
        question_tree = left;
      }
      else
      {
        question_tree = right;
      }
    }
  }
  // When done, write the decision tree to the data file by calling
  // the write function so that the new
  // question and answer is added to the data file
  ofstream out;
  out.open(filename);
  write(out,root,0);
}
