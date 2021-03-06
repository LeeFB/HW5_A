//
//  accumulate.hpp
//  itertools-cfar-a
//
//  Created by Lee Fingerhut on 08/06/2020.
//  Copyright © 2020 Lee Fingerhut. All rights reserved.
//
#pragma once
#include <iostream>
#include <iterator>
using namespace std;


 //מקבל כקלט מיכל או דמוי-מיכל כלשהו. מחזיר דמוי-מיכל חדש הכולל סכומים חלקיים. לדוגמה
 //accumulate(range(5,9)) מייצג את המספרים 5, 11, 18, 26 (5, 5+6, 5+6+7, 5+6+7+8). וכך גם accumulate(vector({5,6,7,8})).

namespace itertools{
    typedef struct {
    template <typename T>
    auto operator()(const T& a , const T& b) const{
    return a + b;
    }
} _plus;//

    template <typename C, typename F = _plus> 
    class accumulate{
        C container;//getting
        F function;//return

    public:
        accumulate(C c, F f = _plus()) : container(c), function(f) {}

        class iterator {
        F function;
        typename C::iterator iter; //start
        typename C::iterator last; //end
        typename decay<decltype(*(container.begin()))>::type data;//Cumulative value
            
        public:
            iterator(typename C::iterator first, typename C::iterator l, F f) : iter(first), last(l), function(f) {//initialization
                if (iter != last) 
                    data = *iter;
            }

            // ++i;
            iterator &operator++(){
                ++iter;
                if (iter != last)
                    data = function(data, *iter);
                return *this;
            }
            // i++;
            iterator operator++(int){
                iterator i = *this;
                ++(*i);
                return i;
            }
            bool operator==(const iterator &other) const{
                return (iter == other.iter);
            }

            bool operator!=(const iterator &other) const{
                return (iter != other.iter);
            }

            auto operator*() const{
                return data;
            }

            iterator &operator=(const iterator &other){
                if  (*this        != other){
                    this->iter     = other.it;
                    this->last     = other.last;
                    this->data     = other.data;
                    this->function = other.function;
                }
                return *this;
            }
        };
        iterator begin(){
            return iterator(container.begin(), container.end(), function);
        }

        iterator end(){
            return iterator(container.end(), container.end(), function);
        }
    };
}