//
// Created by kprlns on 28.05.2020.
//

#ifndef NLP_PAIR_H
#define NLP_PAIR_H


template <typename K, typename V> class Pair {
public:
    /*
    Pair(K& key, V& value) {
        this->key = key;
        this->value = value;
    }
     */
    Pair() = default;
    Pair(K key, V value) {
        this->key = key;
        this->value = value;
    }

    K getKey() const { return key; }
    V getValue() const { return value; }
    void setKey(K newKey) { key = newKey; }
    void setValue(V newValue) { value = newValue; }

    int operator<(Pair<K,V>& other) {
        return key < other.getKey();
    }
    int operator>(Pair<K,V>& other) {
        return other.getKey() < key;
    }
    int operator==(Pair<K,V>& other) {
        return key == other.getKey();
    }

    int operator<(const K& other) {
        return key < other;
    }
    int operator>(const K& other) {
        return other < key;
    }
    int operator==(const K& other) {
        return key == other;
    }

    bool lessThen(Pair<K,V>& other) {
        return key < other.key;
    }
    bool greaterThen(Pair<K,V>& other) {
        return key > other.key;
    }
    bool equals(Pair<K,V>& other) {
        return key == other.key;
    }
    bool lessThen(Pair<K,V>* other) {
        return key < other->key;
    }
    bool greaterThen(Pair<K,V>* other) {
        return key > other->key;
    }
    bool equals(Pair<K,V>* other) {
        return key == other->key;
    }

    K key;
    V value;

    void deleteAll() {
        delete key;
        delete value;
    }

};

#endif //NLP_PAIR_H
