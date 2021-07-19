//
// Created by podda on 07/07/2021.
//

//#include "lz78encode.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <map>

using namespace std;


class BitWriter{
    ofstream& os;
    unsigned int buffer_dim;
    char buffer;
    int counter=0;

    void writeToBuffer(uint32_t bit){
        buffer = buffer << 1;
        buffer += bit;
        ++buffer_dim;
        if(buffer_dim == 8){
            os.write(&buffer, sizeof(buffer));
            buffer_dim = 0;
            buffer = 0;
            if(counter + 5 == 518)
                cout<<"HERE"<<endl;
            ++counter;
            //std::cout<< "Writing byte " << ++counter +4 << endl;
        }
    }

public:
    BitWriter(ofstream& output) : os(output){
        buffer = 0;
        buffer_dim = 0;
    }

    void write(int element, int nBits){
        for(int i = nBits -1; i >= 0; --i){
            uint32_t tmp = element & (int)pow(2, i);
            tmp = tmp >> i;
            writeToBuffer(tmp);
        }
    }

    void stop(){
        while(buffer_dim != 0){
            writeToBuffer(0);
        }
    }

};

bool lz78encode(const std::string& input_filename, const std::string& output_filename, int maxbits){
    ifstream is;
    ofstream os;

    map<std::string, unsigned int> dictionary;

    is.open(input_filename, std::ios::binary);
    if(!is){
        cout << "Error opening " << input_filename << endl;
        return false;
    }

    os.open(output_filename, std::ios::binary);
    if(!os){
        cout << "Error opening " << output_filename << endl;
        return false;
    }

    int dictSize = pow(2, maxbits);

    //inizio l'encoding
    //Magic number
    os << "LZ78";


    BitWriter bitWriter(os);
    bitWriter.write(maxbits, 5);
    std::string pattern = "";
    char read, get;
    int size;

    while(1){
        size = dictionary.size();

        if(size == (pow(2, maxbits))){
            dictionary.clear();
            size = 0;
        }

        get = is.get();
        if(get==-1)
            break;
        read=get;
        pattern += read;

        if(dictionary.find(pattern) != dictionary.end()){   // la chiave è presente nel dizionario
            continue;
        }
        else{
            if(pattern.size() == 1){
                if(size!=0) {
                    int numBits = floor(log2(size)) +1;
                    bitWriter.write(0, numBits);
                }
                bitWriter.write(read, 8);
                dictionary.insert({pattern, size+1});
                pattern = "";
            }
            else{
                string lastPattern = pattern;
                lastPattern.resize(lastPattern.size()-1);
                int value = dictionary.at(lastPattern);
                int numBits = floor(log2(size)) +1;
                bitWriter.write(value, numBits);
                bitWriter.write(read, 8);
                dictionary.insert({pattern, size + 1});
                pattern = "";
            }
        }
    }

    if(pattern != ""){
        string lastPattern = pattern;
        lastPattern.resize(lastPattern.size()-1);
        if(lastPattern != ""){
            int value = dictionary.at(lastPattern);
            int numBits = floor(log2(size)) +1;
            bitWriter.write(value, numBits);
        }
        else{
            int numBits = floor(log2(size)) +1;
            bitWriter.write(0, numBits);
        }
        bitWriter.write(read, 8);
        pattern = "";
    }

    bitWriter.stop();

    return true;

}
