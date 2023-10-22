#include "light_class.h"


std::string enum_int_to_str(Detail::Type a) {
    switch (a) {
        case (Detail::Type::INITIAL) :
            return "initial";
        case (Detail::Type::INTERMEDIATE) :
            return "intermediate";
        case (Detail::Type::FINAL) :
            return "final";
    }
}

void Detail::add_otherDetails(int partNumber){
    if(type==Type::INITIAL) throw std::invalid_argument("can't add to this detail!");
    if(count_otherDetails == 4) throw std::out_of_range("There no space!");
    otherDetails[count_otherDetails] = partNumber;
    count_otherDetails++;
}

Detail::Uniq Detail::   getUniq(){
    Uniq uniq_details{};
    auto* uniq_vector = new Uniq_Detail[4];
    uniq_details.count_elements = 0;
    for(int i = 0; i < count_otherDetails; i ++){
        int index = -1;
        for(int j = 0; j < uniq_details.count_elements;j++){
            if(otherDetails[i] == uniq_vector[j].index){
                index = j;
            }
        }
        if(index != -1){
            uniq_vector[index].count++;
        }
        else{
            uniq_vector[uniq_details.count_elements].index = otherDetails[i];
            uniq_vector[uniq_details.count_elements].count = 1;
            uniq_details.count_elements++;
        }
    }
    uniq_vector = realloc(uniq_vector,uniq_details.count_elements, 4);
    uniq_details.detail = uniq_vector;
    return  uniq_details;
}

    std::strong_ordering Detail::operator <=>(const Detail &det1) {
        return name <=> det1.name;
    }

void output(const Detail& det) {
    std::cout << "Name: " << det.name << std::endl;
    std::cout << "Type: " << enum_int_to_str(det.type)<< std::endl;
    std::cout << "Other Details: ";
    for (int i = 0; i < det.count_otherDetails; i++) {
        std::cout << det.otherDetails[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Assembly Instructions: " << det.assemblyInfo << std::endl;
}





