/**
 * @file main.cpp
 * @brief Main client program for the ShapeFile Parser.
 *
 * This program reads shape data from a file, validates it, and calculates
 * areas. It handles all file and data exceptions.
 *
 * @author Magda Hussein
 * @date 3/29/2026
 * @version 1.0
 */

#include <iostream>
#include <fstream>      // For file I/O (ifstream)
#include <string>       // For std::string
#include <iomanip>      // For std::setprecision
#include <stdexcept>    // For std::invalid_argument

#include "GeometryUtils.h"
#include "Exceptions.h"
#include "FileUtils.h"      // NEW: Include the file utility header

using namespace std;

/**
 * @brief Main entry point for the ShapeFile Parser.
 *
 * This function contains all client logic. It handles:
 * 1. Prompting for an initial filename.
 * 2. Calling the file-opening utility.
 * 3. Reading the file line by line.
 * 4. Catching ParseException for unknown shape types.
 * 5. Catching std::invalid_argument for invalid shape dimensions.
 *
 * No other functions or classes should be defined in this file.
 */
int main() {
    // Set up clean console output for floating point numbers
    cout << fixed << setprecision(2);

    string filename;
    ifstream file;
    int lineNumber = 0;

    // --- 1. File Opening Logic ---
    cout << "Enter filename: ";
    cin >> filename;

    // Call the new utility function to handle the entire file-opening process.
    // We pass 'file' by reference to be opened, and 'filename' by value.
    // STUDENT TODO: Wrap the call to openFileForReading in a try...catch block.
    try {
        openFileForReading(file, filename);
    }
    catch (const FileOpenException& e) {
        cerr << "Error: " << e.what() << endl;
        return 1; // Exit the program with an error code
    }

    // --- 2. File Parsing Logic ---
    cout << "--- Processing Shapes ---" << endl;
    string shapeType;

    // STUDENT TODO: Wrap the entire 'while' loop in a try...catch block
    // that catches a ParseException.
    try {
        // Read from the file one "word" at a time
        while (file >> shapeType) {
            lineNumber++;

            try {
                if (shapeType == "square") {
                    double side;
                    file >> side;

                    // STUDENT TODO: Wrap the call to calculateArea in a
                    // try...catch block to handle std::invalid_argument.
                    try {
                        double area = calculateArea(side); // Call library function
                        cout << "Line " << lineNumber << ": Square Area: " << area << endl;
                    }
                    catch (const std::invalid_argument& e) {
                        cerr << "Line " << lineNumber << ": Error - " << e.what() << endl;
                    }
                }
                else if (shapeType == "rectangle") {
                    double length, width;
                    file >> length >> width;

                    // STUDENT TODO: Wrap the call to calculateArea in a
                    // try...catch block to handle std::invalid_argument.
                    try {
                        double area = calculateArea(length, width); // Call overloaded library function
                        cout << "Line " << lineNumber << ": Rectangle Area: " << area << endl;
                    }
                    catch (const std::invalid_argument& e) {
                        cerr << "Line " << lineNumber << ": Error - " << e.what() << endl;
                    }
                }
                else if (shapeType == "circle") {
                    double radius;
                    file >> radius;

                    // STUDENT TODO: Wrap the call to calculateCircleArea in a
                    // try...catch block to handle std::invalid_argument.
                    try {
                        double area = calculateCircleArea(radius); // Call library function
                        cout << "Line " << lineNumber << ": Circle Area: " << area << endl;
                    }
                    catch (const std::invalid_argument& e) {
                        cerr << "Line " << lineNumber << ": Error - " << e.what() << endl;
                    }
                }
                else {
                    // STUDENT TODO: Replace this 'cerr' statement with a
                    // 'throw ParseException("Unknown shape type: " + shapeType, lineNumber);'
                    throw ParseException("Line " + to_string(lineNumber) + ": Unknown shape type: " + shapeType);
                }
            }
            catch (const ParseException& e) {
                cerr << e.what() << endl;
                // Continue to next line
            }
        }
    }
    catch (const ParseException& e) {
        // This catch block handles any ParseException thrown from outside the inner try block
        // (though with our structure, all ParseExceptions are caught internally)
        cerr << e.what() << endl;
    }
    // The catch block for ParseException should go here.
    // catch (const ParseException& e) { ... }

    // --- 3. Cleanup ---
    cout << "--- Processing Complete ---" << endl;
    file.close();

    return 0; // Successful execution
}