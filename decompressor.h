#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

inline bool DecodeRLE(const std::string& src_name, const std::string& dst_name)
{
    unsigned char header;   // заголовок данных
    int block_type;         // тип бока
    int data_size;          // размер блока
    char c = {};            // текущий символ

    ifstream in(src_name, ios::binary);
    if (!in) { return false; }

    ofstream out(dst_name, ios::binary);
    if (!out) { return false; }

    do
    {
        if (!in.get(c)) { return false; }

        header = static_cast<unsigned char>(c);
        block_type = (header & 1);
        data_size = (header >> 1) + 1;

        if (block_type)
        {
            if (!in.get(c)) { return false; }
            string s(data_size, c);
            out << std::move(s);
        }
        else
        {
            char block[1024];
            in.read(block, data_size);
            out.write(block, data_size);
        }
    } while (in);

    out.close();
    in.close();

    return 1;
}
