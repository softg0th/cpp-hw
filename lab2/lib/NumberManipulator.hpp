#include <vector>
#include <string>
#include <map>
#include "common.hpp"

class NumberManipulator {
    private:
        int number;
        std::vector<std::map<std::string, std::string>> history;
        std::string numToString;

        void updateMapHistory(int number, std::string numToString, std::string typeOfUpdate) {
            std::map<std::string, std::string> historyLine;
            historyLine["time"] = getCurrentTimeStamp();
            historyLine["number"] = std::to_string(number);
            historyLine["numToString"] = numToString;
            historyLine["typeOfUpdate"] = typeOfUpdate;
            this->history.push_back(historyLine);
        }
    public:
        NumberManipulator();
        NumberManipulator(int number, const std::string& numToString);
        NumberManipulator(const NumberManipulator &nm);
        NumberManipulator(NumberManipulator &&mm);

        NumberManipulator& operator=(const NumberManipulator& other);
        NumberManipulator& operator=(NumberManipulator&& other);

        ~NumberManipulator();

        void getHistory() const;
        std::vector<std::map<std::string, std::string>> getValueHistory();
};