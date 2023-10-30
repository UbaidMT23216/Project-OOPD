#ifndef TELECOMCLASSES_HPP
#define TELECOMCLASSES_HPP

#include <iostream>
#include <string>

class MVNOSpectrumData {
public:
    string date;
    string MVNOCompany;
    string location;
    int request;

    // Display function (optional but can be useful for debugging)
    void display() {
        cout << date << " | " << MVNOCompany << " | " << location << " | " << request << endl;
    }
};

class SpectrumRange {
public:
    int index;
    string date;
    string company;
    string spectrumRange;

    void display() {
        cout << index << ". " << date << ", " << company << ", " << spectrumRange << endl;
    }
};

class SpectrumRequest {
public:
    int index;
    string date;
    string company;
    string location;
    string request;

    void display() {
        cout << index << ". " << date << ", " << company << ", " << location << ", " << request << endl;
    }
};

class Subscribers {
public:
    int index;
    string date;
    string company;
    string location;
    int subscribers;

    void display() {
        cout << index << ". " << date << ", " << company << ", " << location << ", " << subscribers << endl;
    }
};

class SpectrumData {
public:
    string date;
    string company;
    string spectralRange;
    string circle;
    int revenue;

    void display() {
        cout << date << ", " << company << ", " << circle << ", " << revenue << endl;
    }
};

class SubscriberData {
public:
    string date;
    string company;
    string location;
    int subscribers;

    void display() {
        cout << date << ", " << company << ", " << location << ", " << subscribers << endl;
    }
};

class SpectrumRequestData {
public:
    string date;
    string company;
    string location;
    int request;

    void display() {
        cout << date << ", " << company << ", " << location << ", " << request << endl;
    }
};

class UsageDensity {
public:
    string company;
    string location;
    double usageDensityValue;

    void display() {
        cout << company << ", " << location << ", " << usageDensityValue << endl;
    }
};

class MatchedEntry {
public:
    string company;
    string location;

    MatchedEntry() {}  // Default constructor

    MatchedEntry(string comp, string loc) 
        : company(comp), location(loc) {}  // Parameterized constructor

    // Check if this entry matches another entry
    bool matches(const SpectrumData& spectrumEntry) const {
        return (company == spectrumEntry.company) && (location == spectrumEntry.circle);
    }
};


#endif // TELECOMCLASSES_HPP