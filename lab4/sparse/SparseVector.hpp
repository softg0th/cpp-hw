
#include <unordered_map>
#include <vector>
#include <iostream>
#include <type_traits>
#include <stdexcept>

template <class T>
class Sparse {
public:
    std::unordered_map<int, int> container;
    std::unordered_map<int, std::unordered_map<int, int>> matrix;

    void buildContainer(const T& input) {
        int index = 0;
        if constexpr (std::is_same_v<typename T::value_type, int>) {
            for (const auto& value : input) {
                if (value != 0) {
                    container[index] = value;
                }
                index++;
            }
        } else {
            throw std::invalid_argument("Unsupported type for Sparse container");
        }
    }

    void buildMatrix(const std::vector<std::vector<int>>& input) {
        for (size_t i = 0; i < input.size(); ++i) {
            for (size_t j = 0; j < input[i].size(); ++j) {
                if (input[i][j] != 0) {
                    matrix[i][j] = input[i][j];
                }
            }
        }
    }

    virtual void print() const {};
};

template <class T>
class SparseVector : public Sparse<T> {
public:
    std::unordered_map<int, int> add(const std::vector<int>& summand) {
        std::unordered_map<int, int> result = this->container;
        for (size_t i = 0; i < summand.size(); ++i) {
            if (summand[i] != 0) {
                result[i] += summand[i];
            }
        }
        for (auto it = result.begin(); it != result.end();) {
            if (it->second == 0) {
                it = result.erase(it);
            } else {
                ++it;
            }
        }
        return result;
    }

    int multiply(const std::vector<int>& multiplier) {
        int result = 0;
        for (size_t i = 0; i < multiplier.size(); ++i) {
            if (multiplier[i] != 0 && this->container.count(i)) {
                result += this->container[i] * multiplier[i];
            }
        }
        return result;
    }

    std::unordered_map<int, int> scalarMultiply(int scalar) {
        std::unordered_map<int, int> result = this->container;
        for (auto& pair : result) {
            pair.second *= scalar;
        }
        return result;
    }

    virtual void print() const override {
        for (const auto& [index, value] : this->container) {
            std::cout << "(" << index << ", " << value << ") ";
        }
        std::cout << std::endl;
    }
};

template <class T>
class SparseMatrix : public Sparse<T> {
public:
    SparseMatrix add(const SparseMatrix& other) const {
        SparseMatrix result;
        for (const auto& [i, row] : this->matrix) {
            for (const auto& [j, value] : row) {
                result.matrix[i][j] = value;
            }
        }
        for (const auto& [i, row] : other.matrix) {
            for (const auto& [j, value] : row) {
                result.matrix[i][j] += value;
            }
        }
        return result;
    }

    SparseMatrix scalarMultiply(int scalar) const {
        SparseMatrix result;
        for (const auto& [i, row] : this->matrix) {
            for (const auto& [j, value] : row) {
                result.matrix[i][j] = value * scalar;
            }
        }
        return result;
    }

    SparseMatrix transpose() const {
        SparseMatrix result;
        for (const auto& [i, row] : this->matrix) {
            for (const auto& [j, value] : row) {
                result.matrix[j][i] = value;
            }
        }
        return result;
    }

    SparseMatrix power(int n) const {
        if (n < 0) {
            throw std::invalid_argument("Negative powers are not supported.");
        }

        SparseMatrix result;
        SparseMatrix base = *this;

        for (const auto& [i, row] : this->matrix) {
            result.matrix[i][i] = 1;
        }

        while (n > 0) {
            if (n % 2 == 1) {
                result = result.multiplyMatrix(base);
            }
            base = base.multiplyMatrix(base);
            n /= 2;
        }

        return result;
    }

    SparseMatrix multiplyMatrix(const SparseMatrix& other) const {
        SparseMatrix result;

        for (const auto& [i, row] : this->matrix) {
            for (const auto& [k, value] : row) {
                if (other.matrix.count(k)) {
                    for (const auto& [j, otherValue] : other.matrix.at(k)) {
                        result.matrix[i][j] += value * otherValue;
                    }
                }
            }
        }

        return result;
    }

    virtual void print() const override {
        for (const auto& [i, row] : this->matrix) {
            for (const auto& [j, value] : row) {
                std::cout << "(" << i << ", " << j << ") : " << value << " ";
            }
            std::cout << std::endl;
        }
    }
};