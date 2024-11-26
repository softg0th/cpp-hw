#include <vector>
#include <string>
#include <map>

class NumberManipulator {
    private:
        int number;
        std::vector<std::map<std::string, std::string>> history;
        std::string numToString;
    public:
        NumberManipulator();
        NumberManipulator(int number, std::string& numToString);
        NumberManipulator(const NumberManipulator &nm);
        NumberManipulator(NumberManipulator &&mm);
        
        ~NumberManipulator();
};