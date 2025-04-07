#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>

class Animal {
protected:
    std::string name;
    int age;
    std::string species;
    std::string birthSeason;
    std::string color;
    std::string gender;
    double weight;
    std::string origin;

public:
    // Constructor
    Animal(std::string n, int a, std::string s, std::string bSeason, std::string c, std::string g, double w, std::string o)
        : name(n), age(a), species(s), birthSeason(bSeason), color(c), gender(g), weight(w), origin(o) {}

    // Getters
    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getSpecies() const { return species; }
    std::string getBirthSeason() const { return birthSeason; }
    std::string getColor() const { return color; }
    std::string getGender() const { return gender; }
    double getWeight() const { return weight; }
    std::string getOrigin() const { return origin; }

    // Display all details
    virtual void display() const {
        std::cout << species << ": " << name << " (" << age << " years old)" << std::endl;
        std::cout << "Birth Season: " << birthSeason << ", Color: " << color << ", Gender: " << gender
                  << ", Weight: " << weight << " pounds" << std::endl;
        std::cout << "Origin: " << origin << std::endl;
    }
};

// Hyena class
class Hyena : public Animal {
public:
    Hyena(std::string n, int a, std::string bSeason, std::string c, std::string g, double w, std::string o)
        : Animal(n, a, "Hyena", bSeason, c, g, w, o) {}

    void display() const override {
        std::cout << "Hyena: " << name << " (" << age << " years old)" << std::endl;
        std::cout << "Birth Season: " << birthSeason << ", Color: " << color << ", Gender: " << gender
                  << ", Weight: " << weight << " pounds" << std::endl;
        std::cout << "Origin: " << origin << std::endl;
    }
};

// Lion class
class Lion : public Animal {
public:
    Lion(std::string n, int a, std::string bSeason, std::string c, std::string g, double w, std::string o)
        : Animal(n, a, "Lion", bSeason, c, g, w, o) {}

    void display() const override {
        std::cout << "Lion: " << name << " (" << age << " years old)" << std::endl;
        std::cout << "Birth Season: " << birthSeason << ", Color: " << color << ", Gender: " << gender
                  << ", Weight: " << weight << " pounds" << std::endl;
        std::cout << "Origin: " << origin << std::endl;
    }
};

// Tiger class
class Tiger : public Animal {
public:
    Tiger(std::string n, int a, std::string bSeason, std::string c, std::string g, double w, std::string o)
        : Animal(n, a, "Tiger", bSeason, c, g, w, o) {}

    void display() const override {
        std::cout << "Tiger: " << name << " (" << age << " years old)" << std::endl;
        std::cout << "Birth Season: " << birthSeason << ", Color: " << color << ", Gender: " << gender
                  << ", Weight: " << weight << " pounds" << std::endl;
        std::cout << "Origin: " << origin << std::endl;
    }
};

// Bear class
class Bear : public Animal {
public:
    Bear(std::string n, int a, std::string bSeason, std::string c, std::string g, double w, std::string o)
        : Animal(n, a, "Bear", bSeason, c, g, w, o) {}

    void display() const override {
        std::cout << "Bear: " << name << " (" << age << " years old)" << std::endl;
        std::cout << "Birth Season: " << birthSeason << ", Color: " << color << ", Gender: " << gender
                  << ", Weight: " << weight << " pounds" << std::endl;
        std::cout << "Origin: " << origin << std::endl;
    }
};

#endif // ANIMAL_H
