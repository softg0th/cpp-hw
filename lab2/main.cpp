#include <iostream>
#include <list>
#include <memory>
#include <vector>

#include "lib/NumberManipulator.hpp"
#include "3rdparty/json.hpp"


void buildJson(std::vector<std::unique_ptr<NumberManipulator>>& instances) {
    nlohmann::json jInstances;

    for (const auto& instance : instances) {
        nlohmann::json j;
        j["history"] = instance->getValueHistory();
        jInstances.push_back(j);
    }
    std::cout << "Serialized JSON: " << jInstances.dump(4) << std::endl;
}
int main() {
    std::cout << "Static:" << std::endl;
    static NumberManipulator first{1, "odin"};
    first.getHistory();


    std::cout << "Dynamic:" << std::endl;
    std::unique_ptr<NumberManipulator> second = std::make_unique <NumberManipulator>();
    second->getHistory();

    std::cout << "Vector:" << std::endl;
    std::map<int, std::string> nums = {{10, "desyat"}, 
                                        {20, "dvadsat"}, 
                                        {30, "tridsat"}, 
                                        {40, "sorok"}, 
                                        {50, "pyatdesyat"}};
    std::vector<std::unique_ptr<NumberManipulator>> instances;

    for (int i = 0; i < 5; i++){
        std::unique_ptr<NumberManipulator> instance = std::make_unique<NumberManipulator>(i*2, nums[i]);
        instances.push_back(std::move(instance));
    }

    buildJson(instances);

    std::cout << "List:" << std::endl;

    std::list<NumberManipulator> instancesList;
    instancesList.emplace_back(3, "tri");
    instancesList.emplace_back(4, "chetyre");
    instancesList.emplace_back(5, "pyat");

    for (auto& ins : instancesList) {
        ins.getHistory();
    }

    return 0;
}
