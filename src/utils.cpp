#include "utils.hpp"

namespace utils{
    /** 
     * Concatenate json values with a comma separator
     * @param json_parse json to be parsed
     * @return parsed value
     */
    std::string concat (nlohmann::json json_parse){
        std::stringstream parsed;
        for (auto& el : json_parse){
            if (el.is_structured()){
                parsed << concat(el);
            } else {
                parsed << el << ",";
            }                
        }
        return parsed.str();

    }
    /**
     * Parse a json to a string in a fixed size
     * @param json_parse json to be parsed
     * @param maxsize sized to be delimitated
     */
    std::string parse (nlohmann::json json_parse, int maxsize){
        std::string response = concat(json_parse);
        response.pop_back();

        int position = 0;
        while ((position = response.find('"')) != std::string::npos){
            response.erase(position, 1);
        }
        
        if (response.size() > maxsize){
            response.resize(maxsize);
            int count = maxsize - 1;
            while (response[count] != ','){
                response[count] = SYMBOL;
                count--;
            }
            response[count] = SYMBOL;
        } else {
            for(int local = response.size() - 1; local < maxsize; local++){
                response.push_back(SYMBOL);
            }
        }

        return response;
    }
}