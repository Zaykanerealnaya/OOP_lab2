#ifndef OOPPROG2_DETAIL_H
#define OOPPROG2_DETAIL_H

#include <iostream>
#include <string>
#include <limits>
#include <cstring>

class Detail{

public:

    enum class Type {
        INITIAL = 1,
        INTERMEDIATE = 2,
        FINAL = 3
    };

private:

    std::string name = "initial";
    Type type = Type::INITIAL;
    int otherDetails[4] {};
    int count_otherDetails = 0;
    std::string assemblyInfo;

public:

    struct Uniq_Detail{
        int index;
        int count;
    };

    struct Uniq{
        size_t count_elements;
        Uniq_Detail *detail;
    };

    friend void output(const Detail&);

     ~Detail(){
        name.clear();
        if(!(assemblyInfo.empty())){
            assemblyInfo.clear();
        }
    }

    explicit Detail(std::string name) : name(std::move(name)) {
    }

    Detail(std::string name, Type type, const int* otherDetails, int count_otherDetails, std::string assemblyInfo) :
            name(std::move(name)), type(type), count_otherDetails(count_otherDetails), assemblyInfo(std::move(assemblyInfo)){
        if(count_otherDetails > 4 || count_otherDetails < 0)
            throw std::out_of_range("wrong size of input!");
        std::copy(otherDetails,otherDetails + count_otherDetails, this->otherDetails);
    }

    [[nodiscard]] std::string getName() const {
        return name;
    }

    [[nodiscard]] Type getType() const {
        return type;
    }

    [[nodiscard]] const int* getOtherDetails() const {
        return otherDetails;
    }

    [[nodiscard]] int getCountOther() const {
        return count_otherDetails;
    }

    [[nodiscard]] const std::string& getAssemblyInstructions() const {
        return assemblyInfo;
    }

    // Методы изменения значений атрибутов класса (сеттеры)

    Detail &setType(Type newType){
        type = newType;
        return *this;
    }

    Detail &setOtherDetails(int* newOtherDetails, int count) {
        if(count_otherDetails > 4 || count_otherDetails < 0){ throw std::out_of_range("wrong size of input!");}
        count_otherDetails = count;
        std::copy(newOtherDetails,newOtherDetails + count, otherDetails);
        return *this;
    }

    Detail &setAssemblyInstructions(std::string newAssemblyInfo) {
        assemblyInfo = std::move(newAssemblyInfo);
        return *this;
    }


    void add_otherDetails(int partNumber);

    Uniq getUniq();

    std::strong_ordering operator <=>(const Detail &det1);

    [[nodiscard]] int find_max() const{
        int max = 0;
        for(int i = 0 ; i < getCountOther();i++){
            max = std::max(max,getOtherDetails()[i]);
        }
        return  max;
    }

};


template<class T>
T* realloc(T* a, size_t new_count, size_t prev_count){
    T *array = new T[new_count];
    if(new_count > prev_count){
        std::copy(a,a + prev_count,array);
    }
    else{
        std::copy(a,a + new_count,array);
    }
    delete[] a;
    return array;
}


#endif