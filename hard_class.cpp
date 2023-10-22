#include "light_class.h"
#include "hard_class.h"
//допущения
//1) в векторе нет лишних деталей
//2) 2 детали не указывают на одно и то же место
//3) В вектор не заносятся дети после родителей

void AssemblyInstruction::input_detail(const Detail& detail) {

    for(int i = 0; i < detail.getCountOther();i++){
        if(busy_[detail.getOtherDetails()[i]]){
            throw std::invalid_argument("Can't add it to instruction");
        }
    }

    for(int i = 0; i < detail.getCountOther();i++){
        if(count_ - 1 < detail.getOtherDetails()[i]){
            throw std::invalid_argument("Can't add it to instruction");
        }
    }

    if(int(count_) == int(capacity)){
        if(capacity == 0) {
            details_ = new Detail*[1];
            busy_ = new bool[1];
            busy_[0] = false;
            capacity = 1;
        }
        else {
            Detail** temp = new Detail*[2*capacity];
            std::copy(details_,details_ + count_,temp);
            busy_ = realloc(busy_, 2 * capacity, capacity);
            for(size_t i = capacity - 1; i < 2*capacity - 1; i++){
                busy_[i] = false;
            }
            capacity = 2 * capacity;
            delete[] details_;
            details_ = temp;
        }
    }

    int index = 0;

    switch (detail.getType()){

        case(Detail::Type::INITIAL):

            while( ( index < light_details ) && ( detail.getName() > ((details_)[index])->getName() )){
                index++;
            }
            for(size_t i = count_ ; i > index;i--){
                (details_)[i] = (details_)[i-1];
            }
            (details_)[index] = new Detail(detail);
            light_details++;
            break;

        case(Detail::Type::INTERMEDIATE):
            index = int (count_ - 1);
            if(final_ != -1) index --;
            for(int i = 0; i < detail.getCountOther();i++){
                busy_[detail.getOtherDetails()[i]] = true;
            }
            while( (index > light_details - 1) && (detail.find_max() < details_[index]->find_max())){
                index--;
            }
            index++;
            for(size_t i = count_; i > index; i --){
                details_[i] = details_[i-1];
            }
            details_[index] = new Detail(detail);
            break;

        case(Detail::Type::FINAL):
            if(final_ == -1){
                for(int i = 0; i < detail.getCountOther();i++){
                    busy_[detail.getOtherDetails()[i]] = true;
                }
                details_[count_] = new Detail(detail);
                final_ = int(count_);
            }
            else throw std::invalid_argument("2 final details!");
            break;
    }
    count_++;
}

AssemblyInstruction::AssemblyInstruction(const Detail* detail,
                                         const size_t count_det) {
    try {
        for (int i = 0; i < count_det; i++) {
            input_detail(detail[i]);
        }
    }
    catch(...){
        delete[] details_;
        capacity = 0;
        count_ = 0;
        light_details = 0;
        final_ = -1;
    }
}

AssemblyInstruction::AssemblyInstruction(AssemblyInstruction&& other) noexcept:
                    details_(other.details_), count_(other.count_), capacity(other.capacity),
                    light_details(other.light_details), final_(other.final_) {
    other.details_ = nullptr;
    other.count_ = 0;
    other.capacity = 0;
    other.light_details = 0;
    other.final_ = 0;
}

AssemblyInstruction::AssemblyInstruction(const Detail& detail) {
    input_detail(detail);
}

AssemblyInstruction::AssemblyInstruction(const AssemblyInstruction& other){
    for(size_t i =0; i < other.count_; i++){
        input_detail(*(other.details_[i]));
    }
}

AssemblyInstruction& AssemblyInstruction::operator+=(const Detail& detail) {//rvalue
    input_detail(detail);
    return *this;
}

Detail& AssemblyInstruction::operator[](size_t index) {//const+ not const
    if(index >= count_) throw std::out_of_range("There no element!");
    return *(details_)[index];
}

const Detail& AssemblyInstruction::operator[](size_t index) const {
    if(index >= count_) throw std::out_of_range("There no element!");
    return *((details_)[index]);
}


void AssemblyInstruction::delete_detail(size_t index) {// delete
    if(index >= count_) throw std::out_of_range("There no element!");

    for(size_t i = index ; i < count_; i++){
        for(int j = 0; j < (*((details_)[i])).getCountOther();j++){
            if((*((details_)[i])).getOtherDetails()[j] == index){
                throw std::invalid_argument("Sorry, can't delete this detail!");
            }
        }
    }
    count_--;
    if(index == count_){
        delete ((details_)[index]);
        return;
    }
    delete ((details_)[index]);
    for (int i = int(index); i < count_; i++) {
        details_[i] = details_[i+1];
        busy_[i] = busy_[i+1];
    }
    delete ((details_)[count_]);
}

void AssemblyInstruction::check_recur(int *busy_v, int index,const Detail& detail){
    if(busy_v[index] == 1) throw std::runtime_error("Index was earlier");
    else busy_v[index] = 1;
    for(int i =0; i < detail.getCountOther();i++){
        check_recur(busy_v,detail.getOtherDetails()[i],*(details_[detail.getOtherDetails()[i]]));
    }
}

void AssemblyInstruction::check_final_detail(){
    try{
        int busy[count_];
        if(final_==-1) throw std::runtime_error("There no final detail");
        check_recur(busy,final_,*(details_[final_]));
        std::cout <<"Can make final detail" << std::endl;
        return;
    }
    catch(std::exception &e){
        std::cout << "Error is " << e.what();
    }
}

std::string AssemblyInstruction::get_initial_name() const {
    std::string names;
    for (size_t i = 0; i < light_details; i++) {
         names += (*((details_)[i])).getName() + '\n';
    }
    return names;
}

Detail** AssemblyInstruction::get_ordered_details() const {
    auto** order = new Detail*[count_];
    std::copy(details_,details_+count_,order);
    return order;
}

std::string AssemblyInstruction::instruction() const {
    std::string instruction;

    for(int i = int(count_) - 1; i > -1; i--){
        instruction+=  std::to_string(count_ - i) + ')'
                + details_[i]->getName()
                +' ' ;
        if((*((details_)[i])).getCountOther()!= 0){
            instruction += '(';
            for(int j =0; j < ((details_)[i])->getCountOther();j++) {
                instruction += std::to_string(count_ - (*((details_))[i]).getOtherDetails()[j]);
                if (j == ((details_)[i])->getCountOther() - 1) {
                    instruction += ')';
                } else {
                    instruction += ',';
                }
            }
            if(!((*((details_)[i])).getAssemblyInstructions().empty())){
                instruction+= " guide: " + (*((details_)[i])).getAssemblyInstructions();
            }
        }
        instruction +='\n';
    }
    return instruction;
}

AssemblyInstruction::~AssemblyInstruction() {
        delete[] details_;
        details_ = nullptr;
        count_ = 0;
        capacity = 0;
        light_details = 0;
        final_ = -1;
    }








