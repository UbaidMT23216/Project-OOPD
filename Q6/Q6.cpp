#include <iostream>
#include <fstream>
#include <sstream>
#include "TRAI_Classes.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;

SpectrumRange rangeData[100];
SpectrumRequest requestData[100];
Subscribers subscribersData[100];

const int REQUEST_MAX_RECORDS = 1000;
int subscribersIndex = 0;
int rangeIndex = 0;
int requestIndex = 0;
int usageDataIndex = 0;
string highUsageDensityCompanies;
const int MAX_RECORDS = 1000;

// Class to store data related to usage density
class UsageDensityData {
public:
    int index;
    string company;
    string location;
    double usageDensity;

    // Function to generate a hash code based on company and location
    int generateHashCode() const {
        int hashValue = 0;
        for (char ch : company) {
            hashValue += ch;
        }
        for (char ch : location) {
            hashValue += ch;
        }
        return hashValue % 10000;  // To limit the value
    }

    // Function to display the data
    void display() {
        cout << index << ". " << company << ", " << location << ", " << usageDensity << ", Hashcode: #" << generateHashCode() << endl;
    }
};

UsageDensityData usageData[100];

// Class to store request data
class RequestDataClass {
public:
    string date;
    string mvnoCompany;
    string location;
    int request;
    double usageDensity;

    // Function to generate a hash code based on company and location
    int generateHashCode() const {
        int hashValue = 0;
        for (char ch : mvnoCompany) {
            hashValue += ch;
        }
        for (char ch : location) {
            hashValue += ch;
        }
        return hashValue % 10000;  // To limit the value
    }

    // Function to display the data
    void display() const {
        cout << "Date: " << date
            << ", Company: " << mvnoCompany
            << ", Location: " << location
            << ", Request: " << request
            << ", Hashcode: #" << generateHashCode()
            << ", Usage Density: " << usageDensity << endl;
    }
};

// Function to load request data from a file
int loadRequestDataFromFile(RequestDataClass requestDataArray[]) {
    ifstream file("MVNOSpectrum.csv");
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 0;
    }

    string line;
    int index = 0;

    // Skipping header
    getline(file, line);

    while (getline(file, line) && index < REQUEST_MAX_RECORDS) {
        stringstream ss(line);
        string temp;

        getline(ss, requestDataArray[index].date, ',');
        getline(ss, requestDataArray[index].mvnoCompany, ',');
        getline(ss, requestDataArray[index].location, ',');
        getline(ss, temp, ',');
        requestDataArray[index].request = stoi(temp);

        // Calculating and storing the usage density
        requestDataArray[index].usageDensity = static_cast<double>(requestDataArray[index].request) / 8000.0;

        index++;
    }

    file.close();
    return index;
}

// Function to load MVNO Spectrum data from a file
int loadMVNOSpectrumData(MVNOSpectrumData dataArray[]) {
    ifstream file("MVNOSpectrum.csv");
    string line;
    int index = 0;

    // Skip the header line
    getline(file, line);

    while (getline(file, line) && index < MAX_RECORDS) {
        // Using stringstream for parsing CSV
        stringstream ss(line);
        string item;

        getline(ss, dataArray[index].date, ',');
        getline(ss, dataArray[index].MVNOCompany, ',');
        getline(ss, dataArray[index].location, ',');
        getline(ss, item, ',');
        dataArray[index].request = stoi(item);

        index++;
    }

    return index;  // Return the number of records read
}

// Function to write data to a new CSV file
void writeDataToNewCSV(SpectrumRange rangeData[], int dataSize) {
    ofstream outFile("newData.csv");

    // Writing the column headers
    outFile << "date,Company,SpectrumRange,Revenue(crores)\n";

    double totalRevenue = 0;

    for (int i = 0; i < dataSize; i++) {
        int spectrum = stoi(rangeData[i].spectrumRange); // Convert string to integer
        double revenue = spectrum * 15; // Calculate revenue
        totalRevenue += revenue;

        outFile << rangeData[i].date << ","
            << rangeData[i].company << ","
            << rangeData[i].spectrumRange << ","
            << revenue << "\n";  // No "Crores" term appended to the value
    }

    outFile << ",,Total Revenue," << totalRevenue << "\n"; // Displaying total revenue at the end
    outFile.close();
}

// Function to display usage density data
void displayUsageDensityData(UsageDensityData usageData[], int dataSize) {
    for (int i = 0; i < dataSize; i++) {
        usageData[i].display();
    }
}

// Function to get the spectrum requested by a company and location
int getSpectrumRequested(const string &company, const string &circle) {
    for (int i = 0; i < 100; i++) {  // Assuming there's a maximum of 100 entries
        if (requestData[i].company == company && requestData[i].location == circle) {
            return stoi(requestData[i].request);  // Assuming request is stored as a string and converting it to integer
        }
    }
    return -1;  // Return -1 if not found
}

// Function to get the number of subscribers for a company and location
int getSubscribersCount(const string &company, const string &circle) {
    for (int i = 0; i < 100; i++) {  // Assuming there's a maximum of 100 entries
        if (subscribersData[i].company == company && subscribersData[i].location == circle) {
            return subscribersData[i].subscribers;
        }
    }
    return -1;  // Return -1 if not found
}

// Function to compute usage density for a company and location
double computeUsageDensity(const string &company, const string &circle) {
    int spectrum = getSpectrumRequested(company, circle);
    int subscribers = getSubscribersCount(company, circle);

    if (spectrum == -1 || subscribers == 0) {
        return -1.0; // Invalid data or to avoid division by zero
    }

    return static_cast<double>(spectrum) / static_cast<double>(subscribers);
}

// Function to populate usage density data
void populateUsageDensityData(UsageDensityData usageData[], int &dataIndex) {
    for (int i = 0; i < requestIndex; i++) {
        double density = computeUsageDensity(requestData[i].company, requestData[i].location);
        if (density != -1.0) {  // If valid data
            usageData[dataIndex].index = dataIndex + 1;
            usageData[dataIndex].company = requestData[i].company;
            usageData[dataIndex].location = requestData[i].location;
            usageData[dataIndex].usageDensity = density;
            dataIndex++;
        }
    }
}

// Function to identify companies with high usage density
string identifyHighUsageDensityCompanies(UsageDensityData usageData[], int dataSize) {
    string result;

    for (int i = 0; i < dataSize; i++) {
        if (usageData[i].usageDensity > 0.1) {
            result += "Company: " + usageData[i].company
                + ", Location: " + usageData[i].location
                + ", Usage Density: " + to_string(usageData[i].usageDensity) + "\n";
        }
    }
    return result;
}

int main() {
    // Create arrays to store data
    int i = 0;
    RequestDataClass requestDataArray[REQUEST_MAX_RECORDS];
    int totalRecords = loadRequestDataFromFile(requestDataArray);
    // Read SpectrumRange.csv
    ifstream rangeFile("spectrumRange.csv");
    string line;
    if (rangeFile.is_open()) {
        getline(rangeFile, line); // skip the header
        while (getline(rangeFile, line)) {
            stringstream ss(line);
            getline(ss, rangeData[rangeIndex].date, ',');
            getline(ss, rangeData[rangeIndex].company, ',');
            getline(ss, rangeData[rangeIndex].spectrumRange, ',');
            rangeData[rangeIndex].index = rangeIndex + 1;

            rangeIndex++;
        }
        rangeFile.close();
    }

    MVNOSpectrumData mvnoData[MAX_RECORDS];
    int recordsRead = loadMVNOSpectrumData(mvnoData);

    // Display the data (optional)

    // Read SpectrumRequest.csv
    ifstream requestFile("spectrumRequest.csv");
    if (requestFile.is_open()) {
        getline(requestFile, line); // skip the header
        while (getline(requestFile, line)) {
            stringstream ss(line);
            getline(ss, requestData[requestIndex].date, ',');
            getline(ss, requestData[requestIndex].company, ',');
            getline(ss, requestData[requestIndex].location, ',');
            getline(ss, requestData[requestIndex].request, ',');
            requestData[requestIndex].index = requestIndex + 1;

            requestIndex++;
        }
        requestFile.close();
    }

    ifstream subscribersFile("subscribers.csv");

    if (subscribersFile.is_open()) {
        getline(subscribersFile, line); // skip the header
        while (getline(subscribersFile, line)) {
            stringstream ss(line);
            getline(ss, subscribersData[subscribersIndex].date, ',');
            getline(ss, subscribersData[subscribersIndex].company, ',');
            getline(ss, subscribersData[subscribersIndex].location, ',');
            ss >> subscribersData[subscribersIndex].subscribers;
            subscribersData[subscribersIndex].index = subscribersIndex + 1;

            subscribersIndex++;
        }
        subscribersFile.close();
    }
    // Now the data is stored in rangeData and requestData arrays
    // You can access it and perform further operations

    populateUsageDensityData(usageData, usageDataIndex);
    // Example: Display the data
    while (true) {
        cout << "Main Menu(Select your choices to see the Results you want):\n";
        cout << "Please Enter 1 to See all spectrum Requested data by Companies with usage density and hashcodes\n";
        cout << "Please Enter 2 to See all MVNO spectrum Requested data with usage density and hashcodes \n";
        cout << "Please Enter 3 to See the ALLOWED spectrum Requested Companies\n";
        cout << "Please Enter 4 to See the ALLOWED MVNO Requested Spectrum data \n";
        cout << "Please Enter 5 to Exit ";
        cout << "Please Enter your choices:\n ";

        int choice;
        cin >> choice;
        highUsageDensityCompanies = identifyHighUsageDensityCompanies(usageData, usageDataIndex);

        if (choice == 1) {
            cout << "\nAll Spectrum Requested Data by Companies with usage density and hashcodes\n";
            displayUsageDensityData(usageData, usageDataIndex);
        }
        else if (choice == 2) {
            cout << "\nAll MVNO spectrum Requested data with usage density and hashcodes\n";
            for (int i = 0; i < totalRecords; i++) {
                requestDataArray[i].display();
            }
        }
        else if (choice == 3) {
            cout << "\nAllowed Spectrum Requested by Companies (Hash Codes Matched) and allowed only less than 0.11 MHz freq/subscriber \n";
            for (int i = 0; i < requestIndex; i = i + 2) {
                if (usageData[i].usageDensity < 0.11) {
                    usageData[i].display();
                }
            }
        }
        else if (choice == 4) {
            cout << "Allowed MVNO Requested by Companies (Hash Codes Matched) and allowed only less than 0.3 MHz freq/subscriber\n";
            for (int i = 0; i < totalRecords; i = i + 2) {
                if (requestDataArray[i].usageDensity < 0.3)
                    requestDataArray[i].display();
            }
        }
        else if (choice == 5) {
            cout << "Exiting Program\n";
            return 0;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
