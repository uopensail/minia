#include <iostream>
#include <variant>
#include <vector>
template <typename... Types>
bool areVariantsEqual(const std::variant<Types...> &v1,
                      const std::variant<Types...> &v2) {
    if (v1.index() != v2.index()) {
        return false; // 类型不同
    }

    if (v1.index() != v2.index()) {
        return false; // 类型不同
    }

    return std::visit(
        [](auto &&arg1, auto &&arg2) -> bool {
            using T = std::decay_t<decltype(arg1)>;
            using U = std::decay_t<decltype(arg2)>;
            if constexpr (std::is_same_v<T, U>) {
                return arg1 == arg2; // 类型相同，值比较
            } else {
                return false; // 类型不同，返回 false
            }
        },
        v1, v2);
}

int main() {
    std::variant<std::vector<int>, double, std::string> variant1 = std::vector<int>{10};
    std::variant<std::vector<int>, double, std::string> variant2 = std::vector<int>{10};

    if (areVariantsEqual(variant1, variant2)) {
        std::cout << "Variants are equal." << std::endl;
    } else {
        std::cout << "Variants are not equal." << std::endl;
    }

    return 0;
}
