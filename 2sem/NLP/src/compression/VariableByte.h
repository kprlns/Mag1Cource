//
// Created by kprlns on 19.06.2020.
//

#ifndef NLP_VARIABLEBYTE_H
#define NLP_VARIABLEBYTE_H

#include "myStl/Vector.h"

class VariableByte {
public:
    unsigned char LAST_BIT =       0b10000000;
    unsigned char FIRST_BITS =     0b01111111;
    int BITS_TO_ENCODE = 7;

    Vector<unsigned char>* encode(Vector<int>* input, Vector<unsigned char>* buffer) {
        buffer->clear();
        for(int i = 0; i < input->getSize(); ++i) {
            int current = input->get(i);
            do {
                unsigned char currentBlock = current & FIRST_BITS;
                current = current >> BITS_TO_ENCODE;
                if(current == 0) {
                    currentBlock = currentBlock | LAST_BIT;
                }
                buffer->add(currentBlock);
            } while (current != 0);

        }
        return buffer;
    }

    Vector<int>* decode(Vector<unsigned char>* input, Vector<int>* output) {
        int current = 0;
        int cnt = 0;
        for(int i = 0; i < input->getSize(); ++i) {
            unsigned char currentBlock = input->get(i);
            if(currentBlock & LAST_BIT) {
               currentBlock = currentBlock & FIRST_BITS;
                current = current | (currentBlock << (BITS_TO_ENCODE * cnt));
                //current = (current << BITS_TO_ENCODE);
               output->add(current);
               current = 0;
               cnt = 0;
            } else {
                current = current | (currentBlock << (BITS_TO_ENCODE * cnt));
                cnt++;
            }
        }
        return output;
    }
};


#endif //NLP_VARIABLEBYTE_H
