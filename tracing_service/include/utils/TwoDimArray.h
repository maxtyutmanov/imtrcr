#ifndef UTILS_TWO_DIM_ARRAY_H
#define UTILS_TWO_DIM_ARRAY_H

#include <stdexcept>

namespace ImTrcr {
namespace Utils {

    template <typename T>
    class TwoDimArray {
    public:
        TwoDimArray(int rows, int columns);
        TwoDimArray(int rows, int columns, T defaultVal);

        T& At(int row, int column);
        const T& At(int row, int column) const;

        int GetRowCount() const;
        int GetColumnCount() const;

        ~TwoDimArray();
    private:
        void Init(int rows, int columns);
        void CheckCoordinates(int r, int c) const;

        int rows;
        int columns;
        T** internalAr;
    };


    template <typename T>
    TwoDimArray<T>::TwoDimArray(int rows, int columns) {
        Init(rows, columns);
    }

    template <typename T>
    TwoDimArray<T>::TwoDimArray(int rows, int columns, T defaultVal) {
        Init(rows, columns);

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < columns; ++c) {
                At(r, c) = defaultVal;
            }
        }
    }

    template <typename T>
    T& TwoDimArray<T>::At(int row, int column) {
        CheckCoordinates(row, column);
        return internalAr[row][column];
    }

    template <typename T>
    const T& TwoDimArray<T>::At(int row, int column) const {
        CheckCoordinates(row, column);
        return internalAr[row][column];
    }

    template <typename T>
    int TwoDimArray<T>::GetRowCount() const {
        return rows;
    }

    template <typename T>
    int TwoDimArray<T>::GetColumnCount() const {
        return columns;
    }

    template <typename T>
    TwoDimArray<T>::~TwoDimArray() {
        for (unsigned int r = 0; r < rows; ++r) {
            delete [] internalAr[r];
        }

        delete [] internalAr;
    }

    template <typename T>
    void TwoDimArray<T>::Init(int rows, int columns) {
        this->rows = rows;
        this->columns = columns;

        if (rows <= 0 || columns <= 0) {
            throw std::logic_error("Size of array must be a positive integer");
        }

        internalAr = new bool*[rows];

        for (int i = 0; i < rows; ++i) {
            internalAr[i] = new bool[columns];
        }
    }

    template <typename T>
    void TwoDimArray<T>::CheckCoordinates(int r, int c) const {
        if (r < 0 || r >= rows ||
            c < 0 || c >= columns) {

            throw std::logic_error("Wrong row and/or column indices in two dimensional array");
        }
    }
}
}

#endif