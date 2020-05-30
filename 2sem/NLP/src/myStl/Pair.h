//
// Created by kprlns on 28.05.2020.
//

#ifndef NLP_PAIR_H
#define NLP_PAIR_H


template <typename K, typename V> class Pair {
public:
    Pair(K& key, V& value) {
        this->key = key;
        this->value = value;
    }

    K getKey() const { return key; }
    V getValue() const { return value; }
    void setKey(K newKey) { key = newKey; }
    void setValue(V newValue) { value = newValue; }

    int operator<(const Pair<K,V>& other) {
        return key < other.getKey();
    }
    int operator>(const Pair<K,V>& other) {
        return other.getKey() < key;
    }
    int operator==(const Pair<K,V>& other) {
        return key == other.getKey();
    }

    K key;
    V value;
};

#endif //NLP_PAIR_H
