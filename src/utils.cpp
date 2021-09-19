#include "utils.hpp"

void utils::printJSON(nlohmann::json json){
    if(json.is_object()){
        for(auto& el : json.items()){
            if (el.value().is_structured()) printJSON(el.value());
            else std::cout << el.key() << ":" << el.value() << std::endl;
        }
    }else {
        for(auto& el : json){
            if (el.is_structured()) printJSON(el);
            else std::cout << el << std::endl;
        }
    }
    
}
