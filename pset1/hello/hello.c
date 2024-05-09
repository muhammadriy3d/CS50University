#include <cs50.h>
#include <stdio.h>

void hello_world(void);
void nameInput(string q, string w);

int main(void)
{
    // First task #1: Hello, world
    hello_world();

    // Second task #2: Get user input of their actual name
    nameInput("What is your name? ", "hello");
}













// system manager of our program

//hello task 1
void hello_world(void)
{
    printf("Hello, world\n");
}

//task2
//get user name w: customize welcome, q: customize question
void nameInput(string q, string w)
{
    string name = get_string("%s", q);
    printf("%s, %s! Nice to have you here\n", w, name);
}