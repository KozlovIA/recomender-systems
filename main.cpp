#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <conio.h>

using namespace std;

vector<vector<int>> read_txt(string file_name)
{
    ifstream inputFile(file_name);
    if (!inputFile.is_open())
    {
        cerr << "Failed to open the file." << endl;
        // return 0;
    }

    vector<vector<int>> data; // Вектор векторов для хранения значений

    string line;
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        vector<int> values;
        int value;
        while (iss >> value)
        {
            values.push_back(value);
        }
        data.push_back(values);
    }

    // Теперь у вас есть вектор векторов data, в котором каждый внутренний вектор содержит значения из соответствующей строки файла.

    inputFile.close(); // Не забудьте закрыть файл после использования.

    return data;
}

vector<int> read_txt_key(string file_name)
{
    ifstream inputFile("read_by_user_keys.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Невозможно открыть файл." << std::endl;
    }

    std::vector<int> values;
    int value;

    while (inputFile >> value)
    {
        values.push_back(value);
    }

    inputFile.close();

    return values;
}

int main()
{
    cout << "Start" << endl;
    vector<vector<int>> data = read_txt("read_by_user.txt");
    vector<int> keys = read_txt_key("read_by_user_keys.txt");

    // дальше после чтения

    ofstream outputFile("output_key_index.txt"); // Открываем файл для записи

    bool out_of_cyrcle = false;

    if (outputFile.is_open())
    {
        int length_data = data.size();
        int i = 0;
        for (i = 0; i < length_data; i++) // все строки
        {
            if (i % 1000 == 0)
                cout << i << endl;
            int j = 0;
            if (i == length_data - 1)
                j = 0;
            else
                j = i + 1;
            for (j; j < length_data - 1; j++) // проходим по оставшимся строкам
            {
                for (int k = 0; k < data[i].size(); k++)
                {
                    for (int l = 0; l < data[j].size(); l++)
                    {
                        if (data[i][k] == data[j][l])
                        {
                            // cout << "(" << i << ", " << j << ")"
                            //      << "\n";
                            outputFile << "(" << keys[i] << ", " << keys[j] << ")"
                                       << "\n";
                            out_of_cyrcle = true;
                            break;
                        }
                        if (out_of_cyrcle)
                        {
                            out_of_cyrcle = false;
                            break;
                        }
                    }
                }
            }
        }

        // Закрываем файл после записи
        outputFile.close();
        std::cout << "The information was successfully written to the file." << std::endl;
    }

    else
    {
        std::cerr << "The file cannot be opened for writing." << std::endl;
    }

    // getch();

    return 0;
}
