#include <iostream>
#include <fstream>
using namespace std;

void createFile(ofstream& filename, int* numbers, int size);
void readFromFile(ifstream& filename, int*& numbers, int& size);
void fromTo(ifstream& in, ofstream& out);
int countBinaryDifference(int num);
void findAndRemoveOddNegativeElements(int* numbers, int& size);
void bubbleSort(int* numbers, int size);

void createFile(ofstream& filename, int* numbers, int size)
{
    if (!filename.is_open()) {
        throw "Failed to open the file.";
    }

    filename << size << endl;
    for (int i = 0; i < size; i++) {
        filename<< numbers[i] << " ";
    }

    filename.close();
}

int* readFromFile(ifstream& filename, int& size) {
    
    if (!filename.is_open()) {
        throw "Failed to open the file.";
    }

    filename >> size;
    int* numbers = new int[size];

    for (int i = 0; i < size; i++) {
        filename>> numbers[i];
    }

    filename.close();

    return numbers;
}

void fromTo(ifstream& in, ofstream& out)
{
    if (!in.is_open())
    {
        throw "Failed to open the file.";
    }

    if (!out.is_open())
    {
        throw "Failed to open the file.";
    }

    int num;
    while (in >> num)
    {
        out << num << " ";
    }

    in.close();
    out.close();
    return;
}

int countBinaryDifference(int num) {
    int countOnes = 0;

    while (num != 0) {
        if (num % 2 == 1) {
            countOnes++;
        }

        num /= 2;
    }

    int countZeros = sizeof(int) * 8 - countOnes;

    return countOnes - countZeros;
}

void findAndRemoveOddNegativeElements(int* numbers, int& size) {
    int* temp = new int[size];
    int tempSize = 0;

    for (int i = 0; i < size; i++) {
        if (numbers[i] >= 0 || numbers[i] % 2 == 0) {
            temp[tempSize++] = numbers[i];
        }
    }

    size = tempSize;
    for (int i = 0; i < size; i++) {
        numbers[i] = temp[i];
    }

    delete[] temp;
}

void bubbleSort(int* numbers, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {

            if (countBinaryDifference(numbers[j + 1]) > countBinaryDifference(numbers[j])) {

                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
}

int main() {
    string fileIn = "in.txt", fileOut = "out.txt";
    ofstream inputFile(fileIn);
    int size = 10;

    int* numbers = new int[size];

    createFile(inputFile, numbers, size);

    ifstream outputFile(fileOut);

    bubbleSort(numbers, size);

    findAndRemoveOddNegativeElements(numbers, size);
    readFromFile(outputFile, numbers, size);
    fromTo(outputFile, inputFile);

    cout << "Enter " << size << " elements of the array: ";
    for (int i = 0; i < size; i++) {
        cin >> numbers[i];
    }



    inputFile.close();
    outputFile.close();

    delete[] numbers;

}