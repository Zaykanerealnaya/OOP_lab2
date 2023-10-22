#include <gtest/gtest.h>

#include "light_class.h"
#include "hard_class.h"

TEST(DetailTest, GetName){
std::string name = "detail";
Detail detail(name);
EXPECT_EQ(detail.getName(), name);
}

TEST(DetailTest, GetType){
Detail detail("detail", Detail::Type::INITIAL, nullptr, 0, "");
EXPECT_EQ(detail.getType(), Detail::Type::INITIAL);
}

TEST(DetailTest, GetOtherDetails){
int otherDetails[] = {1, 2, 3};
Detail detail("detail", Detail::Type::INITIAL, otherDetails, 3, "");
const int* result = detail.getOtherDetails();
EXPECT_EQ(result[0], 1);
EXPECT_EQ(result[1], 2);
EXPECT_EQ(result[2], 3);
}

TEST(DetailTest, GetCountOther){
int otherDetails[] = {1, 2, 3};
Detail detail("detail", Detail::Type::INITIAL, otherDetails, 3, "");
EXPECT_EQ(detail.getCountOther(), 3);
}

TEST(DetailTest, GetAssemblyInstructions){
std::string assemblyInfo = "assembly instructions";
Detail detail("detail", Detail::Type::INITIAL, nullptr, 0, assemblyInfo);
EXPECT_EQ(detail.getAssemblyInstructions(), assemblyInfo);
}

TEST(DetailTest, SetType){
Detail detail("detail");
detail.setType(Detail::Type::FINAL);
EXPECT_EQ(detail.getType(), Detail::Type::FINAL);
}

TEST(DetailTest, SetOtherDetails){
int otherDetails[] = {1, 2, 3};
Detail detail("detail", Detail::Type::INITIAL, nullptr, 0, "");
detail.setOtherDetails(otherDetails, 3);
const int* result = detail.getOtherDetails();
EXPECT_EQ(result[0], 1);
EXPECT_EQ(result[1], 2);
EXPECT_EQ(result[2], 3);
}

TEST(DetailTest, SetAssemblyInstructions){
std::string assemblyInfo = "assembly instructions";
Detail detail("detail");
detail.setAssemblyInstructions(assemblyInfo);
EXPECT_EQ(detail.getAssemblyInstructions(), assemblyInfo);
}

TEST(DetailTest, GetUniq){
int otherDetails[] = {1, 2, 3};
Detail detail("detail", Detail::Type::INTERMEDIATE, otherDetails, 3, "");
Detail::Uniq uniq = detail.getUniq();
EXPECT_EQ(uniq.count_elements, 3);
EXPECT_EQ(uniq.detail[0].index, 1);
EXPECT_EQ(uniq.detail[0].count, 1);
}

TEST(DetailTest, FindMax){
int otherDetails[] = {1, 2, 3};
Detail detail("detail", Detail::Type::INITIAL, otherDetails, 3, "");
int max = detail.find_max();
output(detail);
EXPECT_EQ(max, 3);
}

TEST(DetailTest, Comparison){
Detail detail1("detail", Detail::Type::INITIAL, nullptr, 0, "");
Detail detail2("detail", Detail::Type::INITIAL, nullptr, 0, "");
EXPECT_EQ(detail1 <=> detail2, std::strong_ordering::equal);
}

TEST(DetailTest, Add_other_detail){
    int otherDetails[] = {1, 2, 3};
    Detail detail("detail", Detail::Type::INTERMEDIATE, otherDetails, 3, "");
    detail.add_otherDetails(5);

}

// Тестирование функции input_detail()
TEST(AssemblyInstructionTest, InputDetail) {
    Detail detail("Detail1");
    AssemblyInstruction instruction(detail);
    instruction.input_detail(detail);

    ASSERT_EQ(instruction[0].getName(), "Detail1");
}

// Тестирование конструктора AssemblyInstruction(const Detail*, size_t)
TEST(AssemblyInstructionTest, ConstructorWithDetails) {
    Detail detail1("Detail1");
    Detail detail2("Detail2");
    Detail detail3("Detail3");

    Detail details[] = {detail1, detail2, detail3};
    AssemblyInstruction instruction(details, 3);

    ASSERT_EQ(instruction[0].getName(), "Detail1");
    ASSERT_EQ(instruction[1].getName(), "Detail2");
    ASSERT_EQ(instruction[2].getName(), "Detail3");
}

// Тестирование перемещающего конструктора AssemblyInstruction(AssemblyInstruction&&)
TEST(AssemblyInstructionTest, MoveConstructor) {
    Detail detail("Detail1");
    AssemblyInstruction instruction1(detail);

    AssemblyInstruction instruction2(std::move(instruction1));

    ASSERT_EQ(instruction2[0].getName(), "Detail1");
}

// Тестирование копирующего конструктора AssemblyInstruction(const AssemblyInstruction&)
TEST(AssemblyInstructionTest, CopyConstructor) {
    Detail detail("Detail1");
    AssemblyInstruction instruction1(detail);
    instruction1.input_detail(detail);

    AssemblyInstruction instruction2(instruction1);

    ASSERT_EQ(instruction2[0].getName(), "Detail1");
}

// Тестирование оператора +=
TEST(AssemblyInstructionTest, AddDetail) {
    Detail detail1("Detail1");
    Detail detail2("Detail2");
    AssemblyInstruction instruction(detail1);
    instruction += detail2;

    ASSERT_EQ(instruction[0].getName(), "Detail1");
    ASSERT_EQ(instruction[1].getName(), "Detail2");
}

TEST(AssemblyInstructionTest, Chech_final_Delete_Input){
    Detail table_leg1("table_leg");
    Detail table_leg2("emotion_damage");
    Detail table_leg3("table_leg");
    Detail table_leg4("table_leg");
    Detail chair_lag1a("chair_leg");
    Detail chair_lag2a("chair_leg");
    Detail chair_lag3a("chair_leg");
    Detail chair_seata("chair_seat");
    Detail chair_lag1b("chair_leg");
    Detail chair_lag2b("chair_leg");
    Detail chair_lag3b("chair_leg");
    Detail chair_seatb("chair_seat");
    Detail chair_lag1c("chair_leg");
    Detail chair_lag2c("chair_leg");
    Detail chair_lag3c("chair_leg");
    Detail chair_seatc("chair_seat");
    int table_index[] = {0,1,2,3};
    int chaira_index[] = {4,5,6,7};
    int chairb_index[] = {8,9,10,11};
    int chairc_index[] = {12,13,14,15};
    Detail table("table",Detail::Type::INTERMEDIATE,table_index,4,"beautiful.very");
    Detail chaira("chair",Detail::Type::INTERMEDIATE,chaira_index,4,"chair A");
    Detail chairb("chair",Detail::Type::INTERMEDIATE,chairb_index,4,"chair B");
    Detail chairc("chair",Detail::Type::INTERMEDIATE,chairc_index,4,"chair c");
    int dinnig_room_index[] = {16,17,18,19};
    Detail dinning_room("dinnin room", Detail::Type::FINAL,dinnig_room_index,4,"BIG BIG ROOM");

    AssemblyInstruction how_to_make_dinning_room(table_leg1);
    how_to_make_dinning_room+=table_leg2;
    how_to_make_dinning_room+=table_leg3;
    how_to_make_dinning_room+=table_leg4;
    how_to_make_dinning_room+=chair_lag1a;
    how_to_make_dinning_room+=chair_lag2a;
    how_to_make_dinning_room+=chair_lag3a;
    how_to_make_dinning_room+=chair_seata;
    how_to_make_dinning_room+=chair_lag1b;
    how_to_make_dinning_room+=chair_lag2b;
    how_to_make_dinning_room+=chair_lag3b;
    how_to_make_dinning_room+=chair_seatb;
    how_to_make_dinning_room+=chair_lag1c;
    how_to_make_dinning_room+=chair_lag2c;
    how_to_make_dinning_room+=chair_lag3c;
    how_to_make_dinning_room+=chair_seatc;
    how_to_make_dinning_room+=table;
    how_to_make_dinning_room+=chaira;
    how_to_make_dinning_room+=chairb;
    how_to_make_dinning_room+=chairc;
    how_to_make_dinning_room+=dinning_room;
    std::cout << "Inst\n" << how_to_make_dinning_room.instruction() << std::endl;
    std::cout << "Final\n" << std::endl;
    how_to_make_dinning_room.check_final_detail() ;
    std::cout << "Initial\n" << how_to_make_dinning_room.get_initial_name() << std::endl;

    AssemblyInstruction check(how_to_make_dinning_room);
    how_to_make_dinning_room.delete_detail(20);
    how_to_make_dinning_room.delete_detail(18);
    Detail** testing12 = how_to_make_dinning_room.get_ordered_details();
    std::cout << "Final\n" << std::endl;
    how_to_make_dinning_room.check_final_detail() ;
    AssemblyInstruction rest(std::move(how_to_make_dinning_room));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}