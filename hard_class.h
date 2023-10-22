#include "light_class.h"
class AssemblyInstruction{

private:
    Detail** details_ = nullptr;
    size_t count_ = 0;
    size_t capacity = 0;
    size_t light_details = 0;
    int final_ = -1;
    bool* busy_  = nullptr;

public:

    void input_detail(const Detail& detail);

    AssemblyInstruction(const Detail* detail, size_t count);

    AssemblyInstruction(AssemblyInstruction&& other) noexcept;

    AssemblyInstruction(const AssemblyInstruction& other);

    explicit AssemblyInstruction(const Detail& detail);

    ~AssemblyInstruction();

    AssemblyInstruction& operator+=(const Detail& detail);

    Detail& operator[](size_t index);
    const Detail& operator[](size_t index) const;

    void delete_detail(size_t index);

    void check_recur(int *busy_v, int index,const Detail& detail);
    void check_final_detail();

    [[nodiscard]] std::string get_initial_name() const;

    [[nodiscard]] Detail** get_ordered_details() const;

    [[nodiscard]] std::string instruction() const;

};
