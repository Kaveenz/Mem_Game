#include "mbed.h"
#include "ThisThread.h"
#include <cstdlib> // For rand() and srand()
#include <vector>
#include "NHD_0216HZ.h"
#include <chrono>
int points;
int highscore;


 
// Define LEDs
DigitalOut L1(D2);
DigitalOut L2(D3);
DigitalOut L3(D4);


// Define Buttons with PullDown resistors
DigitalIn B1(A0, PullDown);
DigitalIn B2(A1, PullDown);
DigitalIn B3(A2, PullDown);

// SPEAKER 
#define SPEAKER D6
//Define the frequency of basic music notes
# define Do     0.5
# define Re     0.45
# define Mi     0.4
# define Fa     0.36
# define So     0.33
# define La     0.31
# define Si     0.3
# define No     0
//Define the beat length (e.g. whole note, half note)
# define b1     0.5
# define b2     0.25
# define b3     0.125
# define b4     0.075

float note[] = {};
float beat[] = {};
/*
wrong
float note[] = {Si,Mi,Do,No};
float beat[] = {b3,b3,b3,b3};
right
float note[] = {Do,Mi,Si,No};
float beat[] = {b3,b3,b3,b3};
tune Start
float note[] = {Do,Mi,Do,Si,Do,Mi,Do,Si,Do,Mi,Do,No};
float beat[] = {b4,b4,b4,b4,b4,b4,b4,b4,b4,b4,b4,b4};
*/
//Define the PWM output for the speaker(given)

PwmOut speaker(D6);


//Define the frequency of basic music notes
#define Do     0.5
#define Re     0.45
#define Mi     0.4
#define Fa     0.36
#define So     0.33
#define La     0.31
#define Si     0.3
#define No     0
//Define the beat length (e.g. whole note, half note)
#define b1     0.5
#define b2     0.25
#define b3     0.125
#define b4     0.075


float notesCorrect[] = {987.77, 659.26, 523.25, 0.0}; // Frequencies for B (Si), E (Mi), C (Do), and a rest (No)
float durationsCorrect[] = {0.5, 0.5, 0.5, 0.5};       // Durations for each note in seconds
// Function to play a melody
void play_melody_correct() {
   Timer timer;
   for (int i = 0; i < sizeof(notesCorrect) / sizeof(notesCorrect[0]); i++) {
       timer.reset();
       timer.start();


       if (notesCorrect[i] > 0) {
           speaker.period(1.0 / notesCorrect[i]); // Set the frequency
           speaker.write(0.5);            // 50% duty cycle for sound
       } else {
           speaker.write(0.0);            // Rest
       }


       while (timer.read() < durationsCorrect[i]) {
           // Wait for the duration without blocking
       }


       speaker.write(0.0);                // Silence between notes
       timer.reset();


       while (timer.read() < 0.1) {
           // Pause between notes (100ms)
       }
   }
}

float notes_start[] = {523.25, 659.26, 523.25, 493.88, 523.25, 659.26, 523.25, 493.88, 523.25, 659.26, 523.25, 0.0}; // Frequencies for C (Do), E (Mi), C (Do), B (Si), and rest (No)
float durations_start[] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25}; // Durations for each note in seconds
void play_melody_start() {
   Timer timer;
   for (int i = 0; i < sizeof(notes_start) / sizeof(notes_start[0]); i++) {
       timer.reset();
       timer.start();

       if (notes_start[i] > 0) {
           speaker.period(1.0 / notes_start[i]); // Set the frequency
           speaker.write(0.5);            // 50% duty cycle for sound
       } else {
           speaker.write(0.0);            // Rest
       }

       while (timer.read() < durations_start[i]) {
           // Wait for the duration without blocking
       }

       speaker.write(0.0);                // Silence between notes
       timer.reset();

       while (timer.read() < 0.1) {
           // Pause between notes (100ms)
       }
   }
}

float notes_wrong[] =       {493.88,329.63,261.63,0.0};
float durations_wrong[] =   {0.33,0.33,0.33,0.33};
void play_melody_wrong() {
   Timer timer;
   for (int i = 0; i < sizeof(notes_wrong) / sizeof(notes_wrong[0]); i++) {
       timer.reset();
       timer.start();


       if (notes_wrong[i] > 0) {
           speaker.period(1.0 / notes_wrong[i]); // Set the frequency
           speaker.write(0.5);            // 50% duty cycle for sound
       } else {
           speaker.write(0.0);            // Rest
       }


       while (timer.read() < durations_wrong[i]) {
           // Wait for the duration without blocking
       }


       speaker.write(0.0);                // Silence between notes
       timer.reset();


       while (timer.read() < 0.1) {
           // Pause between notes (100ms)
       }
   }
}

////////////////////////////////////////////////////////////////////
// Function to display LED combinations and wait for user input


void displayLevel(int level) {
    std::vector<int> sequence; //vector to store the sequence of LED indices that are on


    // Generate the LED combination sequence for the level
    for (int i = 0; i < level; i++) {
        // Pick a random LED to turn on (only one LED per combination)
        int led = rand() % 3;  //Random number between 0, 1, 2
        sequence.push_back(led);
    }

    //Show the LED combinations one by one
    for (auto& ledIndex : sequence) {
        L1 = (ledIndex == 0) ? 1 : 0; //Turn on LED 1 if ledIndex is 0
        L2 = (ledIndex == 1) ? 1 : 0; //Turn on LED 2 if ledIndex is 1
        L3 = (ledIndex == 2) ? 1 : 0; //urn on LED 3 if ledIndex is 2


        printf("LED states: L1=%d, L2=%d, L3=%d\n", L1.read(), L2.read(), L3.read());
      
        ThisThread::sleep_for(1000); //Wait for 1 second to show the LED


        L1 = 0; L2 = 0; L3 = 0;    //Turn off all LEDs
        ThisThread::sleep_for(500); //Pause before showing the next combination


    }

    // Wait for the user to press the correct buttons in sequence


    for (int i = 0; i < level; i++) {
        bool buttonPressed = false;


        while (!buttonPressed) {
            bool A = !B1.read(); // Read button states
            bool B = !B2.read();
            bool C = !B3.read();


            // Check if the correct button is pressed for the current LED
            if ((sequence[i] == 0 && A) || (sequence[i] == 1 && B) || (sequence[i] == 2 && C)) {
                printf("Correct! Button %d pressed when LED %d was ON.\n", sequence[i] + 1, sequence[i] + 1);
                play_melody_correct();
                buttonPressed = true;
                points += 1;
            

                if(highscore < points)
                {
                    highscore = points;
                }

            } else if (A || B || C) {
                // Wrong button pressed
                printf("Wrong! Deducting a point.\n");
                play_melody_wrong();
                buttonPressed = true;
                points = (points > 0) ? points - 1 : 0; // Avoid negative points
            }
            


            ThisThread::sleep_for(200); // Debounce time to avoid multiple presses
        }
    }
}


// Main function
int main() {
    // Seed the random number generator
    srand((unsigned int)time(NULL));


    init_spi();
    init_lcd();
    printf("Starting memory game. Press buttons in the correct order!\n");
    
    play_melody_start();
   
    int level = 1;
    while (true) {
        set_cursor(0, 0); 
        char lev[20];
        sprintf(lev, "Current Level: %d", level);
        print_lcd(lev);
        displayLevel(level); // Display the LED sequence and wait for input

        set_cursor(0,1);
        char score[20];
        sprintf(score, "Sco:%d  HiSco:%d",points, highscore );
        print_lcd(score);

        level++; // Increase level after each round
        if (level > 10) 
        {
            level = 1; // Reset to level 1 after level 3
            printf("Current Highscore  %d\n", highscore);
            points = 0;
        }
    }
}