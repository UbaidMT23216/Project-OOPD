#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const int MAX_ENTRIES = 100;

// Define the SpectrumData class to store spectrum range data
class SpectrumData {
public:
    string date;
    string company;
    string spectralRange;
    string circle;
    int revenue;

    // Function to display spectrum range data
    void display() {
        cout << date << ", " << company << ", " << circle << ", " << revenue << endl;
    }
};

// Define the SubscriberData class to store subscriber data
class SubscriberData {
public:
    string date;
    string company;
    string location;
    int subscribers;

    // Function to display subscriber data
    void display() {
        cout << date << ", " << company << ", " << location << ", " << subscribers << endl;
    }
};

// Define the SpectrumRequestData class to store spectrum request data
class SpectrumRequestData {
public:
    string date;
    string company;
    string location;
    int request;

    // Function to display spectrum request data
    void display() {
        cout << date << ", " << company << ", " << location << ", " << request << endl;
    }
};

// Define the UsageDensity class to calculate and store usage density
class UsageDensity {
public:
    string company;
    string location;
    double usageDensityValue;

    // Function to display usage density
    void display() {
        cout << company << ", " << location << ", " << usageDensityValue << endl;
    }
};

// Define the MatchedEntry class to represent matched spectrum entries
class MatchedEntry {
public:
    string company;
    string location;

    // Default constructor
    MatchedEntry() {}

    // Parameterized constructor
    MatchedEntry(std::string comp, std::string loc) 
        : company(comp), location(loc) {}

    // Check if this entry matches a SpectrumData entry
    bool matches(const SpectrumData& spectrumEntry) const {
        return (company == spectrumEntry.company) && (location == spectrumEntry.circle);
    }
};

// Define the MVNOSpectrumData class to store MVNO spectrum data
class MVNOSpectrumData {
public:
    string date;
    string MVNOCompany;
    string location;
    int request;

    // Function to display MVNO spectrum data
    void display() {
        cout << date << " | " << MVNOCompany << " | " << location << " | " << request << endl;
    }
};

const int MAX_RECORDS = 1000;

// Function to ask the user for a custom threshold density
double askForThresholdDensity() {
    double threshold;
    cout << "Enter the threshold density (e.g., 0.05 for 0.05 MHz/Subscriber): ";
    cin >> threshold;
    return threshold;
}

// Function to load MVNO Spectrum Data from a file and populate the MVNOSpectrumData array
int loadMVNOSpectrumData(MVNOSpectrumData dataArray[]) {
    ifstream file("MVNOSpectrum.csv");
    string line;
    int index = 0;

    getline(file, line);

    while (getline(file, line) && index < MAX_RECORDS) {
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

int main() {
    MatchedEntry matchedEntries[100];  // Assuming max 100 matched entries
    int matchedCount = 0;
    SpectrumData spectrumData[MAX_ENTRIES];
    SubscriberData subscriberData[MAX_ENTRIES];
    SpectrumRequestData requestData[MAX_ENTRIES];
    int spectrumCount = 0, subscriberCount = 0, requestCount = 0;
    int choice;

    // Load Spectrum Data from CSV
    ifstream spectrumFile("spectrumRange.csv");
    if (!spectrumFile.is_open()) {
        cout << "Error: Couldn't open spectrum file." << endl;
        return 1;
    }

    string line;
    getline(spectrumFile, line); // Skipping header line

    while (getline(spectrumFile, line) && spectrumCount < MAX_ENTRIES) {
        stringstream ss(line);
        SpectrumData entry;
        string item;

        // Extract and assign values from the CSV
        getline(ss, item, ',');
        entry.date = item;

        getline(ss, item, ',');
        entry.company = item;

        getline(ss, item, ',');
        entry.spectralRange = item;

        getline(ss, item, ',');
        entry.circle = item;

        getline(ss, item, ',');
        entry.revenue = stoi(item);

        spectrumData[spectrumCount++] = entry;
    }

    spectrumFile.close();

    // Load Subscriber Data from CSV
    ifstream subscriberFile("subscribers.csv");
    if (!subscriberFile.is_open()) {
        cout << "Error: Couldn't open subscriber file." << endl;
        return 1;
    }

    getline(subscriberFile, line); // Skipping header line

    while (getline(subscriberFile, line) && subscriberCount < MAX_ENTRIES) {
        stringstream ss(line);
        SubscriberData entry;
        string item;

        // Extract and assign values from the CSV
        getline(ss, item, ',');
        entry.date = item;

        getline(ss, item, ',');
        entry.company = item;

        getline(ss, item, ',');
        entry.location = item;

        getline(ss, item, ',');
        entry.subscribers = stoi(item);

        subscriberData[subscriberCount++] = entry;
    }

    subscriberFile.close();

    MVNOSpectrumData mvnoData[MAX_RECORDS];
    int recordsRead = loadMVNOSpectrumData(mvnoData);

    ifstream requestFile("spectrumRequest.csv");
    if (!requestFile.is_open()) {
        cout << "Error: Couldn't open spectrum request file." << endl;
        return 1;
    }

    getline(requestFile, line); // Skipping header line

    while (getline(requestFile, line) && requestCount < MAX_ENTRIES) {
        stringstream ss(line);
        SpectrumRequestData entry;
        string item;

        // Extract and assign values from the CSV
        getline(ss, item, ',');
        entry.date = item;

        getline(ss, item, ',');
        entry.company = item;

        getline(ss, item, ',');
        entry.location = item;

        getline(ss, item, ',');
        entry.request = stoi(item);

        requestData[requestCount++] = entry;
    }

    requestFile.close();

    double thresholdDensity = askForThresholdDensity(); // Ask the user for the threshold density

    while (true) {
       cout << "Please select an option from the menu:" << endl;
       cout << "Please Enter 1.To Display Spectrum Range Data" << endl;
       cout << "Please Enter 2.To Display Subscriber Data" << endl;
       cout << "Please Enter 3.To Display Spectrum Request Data" << endl;
       cout << "Please Enter 4.To Calculate and Display Usage Density" << endl;
       cout << "Please Enter 5.To Show Companies with High Usage Density (> " << thresholdDensity << " MHz/Subscriber) Not Allowed in Auction" << endl;
       cout << "Please Enter 6.To Display Spectrum Allocated to Companies with Appropriate Usage Density" << endl;
       cout << "Please Enter 7.To Display Revenue Data for Allocated Spectrum and Save it to 'SavedAllocatedDatawithRevenues.csv'" << endl;
       cout << "Please Enter 8.To Display MVNO Spectrum Data" << endl;
       cout << "Please Enter 9.To Exit Program" << endl;

        cin >> choice;

        if (choice == 1) {
            for (int i = 0; i < spectrumCount; i++) {
                spectrumData[i].display();
            }
        } else if (choice == 2) {
            for (int i = 0; i < subscriberCount; i++) {
                subscriberData[i].display();
            }
        } else if (choice == 3) {
            for (int i = 0; i < requestCount; i++) {
                requestData[i].display();
            }
        } else if (choice == 4) {
            for (int i = 0; i < requestCount; i++) {
                int totalRequests = 0;
                int totalSubscribers = 0;

                for (int j = 0; j < requestCount; j++) {
                    if (requestData[i].company == requestData[j].company && 
                        requestData[i].location == requestData[j].location) {
                        totalRequests += requestData[j].request;
                    }
                }

                for (int k = 0; k < subscriberCount; k++) {
                    if (requestData[i].company == subscriberData[k].company && 
                        requestData[i].location == subscriberData[k].location) {
                        totalSubscribers += subscriberData[k].subscribers;
                    }
                }

                if (totalSubscribers != 0) {
                    UsageDensity density;
                    density.company = requestData[i].company;
                    density.location = requestData[i].location;
                    density.usageDensityValue = static_cast<double>(totalRequests) / totalSubscribers;

                    bool alreadyDisplayed = false;
                    for (int l = 0; l < i; l++) {
                        if (requestData[i].company == requestData[l].company && 
                            requestData[i].location == requestData[l].location) {
                            alreadyDisplayed = true;
                            break;
                        }
                    }

                    if (!alreadyDisplayed) {
                        density.display();
                    }
                }
            }
        } else if (choice == 5) {
            cout << "Companies with usage density > " << thresholdDensity << " MHz/Subscriber are:" << endl;
            for (int i = 0; i < requestCount; i++) {
                int totalRequests = 0;
                int totalSubscribers = 0;

                for (int j = 0; j < requestCount; j++) {
                    if (requestData[i].company == requestData[j].company && 
                        requestData[i].location == requestData[j].location) {
                        totalRequests += requestData[j].request;
                    }
                }

                for (int k = 0; k < subscriberCount; k++) {
                    if (requestData[i].company == subscriberData[k].company && 
                        requestData[i].location == subscriberData[k].location) {
                        totalSubscribers += subscriberData[k].subscribers;
                    }
                }

                if (totalSubscribers != 0) {
                    double usageDensityValue = static_cast<double>(totalRequests) / totalSubscribers;

                    bool alreadyDisplayed = false;
                    for (int l = 0; l < i; l++) {
                        if (requestData[i].company == requestData[l].company && 
                            requestData[i].location == requestData[l].location) {
                            alreadyDisplayed = true;
                            break;
                        }
                    }

                    if (!alreadyDisplayed && usageDensityValue > thresholdDensity) {
                        cout << "Company: " << requestData[i].company << ", Location: " << requestData[i].location << ", Usage Density: " << usageDensityValue << endl;
                    }
                }
            }
        } else if (choice == 6) {
            cout << "Companies with usage density < " << thresholdDensity << " MHz/Subscriber are:" << endl;
            for (int i = 0; i < requestCount; i++) {
                int totalRequests = 0;
                int totalSubscribers = 0;

                for (int j = 0; j < requestCount; j++) {
                    if (requestData[i].company == requestData[j].company && 
                        requestData[i].location == requestData[j].location) {
                        totalRequests += requestData[j].request;
                    }
                }

                for (int k = 0; k < subscriberCount; k++) {
                    if (requestData[i].company == subscriberData[k].company && 
                        requestData[i].location == subscriberData[k].location) {
                        totalSubscribers += subscriberData[k].subscribers;
                    }
                }

                if (totalSubscribers != 0) {
                    double usageDensityValue = static_cast<double>(totalRequests) / totalSubscribers;

                    bool alreadyDisplayed = false;
                    for (int l = 0; l < i; l++) {
                        if (requestData[i].company == requestData[l].company && 
                            requestData[i].location == requestData[l].location) {
                            alreadyDisplayed = true;
                            break;
                        }
                    }

                    if (!alreadyDisplayed && usageDensityValue < thresholdDensity) {
                        matchedEntries[matchedCount++] = MatchedEntry(requestData[i].company, requestData[i].location);
                        cout << "Company: " << requestData[i].company << ", Location: " << requestData[i].location << ", Usage Density: " << usageDensityValue << endl;
                    }
                }
            }
        } else if (choice == 7) {
            ofstream outputFile("AllocationReport.csv");

            outputFile << "Date,Company,Spectrum Circle,Revenue\n";

            for (int i = 0; i < matchedCount; ++i) {
                for (const auto& spectrumEntry : spectrumData) {
                    if (matchedEntries[i].matches(spectrumEntry)) {
                        cout << "Date: " << spectrumEntry.date << ", Company: " << spectrumEntry.company 
                            << ", Spectrum Circle: " << spectrumEntry.circle
                            << ", Revenue: (in Crores) " << spectrumEntry.revenue << endl;

                        outputFile << spectrumEntry.date << ","
                            << spectrumEntry.company << ","
                            << spectrumEntry.circle << ","
                            << spectrumEntry.revenue << "\n";
                    }
                }
            }

            outputFile.close();
            cout << "Data has been saved to AllocationReport.csv" << endl;
        } else if (choice == 8) {
            cout << "MVNO Spectrum Data" << endl;
            for (int i = 0; i < recordsRead; i++) {
                mvnoData[i].display();
            }
        } else if (choice == 9) {
            cout << "Exiting program..." << endl;
            return 0;
        } else {
            cout << "Invalid choice. Please select again." << endl;
        }
    }

    return 0;
}
