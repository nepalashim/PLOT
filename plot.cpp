#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <plplot/plplot.h>

// Define a map to store sales distribution and volume data for each district
using DistrictData = std::map<std::string, std::pair<int, int>>;

// Function to read the dataset from a CSV file and populate the map
DistrictData readDataset(const std::string& filename) {
    DistrictData data;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ','); // District
        std::getline(ss, token, ','); // Customer Name
        std::getline(ss, token, ','); // Age
        std::getline(ss, token, ','); // Location
        int salesDistribution = std::stoi(token); // Sales Distribution
        std::getline(ss, token, ','); // Product Volume
        int productVolume = std::stoi(token);

        data[token] = std::make_pair(salesDistribution, productVolume);
    }

    return data;
}

// Function to create a scatter plot using plplot
void generateScatterPlot(const DistrictData& districtData) {
    plstream pls(1, 1, 0, 0);

    pls.sdev("pngcairo");
    pls.init();
    pls.adv(0);

    pls.lab("Sales Distribution (%)", "Product Volume", "Sales Distribution vs Product Volume");

    int n = districtData.size();
    PLFLT* x = new PLFLT[n];
    PLFLT* y = new PLFLT[n];

    int i = 0;
    for (const auto& entry : districtData) {
        x[i] = entry.second.first;
        y[i] = entry.second.second;
        i++;
    }

    pls.poin(n, x, y, 9);
    pls.ptex(x, y, 1, 0, 0.5, " ");

    delete[] x;
    delete[] y;

    pls.eop();
    pls.plend();
}

int main() {
    // Replace "geographical_data_nepal.csv" with the actual filename
    DistrictData districtData = readDataset("geographical_data_nepal.csv");

    // Create a scatter plot using plplot
    generateScatterPlot(districtData);

    return 0;
}
