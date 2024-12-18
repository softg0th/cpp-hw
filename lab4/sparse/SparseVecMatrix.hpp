#include <vector>
#include <iostream>
#include <type_traits>
#include <stdexcept>

template <class T>
class Sparse {
public:
    std::vector<int> container;
    std::vector<std::vector<int>> matrix;

    void buildContainer(const T& input) {
        if constexpr (std::is_same_v<typename T::value_type, int>) {
            container.reserve(input.size());
            for (const auto& value : input) {
                container.push_back(value);
            }
        } else {
            throw std::invalid_argument("Unsupported type for Sparse container");
        }
    }

    void buildMatrix(const std::vector<std::vector<int>>& input) {
        matrix.resize(input.size());
        for (size_t i = 0; i < input.size(); ++i) {
            matrix[i].reserve(input[i].size());
            for (const auto& value : input[i]) {
                matrix[i].push_back(value);
            }
        }
    }

    virtual void print() const {}
};

template <class T>
class SparseVector : public Sparse<T> {
public:
    std::vector<int> add(const std::vector<int>& summand) {
        size_t maxSize = std::max(this->container.size(), summand.size());
        std::vector<int> result(maxSize, 0);
        for (size_t i = 0; i < this->container.size(); ++i) {
            result[i] += this->container[i];
        }
        for (size_t i = 0; i < summand.size(); ++i) {
            result[i] += summand[i];
        }
        for (size_t i = 0; i < result.size(); ) {
            if (result[i] == 0) {
                result.erase(result.begin() + i);
            } else {
                ++i;
            }
        }
        return result;
    }

    int multiply(const std::vector<int>& multiplier) {
        int result = 0;
        size_t minSize = std::min(this->container.size(), multiplier.size());
        for (size_t i = 0; i < minSize; ++i) {
            result += this->container[i] * multiplier[i];
        }
        return result;
    }

    std::vector<int> scalarMultiply(int scalar) {
        std::vector<int> result = this->container;
        for (auto& value : result) {
            value *= scalar;
        }
        return result;
    }

    virtual void print() const override {
        for (size_t i = 0; i < this->container.size(); ++i) {
            if (this->container[i] != 0) {
                std::cout << "(" << i << ", " << this->container[i] << ") ";
            }
        }
        std::cout << std::endl;
    }
};

template <class T>
class SparseMatrix : public Sparse<T> {
public:
    SparseMatrix add(const SparseMatrix& other) const {
        size_t rows = std::max(this->matrix.size(), other.matrix.size());
        SparseMatrix result;
        result.matrix.resize(rows);
        for (size_t i = 0; i < this->matrix.size(); ++i) {
            size_t cols = std::max(this->matrix[i].size(), other.matrix[i].size());
            result.matrix[i].resize(cols, 0);
            for (size_t j = 0; j < this->matrix[i].size(); ++j) {
                result.matrix[i][j] += this->matrix[i][j];
            }
        }
        for (size_t i = 0; i < other.matrix.size(); ++i) {
            if (i >= result.matrix.size()) {
                result.matrix.resize(i + 1, std::vector<int>());
            }
            for (size_t j = 0; j < other.matrix[i].size(); ++j) {
                if (j >= result.matrix[i].size()) {
                    result.matrix[i].resize(j + 1, 0);
                }
                result.matrix[i][j] += other.matrix[i][j];
            }
        }
        return result;
    }

    SparseMatrix scalarMultiply(int scalar) const {
        SparseMatrix result;
        result.matrix.resize(this->matrix.size());
        for (size_t i = 0; i < this->matrix.size(); ++i) {
            result.matrix[i].resize(this->matrix[i].size());
            for (size_t j = 0; j < this->matrix[i].size(); ++j) {
                result.matrix[i][j] = this->matrix[i][j] * scalar;
            }
        }
        return result;
    }

    SparseMatrix transpose() const {
        size_t rows = this->matrix.size();
        size_t cols = 0;
        for (const auto& row : this->matrix) {
            if (row.size() > cols) {
                cols = row.size();
            }
        }
        SparseMatrix result;
        result.matrix.resize(cols, std::vector<int>(rows, 0));
        for (size_t i = 0; i < this->matrix.size(); ++i) {
            for (size_t j = 0; j < this->matrix[i].size(); ++j) {
                result.matrix[j][i] = this->matrix[i][j];
            }
        }
        return result;
    }

    SparseMatrix power(int n) const {
        if (n < 0) {
            throw std::invalid_argument("Negative powers are not supported.");
        }
        size_t size = this->matrix.size();
        for (const auto& row : this->matrix) {
            if (row.size() != size) {
                throw std::invalid_argument("Matrix must be square to compute power.");
            }
        }
        SparseMatrix result;
        result.matrix.resize(size, std::vector<int>(size, 0));
        for (size_t i = 0; i < size; ++i) {
            result.matrix[i][i] = 1;
        }
        SparseMatrix base = *this;
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
        size_t rows = this->matrix.size();
        size_t cols = other.matrix.empty() ? 0 : other.matrix[0].size();
        SparseMatrix result;
        result.matrix.resize(rows, std::vector<int>(cols, 0));
        for (size_t i = 0; i < this->matrix.size(); ++i) {
            for (size_t k = 0; k < this->matrix[i].size(); ++k) {
                if (k < other.matrix.size()) {
                    for (size_t j = 0; j < other.matrix[k].size(); ++j) {
                        if (j < cols) {
                            result.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
                        }
                    }
                }
            }
        }
        return result;
    }

    virtual void print() const override {
        for (size_t i = 0; i < this->matrix.size(); ++i) {
            for (size_t j = 0; j < this->matrix[i].size(); ++j) {
                if (this->matrix[i][j] != 0) {
                    std::cout << "(" << i << ", " << j << ") : " << this->matrix[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};
