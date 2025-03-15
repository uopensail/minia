#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

// Helper type trait for vector detection
template <typename T> struct is_vector : std::false_type {};

template <typename T, typename A>
struct is_vector<std::vector<T, A>> : std::true_type {};

template <typename T> inline constexpr bool is_vector_v = is_vector<T>::value;

// 静态断言，确保恰好有一个类型是 std::vector
template <typename... Types> constexpr bool exactly_one_vector() {
    return (0 + ... + is_vector<std::decay_t<Types>>::value) == 1;
}

template <typename... Types> auto repeat_apply() {
    static_assert(exactly_one_vector<Types...>(),
                  "Exactly one type must be a std::vector.");
}

// 主模板，用于查找 std::vector 类型的索引
template <std::size_t Index, typename TargetType, typename... Types>
struct find_vector_index;

// 特化：当找到 std::vector 类型时
template <std::size_t Index, typename TargetType, typename First,
          typename... Rest>
struct find_vector_index<Index, TargetType, First, Rest...> {
    static constexpr std::size_t value =
        is_vector_v<First>
            ? Index
            : find_vector_index<Index + 1, TargetType, Rest...>::value;
};

// 特化：当没有找到 std::vector 类型时（递归结束）
template <std::size_t Index, typename TargetType>
struct find_vector_index<Index, TargetType> {
    static constexpr std::size_t value =
        std::numeric_limits<std::size_t>::max(); // 返回一个无效索引
};

// 用于模板调用的方便别名
template <typename... Types> constexpr std::size_t get_vector_type_index() {
    return find_vector_index<0, void, Types...>::value;
}

template <typename Func, typename... Ts, size_t... Is>
auto partial(Func func, const std::tuple<Ts...> &args,
             std::index_sequence<Is...>, size_t index) {
    return std::bind(
        func, (Is == index ? std::placeholders::_1 : std::get<Is>(args))...);
}

template <auto Func, typename... Ts>
auto bind_with_placeholder(const Ts &...args, size_t index) {
    return partial<Func>(std::make_tuple(args...),
                         std::index_sequence_for<Ts...>{}, index);
}

template <typename Func, typename Tuple, typename ElementType,
          std::size_t... Is>
auto apply_with_replacement(Func func, const Tuple &tuple_args,
                            const ElementType &elem, size_t index,
                            std::index_sequence<Is...>) {
    return func((Is == index ? elem : std::get<Is>(tuple_args))...);
}

template <auto Func, typename... Types>
auto repeat_apply(const Types &...args) {
    static_assert(exactly_one_vector<Types...>(),
                  "Exactly one type must be a std::vector.");

    constexpr const size_t index = get_vector_type_index<Types...>();
    auto tuple_args = std::make_tuple(args...);
    using VecType = std::decay_t<decltype(std::get<index>(tuple_args))>;
    const auto &vec = std::get<index>(tuple_args);

    using ElementType = typename VecType::value_type;
    using ResultType = decltype(Func(
        (std::conditional_t<std::is_same_v<std::decay_t<Types>, VecType>,
                            ElementType, Types>())...));

    std::vector<ResultType> ret;
    ret.reserve(vec.size());

    for (const ElementType &elem : vec) {
        ret.push_back(Func(
            *static_cast<
                std::conditional_t<std::is_same_v<std::decay_t<Types>, VecType>,
                                   ElementType, Types> *>(
                std::is_same_v<std::decay_t<decltype(args)>, VecType>
                    ? (void *)(&elem)
                    : (void *)&args)...));
    }
    return ret;
}

// 示例函数
int example_function(int a, int b) { return a + b; }

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    int addend = 10;

    // 使用 repeat_apply 对每个元素应用 example_function
    auto results =
        repeat_apply<example_function, int, std::vector<int>>(addend, numbers);

    // 输出结果
    for (const auto &result : results) {
        std::cout << result << " ";
    }
    return 0;
}