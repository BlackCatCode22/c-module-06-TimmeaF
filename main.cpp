#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <filesystem>
#include "animal.h"
#include <regex>

using namespace std;

// Function to read names from a file and categorize them by species
void readNamesFromFile(const string& filename, vector<string>& hyenaNames, vector<string>& lionNames, vector<string>& bearNames, vector<string>& tigerNames) {
    ifstream file(filename);
    string line;
    string currentSpecies;

    if (!file) {
        cerr << "Error: Could not open " << filename << " for reading" << endl;
        return;
    }

    while (getline(file, line)) {
        // Skip empty lines or lines that are just headings
        if (line.empty() || line.find("Names:") != string::npos) {
            // Set the current species based on the heading
            if (line.find("Hyena Names") != string::npos) {
                currentSpecies = "Hyena";
            } else if (line.find("Lion Names") != string::npos) {
                currentSpecies = "Lion";
            } else if (line.find("Bear Names") != string::npos) {
                currentSpecies = "Bear";
            } else if (line.find("Tiger Names") != string::npos) {
                currentSpecies = "Tiger";
            }
        } else {
            // Remove any leading or trailing whitespace
            line = line.substr(0, line.find_last_not_of(" \n\r\t") + 1);

            // Add the name to the correct species vector
            if (currentSpecies == "Hyena") {
                hyenaNames.push_back(line);
            } else if (currentSpecies == "Lion") {
                lionNames.push_back(line);
            } else if (currentSpecies == "Bear") {
                bearNames.push_back(line);
            } else if (currentSpecies == "Tiger") {
                tigerNames.push_back(line);
            }
        }
    }

    file.close();
}

// Function to read and parse data from a file
void readAnimalsFromFile(const string& filename, vector<Animal*>& animals,
                         vector<string>& hyenaNames, vector<string>& lionNames,
                         vector<string>& bearNames, vector<string>& tigerNames) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Could not open " << filename << " for reading" << endl;
        return;
    }

    int hyenaIndex = 0, lionIndex = 0, bearIndex = 0, tigerIndex = 0;
    string line;

    random_device rd;  // For true randomness
    mt19937 gen(rd()); // Standard mersenne_twister_engine
    uniform_int_distribution<> dis(0, 9);  // Random index generator

    while (getline(inFile, line)) {
        cout << "Reading line: " << line << endl;

        string name, species, birthSeason, color, gender, origin;
        int age;
        double weight;

        // Adjusted regex pattern
        regex rgx("(\\d+) year old (\\w+) (hyena|lion|bear|tiger), born in (spring|summer|fall|winter|unknown), ([A-Za-z]+(?: [A-Za-z]+)*) color, (\\d+) pounds, from (.+)");
        smatch matches;

        if (regex_search(line, matches, rgx)) {
            species = matches[3];
            cout << "Extracted species: " << species << endl;

            // Randomly assign names from the lists based on species
            if (species == "hyena") {
                if (!hyenaNames.empty()) {
                    int idx = dis(gen) % hyenaNames.size();  // Generate random index for hyenas
                    name = hyenaNames[idx];
                    hyenaNames.erase(hyenaNames.begin() + idx);  // Remove assigned name
                } else {
                    name = "Unnamed";
                }
            } else if (species == "lion") {
                if (!lionNames.empty()) {
                    int idx = dis(gen) % lionNames.size();  // Generate random index for lions
                    name = lionNames[idx];
                    lionNames.erase(lionNames.begin() + idx);  // Remove assigned name
                } else {
                    name = "Unnamed";
                }
            } else if (species == "bear") {
                if (!bearNames.empty()) {
                    int idx = dis(gen) % bearNames.size();  // Generate random index for bears
                    name = bearNames[idx];
                    bearNames.erase(bearNames.begin() + idx);  // Remove assigned name
                } else {
                    name = "Unnamed";
                }
            } else if (species == "tiger") {
                if (!tigerNames.empty()) {
                    int idx = dis(gen) % tigerNames.size();  // Generate random index for tigers
                    name = tigerNames[idx];
                    tigerNames.erase(tigerNames.begin() + idx);  // Remove assigned name
                } else {
                    name = "Unnamed";
                }
            }

            // Extract other data
            age = stoi(matches[1]);
            gender = matches[2];
            birthSeason = matches[4];
            color = matches[5];
            weight = stod(matches[6]);
            origin = matches[7];

            // Create animal objects and add them to the vector
            if (species == "hyena") {
                animals.push_back(new Hyena(name, age, birthSeason, color, gender, weight, origin));
            } else if (species == "lion") {
                animals.push_back(new Lion(name, age, birthSeason, color, gender, weight, origin));
            } else if (species == "tiger") {
                animals.push_back(new Tiger(name, age, birthSeason, color, gender, weight, origin));
            } else if (species == "bear") {
                animals.push_back(new Bear(name, age, birthSeason, color, gender, weight, origin));
            } else {
                cout << "Unknown species: " << species << endl;
            }
        } else {
            cout << "Regex did not match for line: " << line << endl;
        }
    }

    inFile.close();
}

// Function to generate the report for all animals and write it to a new file
void generateReportToFile(const vector<Animal*>& animals, const string& outputFilename) {
    ofstream outFile(outputFilename);

    if (!outFile) {
        cerr << "Error: Could not open " << outputFilename << " for writing" << endl;
        return;
    }

    for (const auto& animal : animals) {
        // Writing animal information to the file
        outFile << "Name: " << animal->getName() << endl;
        outFile << "Species: " << animal->getSpecies() << endl;
        outFile << "Age: " << animal->getAge() << endl;
        outFile << "Birth Season: " << animal->getBirthSeason() << endl;
        outFile << "Color: " << animal->getColor() << endl;
        outFile << "Gender: " << animal->getGender() << endl;
        outFile << "Weight: " << animal->getWeight() << " pounds" << endl;
        outFile << "Origin: " << animal->getOrigin() << endl;
        outFile << "-----------------------------" << endl;
    }

    outFile.close();
}

int main() {
    vector<Animal*> animals;

    // Create containers for animal names by species
    vector<string> hyenaNames, lionNames, bearNames, tigerNames;

    // Read animal names from file and categorize them by species
    readNamesFromFile("C:/Users/NCG/CLionProjects/zoo/cmake-build-debug/animalNames.txt", hyenaNames, lionNames, bearNames, tigerNames);

    // Read animals from file and assign names from the lists
    readAnimalsFromFile("C:/Users/NCG/CLionProjects/zoo/cmake-build-debug/arrivingAnimals.txt", animals, hyenaNames, lionNames, bearNames, tigerNames);

    // Generate the report and write it to newAnimals.txt
    generateReportToFile(animals, "C:/Users/NCG/CLionProjects/zoo/cmake-build-debug/newAnimals.txt");

    // Clean up dynamically allocated memory
    for (auto* animal : animals) {
        delete animal;
    }

    return 0;
}
